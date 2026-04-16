# CSL3080 Assignment-2: P2P CHORD Ring Network in OMNeT++

## Team Members
- Student 1: `<Roll Number 1>`
- Student 2: `<Roll Number 2>`

---

## Description

This assignment implements a **fully peer-to-peer distributed system** using **OMNeT++ Discrete Event Simulator**. The network consists of N client nodes arranged in a **ring topology**, augmented with **CHORD Distributed Hash Table** finger connections to achieve **O(log N)** message routing complexity.

### Key Features

| Feature | Details |
|---|---|
| Topology | Ring + CHORD finger table |
| Task | Find maximum element in a distributed array |
| Routing | O(log N) via CHORD finger table |
| Gossip | Flood-with-ML (Message Log) gossip for termination |
| Config | N is read dynamically from `topo.txt` |

---

## Architecture Overview

```
Client 0 (Initiator)
  ├── Divides array into x subtasks (x > N, each part ≥ 2 elements)
  ├── Routes subtask i to Client (i % N) via CHORD
  └── Consolidates results → final max

Each Client
  ├── Ring connections: successor (i+1)%N, predecessor (i-1+N)%N
  ├── CHORD fingers: (i + 2^k) % N for k = 0..floor(log2(N))-1
  ├── Receives subtasks, computes local max, returns result
  └── Generates gossip after task completion

Gossip Protocol
  └── Flood with ML (Message Log) to prevent loops
      └── Terminate when all N gossip messages received
```

---

## File Structure

```
cn2/
├── src/
│   ├── Client.ned          # Client module NED declaration
│   ├── Client.h            # Client module header
│   ├── Client.cc           # Client module implementation
│   ├── NetworkManager.ned  # NetworkManager NED declaration
│   ├── NetworkManager.cc   # Dynamic topology wiring
│   ├── Network.ned         # Top-level network NED
│   ├── Messages.msg        # Message type definitions
│   └── package.ned         # Package namespace
├── topo.txt                --->>> move this file inside simulation folder
├── config.csv              # Simulation configuration
├── omnetpp.ini             # OMNeT++ run configuration
├── Makefile                # Build script
└── README.md               # This file
```

---

## Prerequisites

- **OMNeT++ 6.x** installed and environment set up
  - Download: https://omnetpp.org/download/
  - Installation guide: https://doc.omnetpp.org/omnetpp/InstallGuide.pdf
- Linux/macOS (or Windows with MinGW via OMNeT++ installer)
- `opp_msgc`, `opp_makemake` must be in PATH (after running OMNeT++ `setenv`)

---

## Compilation Steps

### Step 1: Set up OMNeT++ environment
```bash
# Navigate to your OMNeT++ installation directory
cd /path/to/omnetpp-6.x
source setenv
```

### Step 2: Navigate to the project directory
```bash
cd /path/to/assignment2
```

### Step 3: Generate message files and build
```bash
# Generate Messages_m.cc and Messages_m.h from Messages.msg
opp_msgc src/Messages.msg

# Generate Makefile for the project
cd src
opp_makemake -f --deep -o assignment2 -O out
make
cd ..
```

Or simply use the provided Makefile:
```bash
make
```

---

## Running the Simulation

### Command-line mode (Cmdenv)
```bash
cd src
./assignment2 -u Cmdenv -f ../omnetpp.ini
```

### GUI mode (Qtenv) — for visual inspection
```bash
cd src
./assignment2 -u Qtenv -f ../omnetpp.ini
```

### Or using Makefile:
```bash
make run        # Command line
make run-gui    # GUI
```

---

## Changing Network Size (N)

> **The evaluator will only edit `topo.txt` — no code changes needed.**

Edit `topo.txt`:
```
N=16
```

Then re-run the simulation. The network topology is built dynamically from this value.

Valid values: N ≥ 2 (recommended: powers of 2 for clean CHORD finger tables)

---

## Output

### Console Output (via EV / Cmdenv)
```
[Client 0] Task started. Array size=32 Subtasks=13
[Client 0] Sending subtask 0 -> target Client 0
[Client 3] Subtask 3 result (max) = 847
[Client 0] Received result for subtask 3: max = 847
[Client 0] FINAL RESULT: Maximum element = 983
[Client 2] GOSSIP received (first time) at t=0.05 from node 1 | 0.1:10.0.0.0:Client0#
```

### Output File (`outputfile.txt`)
- All subtask results (per client)
- Final consolidated result
- All gossip messages with timestamp and sender IP

---

## CHORD Routing Details

Each client `i` maintains a finger table:
```
finger[k] = (i + 2^k) % N,  k = 0, 1, ..., floor(log2(N)) - 1
```

**Example (N=8, Client 0):**
| k | finger[k] |
|---|---|
| 0 | 1 |
| 1 | 2 |
| 2 | 4 |

Routing: to reach target T from node S, forward to the largest finger that doesn't overshoot T → **O(log N) hops**.

---

## Gossip Message Format

```
<simTime>:<IP>:<ClientID#>
```

Example:
```
0.103:10.0.0.0:Client0#
```

---

## Notes
- `outputfile.txt` is opened in **append mode** — delete it before each fresh run
- Client 0 is always the initiator
- All clients are assumed honest (as per assignment spec)
- Finger connections are **unidirectional** (send only); responses return via ring

---

## References
- OMNeT++ Install Guide: https://doc.omnetpp.org/omnetpp/InstallGuide.pdf
- CHORD DHT: https://medium.com/techlog/chord-building-a-dht-distributed-hash-table-in-golang-67c3ce1
- OMNeT++ Dynamic Modules (Section 4.13): https://doc.omnetpp.org/omnetpp/manual/
