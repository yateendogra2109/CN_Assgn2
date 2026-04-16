//============================================================
// Client.cc
// Implementation of the Client module for CSL3080 Assignment-2
//
// Features:
//  - Reads N from topo.txt dynamically
//  - Ring topology + CHORD finger table connections
//  - Distributes subtasks (find-max) with O(log N) routing
//  - Gossip protocol for termination
//  - Outputs results to console and outputfile.txt
//============================================================

#include "Client.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

Define_Module(Client);

//------------------------------------------------------------
// initialize(): called once when simulation starts
//------------------------------------------------------------
void Client::initialize() {
    // Assign identity
    selfID = par("clientID").intValue();
    readTopology();  // sets N

    selfIP = "10.0.0." + std::to_string(selfID);
    isInitiator = (selfID == 0); // Client 0 initiates the task
    receivedResultCount = 0;
    gossipReceivedCount = 0;
    taskDone = false;

    // Open output file (append mode so all clients share one file)
    outputFile.open("outputfile.txt", std::ios::app);
    if (!outputFile.is_open()) {
        EV << "[Client " << selfID << "] WARNING: Could not open outputfile.txt\n";
    }

    // Build CHORD finger table
    buildFingerTable();

    EV << "[Client " << selfID << "] Initialized. N=" << N
       << " IP=" << selfIP << "\n";

    // Only the initiator (Client 0) starts the task
    if (isInitiator) {
        // Use a self-message to start after all modules are initialized
        cMessage *startMsg = new cMessage("startTask");
        scheduleAt(simTime() + 0.1, startMsg);
    }
}

//------------------------------------------------------------
// readTopology(): parse N from topo.txt
//------------------------------------------------------------
void Client::readTopology() {
    std::ifstream topoFile("topo.txt");
    if (!topoFile.is_open()) {
        throw cRuntimeError("Cannot open topo.txt! Make sure it exists in the run directory.");
    }
    std::string line;
    N = 0;
    while (std::getline(topoFile, line)) {
        if (line.rfind("N=", 0) == 0) {
            N = std::stoi(line.substr(2));
            break;
        }
    }
    topoFile.close();
    if (N <= 0) {
        throw cRuntimeError("Invalid or missing N in topo.txt");
    }
}

//------------------------------------------------------------
// buildFingerTable(): CHORD finger table
//   finger[k] = (selfID + 2^k) % N, k = 0..floor(log2(N))-1
//------------------------------------------------------------
void Client::buildFingerTable() {
    fingerTable.clear();
    fingerTableSize = (int)std::floor(std::log2((double)N));
    for (int k = 0; k < fingerTableSize; k++) {
        int target = (selfID + (1 << k)) % N;
        fingerTable.push_back(target);
    }
    EV << "[Client " << selfID << "] Finger table: ";
    for (int f : fingerTable) EV << f << " ";
    EV << "\n";
}

//------------------------------------------------------------
// initializeTask(): called by initiator (Client 0)
//   Generates array, divides into x subtasks, sends each
//------------------------------------------------------------
void Client::initializeTask() {
    // Array size: we use 32 elements
    arraySize = 32;
    // x must be > N and k/x >= 2 => x <= k/2
    // Choose x = N + (N/2) to satisfy both, clamped to arraySize/2
    totalSubtasks = std::min(N + (N / 2) + 1, arraySize / 2);
    if (totalSubtasks <= N) totalSubtasks = N + 1;

    // Generate input array with random values
    srand(42); // fixed seed for reproducibility
    inputArray.resize(arraySize);
    for (int i = 0; i < arraySize; i++) {
        inputArray[i] = rand() % 1000 + 1;
    }

    EV << "[Client " << selfID << "] Task started. Array size=" << arraySize
       << " Subtasks=" << totalSubtasks << "\n";
    logOutput("[Client " + std::to_string(selfID) + "] Array: ");
    for (int v : inputArray) {
        if (outputFile.is_open()) outputFile << v << " ";
    }
    if (outputFile.is_open()) outputFile << "\n";

    // Divide array into totalSubtasks parts
    int baseSize = arraySize / totalSubtasks;
    if (baseSize < 2) baseSize = 2; // Guarantee at least 2 per subtask
    // Recalculate totalSubtasks to ensure k/x >= 2
    totalSubtasks = arraySize / baseSize;
    if (totalSubtasks <= N) totalSubtasks = N + 1;

    int idx = 0;
    for (int i = 0; i < totalSubtasks && idx < arraySize; i++) {
        int end = (i == totalSubtasks - 1) ? arraySize : std::min(idx + baseSize, arraySize);
        std::vector<int> sub(inputArray.begin() + idx, inputArray.begin() + end);
        idx = end;
        sendSubtask(i, sub);
    }
}

