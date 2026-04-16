//============================================================
// Client.ned
// NED declaration for the Client simple module.
//============================================================

package cn2;

simple Client {
    parameters:
        int clientID;       // Assigned at network setup (= index)
        @display("i=device/pc");

    gates:
        inout peers[];     // Dynamic gate array:
                           //   peers[0]  = ring successor
                           //   peers[1]  = ring predecessor
                           //   peers[2+] = CHORD finger table entries
}
