//============================================================
// Network.ned
// NED description for the P2P CHORD-based ring network.
//
// N is read from topo.txt at runtime by NetworkManager.
// NetworkManager dynamically wires ring + CHORD connections.
//
// Gate layout per Client:
//   peers[0]  -> ring successor   (i+1)%N
//   peers[1]  -> ring predecessor (i-1+N)%N
//   peers[2+] -> CHORD finger[k]  = (i+2^k)%N
//============================================================

package cn2;

network ChordNetwork {
    parameters:
        @display("bgb=800,600");
        int numClients = default(8);  // Overridden at runtime from topo.txt

    submodules:
        // Topology manager: reads topo.txt and wires connections
        manager: NetworkManager {
            @display("p=400,50");
        }

        // Client nodes
        client[numClients]: Client {
            clientID = index;
            @display("p=,,ring,150");
        }

    connections allowunconnected:
        // All connections are dynamically created by NetworkManager
}