//------------------------------------------------------------
// sendSubtask(): create and route a SubtaskMsg
//------------------------------------------------------------
void Client::sendSubtask(int subtaskID, std::vector<int> subArray) {
    int targetID = subtaskID % N;

    SubtaskMsg *msg = new SubtaskMsg("subtask");
    msg->setSubtaskID(subtaskID);
    msg->setTargetClientID(targetID);
    msg->setOriginClientID(selfID);
    msg->setDataArrArraySize(subArray.size());
    for (int j = 0; j < (int)subArray.size(); j++) {
        msg->setDataArr(j, subArray[j]);
    }
    msg->setDataSize((int)subArray.size());

    EV << "[Client " << selfID << "] Sending subtask " << subtaskID
       << " -> target Client " << targetID << "\n";

    if (targetID == selfID) {
        // Self-delivery
        scheduleAt(simTime() + 0.01, msg);
    } else {
        routeSubtask(msg);
    }
}

//------------------------------------------------------------
// chordNextHop(): returns gate index (neighbor) for routing to dest
//   Uses CHORD logic: find largest finger that doesn't overshoot
//------------------------------------------------------------
int Client::chordNextHop(int destination) {
    if (destination == selfID) return -1; // Already here

    // Check direct ring neighbors first
    int successor   = (selfID + 1) % N;
    int predecessor = (selfID - 1 + N) % N;

    if (destination == successor)   return 0; // gate 0 = successor
    if (destination == predecessor) return 1; // gate 1 = predecessor

    // Try finger table (largest finger not overstepping destination)
    // Distance in ring from selfID to destination (clockwise)
    int distToDest = (destination - selfID + N) % N;

    int bestGate = 0; // default: send to successor
    int bestDist = distToDest;

    for (int k = fingerTableSize - 1; k >= 0; k--) {
        int finger = fingerTable[k];
        int distToFinger = (finger - selfID + N) % N;
        if (distToFinger > 0 && distToFinger <= distToDest) {
            // This finger is closer to destination than current best
            if (distToFinger <= bestDist) {
                bestDist = distToFinger;
                // Gate for finger k: fingers start at gate index 2
                bestGate = 2 + k;
            }
        }
    }
    return bestGate;
}

//------------------------------------------------------------
// routeSubtask(): forward subtask toward its target
//------------------------------------------------------------
void Client::routeSubtask(SubtaskMsg *msg) {
    int target = msg->getTargetClientID();
    int gateIdx = chordNextHop(target);
    // Gate naming: out[0]=successor, out[1]=predecessor, out[2+]=fingers
    std::string gateName = "peers$o";
    send(msg, gateName.c_str(), gateIdx);
}

//------------------------------------------------------------
// routeResult(): forward result toward its target
//------------------------------------------------------------
void Client::routeResult(ResultMsg *msg) {
    int target = msg->getTargetClientID();
    int gateIdx = chordNextHop(target);
    send(msg, "peers$o", gateIdx);
}

//------------------------------------------------------------
// processSubtask(): compute max of subarray, send result back
//------------------------------------------------------------
void Client::processSubtask(SubtaskMsg *msg) {
    int subtaskID  = msg->getSubtaskID();
    int originID   = msg->getOriginClientID();
    int dataSize   = msg->getDataSize();

    int maxVal = msg->getDataArr(0);
    for (int i = 1; i < dataSize; i++) {
        if (msg->getDataArr(i) > maxVal) maxVal = msg->getDataArr(i);
    }

    std::string logLine = "[Client " + std::to_string(selfID) + "] Subtask " +
                          std::to_string(subtaskID) + " result (max) = " +
                          std::to_string(maxVal);
    EV << logLine << "\n";
    logOutput(logLine);

    // Send result back to origin
    ResultMsg *result = new ResultMsg("result");
    result->setSubtaskID(subtaskID);
    result->setResult(maxVal);
    result->setOriginClientID(originID);
    result->setTargetClientID(originID);

    if (originID == selfID) {
        // Self-delivery
        scheduleAt(simTime() + 0.01, result);
    } else {
        routeResult(result);
    }

    delete msg;
}

//------------------------------------------------------------
// processResult(): accumulate results at initiator
//------------------------------------------------------------
void Client::processResult(ResultMsg *msg) {
    int subtaskID = msg->getSubtaskID();
    int result    = msg->getResult();

    subtaskResults[subtaskID] = result;
    receivedResultCount++;

    std::string logLine = "[Client " + std::to_string(selfID) + "] Received result for subtask " +
                          std::to_string(subtaskID) + ": max = " + std::to_string(result);
    EV << logLine << "\n";
    logOutput(logLine);

    if (receivedResultCount >= totalSubtasks) {
        // All results received - compute final max
        int finalMax = INT_MIN;
        for (auto &kv : subtaskResults) {
            if (kv.second > finalMax) finalMax = kv.second;
        }
        std::string finalLog = "[Client " + std::to_string(selfID) +
                               "] FINAL RESULT: Maximum element = " +
                               std::to_string(finalMax);
        EV << finalLog << "\n";
        logOutput(finalLog);

        // Start gossip
        generateGossip();
    }
    delete msg;
}

