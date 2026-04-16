//============================================================
// Client.h
// Header for the Client module in the P2P CHORD-based ring.
// Each client can initiate tasks, route messages via CHORD,
// process subtasks, and participate in gossip protocol.
//============================================================

#ifndef CLIENT_H_
#define CLIENT_H_

#include <omnetpp.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>
#include <string>

#include "Messages_m.h"  // Auto-generated from Messages.msg

using namespace omnetpp;

class Client : public cSimpleModule {
private:
    // ---- Node Identity ----
    int selfID;          // This client's ID (0 to N-1)
    int N;               // Total number of clients in network
    std::string selfIP;  // Simulated IP = "10.0.0.<selfID>"

    // ---- CHORD Finger Table ----
    // fingerTable[k] = (selfID + 2^k) % N
    std::vector<int> fingerTable;
    int fingerTableSize; // = floor(log2(N))

    // ---- Task / Subtask State ----
    bool isInitiator;       // True if this client initiates the task
    int totalSubtasks;      // x: number of subtasks (x > N)
    int arraySize;          // k: total array elements
    std::vector<int> inputArray; // Full array (only at initiator)
    std::map<int, int> subtaskResults; // subtaskID -> result
    int receivedResultCount; // How many results received so far

    // ---- Gossip Protocol State ----
    std::set<std::string> messageLog; // hash/content of seen gossip messages
    int gossipReceivedCount;          // Distinct gossip messages received
    bool taskDone;                    // Whether this node has finished

    // ---- Output File ----
    std::ofstream outputFile;

    // ---- Internal Helpers ----
    void readTopology();
    void buildFingerTable();
    void initializeTask();
    void sendSubtask(int subtaskID, std::vector<int> subArray);
    int  chordNextHop(int destination);
    void routeSubtask(SubtaskMsg *msg);
    void routeResult(ResultMsg *msg);
    int  findMax(int* arr, int size);
    void processSubtask(SubtaskMsg *msg);
    void processResult(ResultMsg *msg);
    void generateGossip();
    void handleGossip(GossipMsg *msg);
    void logOutput(const std::string &line);
    std::string makeGossipContent();
    int  gateToNeighborID(int gateIndex);

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

#endif /* CLIENT_H_ */
