// Messages.msg
// Defines all message types used in the P2P CHORD-based ring network

// Message sent to assign a subtask (subarray) to a target client
message SubtaskMsg {
    int subtaskID;       // Unique subtask ID (i)
    int targetClientID;  // Target = subtaskID % N
    int originClientID;  // Who initiated this task
    int dataArr[];       // Subarray data
    int dataSize;        // Number of elements in subarray
}

// Message sent back with the result (max) of a subtask
message ResultMsg {
    int subtaskID;       // Which subtask this result belongs to
    int result;          // Max element found in subarray
    int originClientID;  // Who should receive this result
    int targetClientID;  // Routing target
}

// Wrapper used for CHORD-based hop-by-hop routing
message RoutingMsg {
    int finalDestID;     // Ultimate destination client ID
    string payloadType;  // "subtask" or "result"
    // The actual payload is embedded as a subobject via encapsulation
}

// Gossip message broadcast after task completion
message GossipMsg {
    string content;      // "<timestamp>:<IP>:<ClientID>"
    int originID;        // Who generated this gossip
    int fromID;          // Immediate sender (for loop prevention)
}