//------------------------------------------------------------
// generateGossip(): create and broadcast gossip message
//------------------------------------------------------------
void Client::generateGossip() {
    std::string content = makeGossipContent();
    messageLog.insert(content);

    GossipMsg *gmsg = new GossipMsg("gossip");
    gmsg->setContent(content.c_str());
    gmsg->setOriginID(selfID);
    gmsg->setFromID(selfID);

    // Send to all neighbors (successor, predecessor, all fingers)
    int totalGates = 2 + fingerTableSize; // ring + fingers
    for (int g = 0; g < totalGates; g++) {
        if (gateSize("peers$o") > g) {
            GossipMsg *copy = gmsg->dup();
            copy->setFromID(selfID);
            send(copy, "peers$o", g);
        }
    }
    delete gmsg;
}

//------------------------------------------------------------
// handleGossip(): gossip protocol handler
//------------------------------------------------------------
void Client::handleGossip(GossipMsg *msg) {
    std::string content = msg->getContent();
    int fromID = msg->getFromID();

    if (messageLog.find(content) == messageLog.end()) {
        // First time seeing this gossip
        messageLog.insert(content);
        gossipReceivedCount++;

        std::string logLine = "[Client " + std::to_string(selfID) +
                              "] GOSSIP received (first time) at t=" +
                              std::to_string(simTime().dbl()) +
                              " from node " + std::to_string(fromID) +
                              " | " + content;
        EV << logLine << "\n";
        logOutput(logLine);

        // Forward to all neighbors except the one it came from
        int totalGates = 2 + fingerTableSize;
        for (int g = 0; g < totalGates; g++) {
            if (gateSize("peers$o") > g) {
                GossipMsg *copy = msg->dup();
                copy->setFromID(selfID);
                send(copy, "peers$o", g);
            }
        }
    }
    // Else: duplicate, ignore

    // Check termination: received gossip from all N clients
    if (gossipReceivedCount >= N) {
        EV << "[Client " << selfID << "] Received all N gossip messages. Terminating.\n";
        logOutput("[Client " + std::to_string(selfID) + "] All gossips received. Done.");
        taskDone = true;
    }

    delete msg;
}

//------------------------------------------------------------
// makeGossipContent(): format gossip string
//------------------------------------------------------------
std::string Client::makeGossipContent() {
    std::ostringstream oss;
    oss << simTime().dbl() << ":" << selfIP << ":Client" << selfID << "#";
    return oss.str();
}

//------------------------------------------------------------
// logOutput(): write line to outputfile.txt
//------------------------------------------------------------
void Client::logOutput(const std::string &line) {
    if (outputFile.is_open()) {
        outputFile << line << "\n";
        outputFile.flush();
    }
}

//------------------------------------------------------------
// gateToNeighborID(): helper (unused externally, kept for debug)
//------------------------------------------------------------
int Client::gateToNeighborID(int gateIndex) {
    if (gateIndex == 0) return (selfID + 1) % N;      // successor
    if (gateIndex == 1) return (selfID - 1 + N) % N;  // predecessor
    int k = gateIndex - 2;
    if (k < fingerTableSize) return fingerTable[k];
    return -1;
}

//------------------------------------------------------------
// handleMessage(): main message dispatcher
//------------------------------------------------------------
void Client::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        if (strcmp(msg->getName(), "startTask") == 0) {
            initializeTask();
            delete msg;
        } else if (dynamic_cast<SubtaskMsg*>(msg)) {
            processSubtask(dynamic_cast<SubtaskMsg*>(msg));
        } else if (dynamic_cast<ResultMsg*>(msg)) {
            processResult(dynamic_cast<ResultMsg*>(msg));
        } else {
            delete msg;
        }
        return;
    }

    if (SubtaskMsg *smsg = dynamic_cast<SubtaskMsg*>(msg)) {
        if (smsg->getTargetClientID() == selfID) {
            processSubtask(smsg);
        } else {
            routeSubtask(smsg); // Forward
        }
    } else if (ResultMsg *rmsg = dynamic_cast<ResultMsg*>(msg)) {
        if (rmsg->getTargetClientID() == selfID) {
            processResult(rmsg);
        } else {
            routeResult(rmsg); // Forward
        }
    } else if (GossipMsg *gmsg = dynamic_cast<GossipMsg*>(msg)) {
        handleGossip(gmsg);
    } else {
        EV << "[Client " << selfID << "] Unknown message type received.\n";
        delete msg;
    }
}

//------------------------------------------------------------
// finish(): cleanup
//------------------------------------------------------------
void Client::finish() {
    if (outputFile.is_open()) {
        outputFile.close();
    }
}
