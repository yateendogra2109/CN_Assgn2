//============================================================
// NetworkManager.ned
// NED declaration for the NetworkManager module.
// This module wires the ring + CHORD finger topology
// dynamically based on N from topo.txt.
//============================================================

package cn2;

simple NetworkManager {
    parameters:
        @display("i=block/control");
}
