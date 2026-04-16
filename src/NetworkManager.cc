//============================================================
// NetworkManager.cc
// Dynamically wires the ring + CHORD finger connections
// between client nodes based on N read from topo.txt.
//
// Gate layout (per client):
//   peers$o[0] / peers$i[0]  -> successor   (i+1)%N
//   peers$o[1] / peers$i[1]  -> predecessor (i-1+N)%N
//   peers$o[2+]/ peers$i[2+] -> CHORD finger[k] = (i+2^k)%N
//============================================================

#include <omnetpp.h>
#include <fstream>
#include <string>
#include <cmath>

using namespace omnetpp;

class NetworkManager : public cSimpleModule {
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override {}
    int readN();
};

Define_Module(NetworkManager);

int NetworkManager::readN() {
    std::ifstream f("topo.txt");
    if (!f.is_open())
        throw cRuntimeError("Cannot open topo.txt");
    std::string line;
    int N = 0;
    while (std::getline(f, line)) {
        if (line.rfind("N=", 0) == 0) {
            N = std::stoi(line.substr(2));
            break;
        }
    }
    if (N <= 0)
        throw cRuntimeError("Invalid N in topo.txt");
    return N;
}

void NetworkManager::initialize() {
    int N = readN();
    int fingerTableSize = (int)std::floor(std::log2((double)N));
    int totalGatesPerNode = 2 + fingerTableSize; // successor + predecessor + fingers

    EV << "[NetworkManager] N=" << N << " fingerTableSize=" << fingerTableSize
       << " gates per node=" << totalGatesPerNode << "\n";

    // Get parent (the ChordNetwork module)
    cModule *parent = getParentModule();

    // Set up gate sizes for each client
    for (int i = 0; i < N; i++) {
        cModule *client = parent->getSubmodule("client", i);
        if (!client)
            throw cRuntimeError("Client %d not found", i);
        client->setGateSize("peers", totalGatesPerNode);
    }

    // Create ring connections: each client i <-> (i+1)%N
    for (int i = 0; i < N; i++) {
        int j = (i + 1) % N;
        cModule *ci = parent->getSubmodule("client", i);
        cModule *cj = parent->getSubmodule("client", j);

        // ci.peers[0] (successor) <-> cj.peers[1] (predecessor)
        cGate *ciOut = ci->gate("peers$o", 0);
        cGate *ciIn  = ci->gate("peers$i", 0);
        cGate *cjOut = cj->gate("peers$o", 1);
        cGate *cjIn  = cj->gate("peers$i", 1);

        // i -> j (successor direction)
        ciOut->connectTo(cjIn);
        // j -> i (predecessor direction)
        cjOut->connectTo(ciIn);
    }

    // Create CHORD finger connections
    for (int i = 0; i < N; i++) {
        cModule *ci = parent->getSubmodule("client", i);
        for (int k = 0; k < fingerTableSize; k++) {
            int fingerTarget = (i + (1 << k)) % N;
            cModule *cf = parent->getSubmodule("client", fingerTarget);

            // Gate index 2+k for finger k
            int gateIdx = 2 + k;

            cGate *ciOut = ci->gate("peers$o", gateIdx);
            cGate *cfIn  = cf->gate("peers$i", gateIdx);

            // Unidirectional: i -> fingerTarget (for sending)
            // Note: for bidirectional you'd need to track reverse too.
            // Here we use unidirectional finger gates (receive via ring).
            if (!ciOut->isConnected()) {
                ciOut->connectTo(cfIn);
            }

            EV << "[NetworkManager] Finger: Client " << i
               << " gate[" << gateIdx << "] -> Client " << fingerTarget << "\n";
        }
    }

    EV << "[NetworkManager] Topology setup complete.\n";
}
