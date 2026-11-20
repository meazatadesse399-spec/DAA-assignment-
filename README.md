# Network Design Using Greedy Algorithms for Minimum Spanning Trees

A collaborative university project for **Design and Analysis of Algorithms (DAA)** implementing an optimal communication network layout using Kruskal's Minimum Spanning Tree (MST) algorithm in C++17.

---

## 1. Project Title & Overview
**Project Title**: Network Design Using Greedy Algorithms for Minimum Spanning Trees
**Course**: Design and Analysis of Algorithms (DAA)
**Algorithm**: Kruskal's Algorithm with Disjoint Set Union (DSU)
**Language**: C++17
**Lead Branch**: `Branch-5/testing-documentation`

In communication and telecommunication network design, stations, computers, or regional hubs must be interconnected with cables, optical fibers, or microwave links. Each link carries an associated capital expenditure (cost, distance, or latency). The objective is to interconnect all $V$ hubs into a unified connected network at the **minimum total cost** without creating circular dependencies (redundant cycles).

---

## 2. Problem Statement & Objectives
- **Problem Statement**: Given a connected, undirected, weighted graph $G = (V, E)$ where vertices represent network nodes and edges represent candidate communication links with non-negative weights $w(u, v)$, determine a subgraph $T \subseteq E$ connecting all vertices such that the total weight $\sum_{e \in T} w(e)$ is minimized and $T$ contains no cycles.
- **Objectives**:
  1. Build an efficient C++ application modeling communication networks.
  2. Implement Kruskal's greedy strategy combined with an optimized Disjoint Set Union (DSU) data structure.
  3. Validate input integrity (reject negative vertices, negative edge weights, invalid IDs, and non-numeric characters).
  4. Detect disconnected networks and avoid false spanning trees.
  5. Conduct automated unit and boundary tests covering all edge cases.

---

## 3. Group Member Responsibilities & Attribution

| Student | Assigned Component | Contributions & Implementation Files | Original Branch |
| :--- | :--- | :--- | :--- |
| **Student 1** | **Edge Structure** | Defined weighted edge representation and sorting comparator (`include/Edge.h`). | `origin/Branch-1/edge` |
| **Student 2** | **Disjoint Set Union (DSU)** | Implemented cycle detection using path compression and union by rank (`include/DSU.h`, `src/DSU.cpp`). | `origin/Branch-2` |
| **Student 3** | **Kruskal's Algorithm** | Implemented the greedy MST edge-selection engine, overflow-safe accumulation, and connectivity checking (`include/Kruskal.h`, `src/Kruskal.cpp`). | `origin/Branch-3/kruskal` |
| **Student 4** | **Input & Validation** | Built robust console/stream reading with bounds validation, error handling, and 1-based to 0-based coordinate normalization (`include/InputHandler.h`, `src/InputHandler.cpp`). | `origin/Branch-4` |
| **Student 5** | **Integration, Testing & Docs** | Project integration lead: resolved merge conflicts, built modular architecture, implemented 12-point automated test suite, wrote build automation, and authored complete documentation (`src/main.cpp`, `tests/test_suite.cpp`, `README.md`, `compile.bat`, `run_tests.bat`). | `Branch-5/testing-documentation` |

---

## 4. Algorithm Explanation & Greedy Strategy

Kruskal's algorithm relies on the **Greedy Choice Property** and **Optimal Substructure**:

1. **Greedy Choice Property**: A globally optimal spanning tree can be reached by continually selecting the locally optimal (cheapest) edge that does not violate the acyclic property.
2. **Algorithm Execution Flow**:
   - **Step 1 (Sort)**: Sort all edges in non-decreasing order of their weights: $w(e_1) \le w(e_2) \le \dots \le w(e_m)$.
   - **Step 2 (Initialize Sets)**: Place every vertex $v \in V$ into its own disjoint singleton set.
   - **Step 3 (Greedy Selection & Cycle Check)**: Iterate through sorted edges. For each edge $(u, v)$:
     - Query `DSU.find(u)` and `DSU.find(v)`.
     - If both roots are equal, adding $(u, v)$ creates a cycle $\rightarrow$ **discard edge**.
     - If roots differ, the edge bridges two separate components $\rightarrow$ **include edge in MST**, add weight to total cost, and call `DSU.unite(u, v)`.
   - **Step 4 (Termination)**: Terminate early as soon as $V - 1$ edges are selected.
   - **Step 5 (Connectivity Verification)**: If the loop finishes with fewer than $V - 1$ edges, the graph is disconnected; report that no spanning tree exists.

---

## 5. Data Structures & Efficiency Analysis

### Data Structures Used
- **`std::vector<Edge>`**: Efficient, contiguous storage for edge lists, permitting cache-friendly sorting via `std::sort`.
- **Disjoint Set Union (DSU)**:
  - **Path Compression**: During `find(x)`, recursively points every node directly to the root, reducing subsequent lookup costs.
  - **Union by Rank**: During `unite(u, v)`, attaches the shallower tree under the root of the deeper tree, keeping tree height bounded by $O(\log V)$.

### Asymptotic Complexity
- **Time Complexity**:
  - Edge Sorting: $O(E \log E)$. Since $E \le V^2$, $\log E \le 2 \log V$, which is $O(E \log V)$.
  - DSU Operations: $2E$ finds and at most $V - 1$ unions take $O(E \cdot \alpha(V))$, where $\alpha$ is the Inverse Ackermann function ($\alpha(V) < 5$ for all practical input sizes).
  - **Total Time Complexity**: $\mathbf{O(E \log E)}$ or $\mathbf{O(E \log V)}$.
- **Space Complexity**:
  - Edge storage: $O(E)$.
  - DSU structures (`parent` and `rank` vectors): $O(V)$.
  - **Total Auxiliary Space**: $\mathbf{O(V + E)}$.

---

## 6. Project Architecture

```text
DAA-assignment-/
â”œâ”€â”€ include/
â”‚   â”œâ”€â”€ Edge.h             # Student 1: Edge definition & comparator
â”‚   â”œâ”€â”€ DSU.h              # Student 2: Disjoint Set Union class declaration
â”‚   â”œâ”€â”€ Kruskal.h          # Student 3: Kruskal MST interface
â”‚   â””â”€â”€ InputHandler.h     # Student 4: User/stream input handling & validation
â”œâ”€â”€ src/
â”‚   â”œâ”€â”€ DSU.cpp            # Student 2: DSU path compression & union by rank
â”‚   â”œâ”€â”€ Kruskal.cpp        # Student 3: Kruskal algorithm engine & disconnect check
â”‚   â”œâ”€â”€ InputHandler.cpp   # Student 4: Stream/console input parser & index normalizer
â”‚   â””â”€â”€ main.cpp           # Student 5: Main integrated application driver
â”œâ”€â”€ tests/
â”‚   â””â”€â”€ test_suite.cpp     # Student 5: Formal 12-case automated test suite
â”œâ”€â”€ .gitignore             # Student 5: Excludes binaries and IDE build artifacts
â”œâ”€â”€ compile.bat            # Student 5: Windows build script (C++17)
â”œâ”€â”€ run_tests.bat          # Student 5: Windows automated test runner
â””â”€â”€ README.md              # Student 5: Comprehensive documentation
```

---

## 7. Compilation & Execution Guide

### Requirements
- Any C++17 compliant compiler (`g++` / MinGW-w64, Clang, or MSVC).

### Manual Compilation
```bash
# Compile integrated main program
g++ -std=c++17 -Wall -Wextra -Iinclude src/DSU.cpp src/Kruskal.cpp src/InputHandler.cpp src/main.cpp -o network_mst.exe

# Compile automated test suite
g++ -std=c++17 -Wall -Wextra -Iinclude src/DSU.cpp src/Kruskal.cpp src/InputHandler.cpp tests/test_suite.cpp -o test_suite.exe
```

### Windows Batch Scripts
- To compile the application: run `compile.bat`
- To compile and run all automated tests: run `run_tests.bat`

---

## 8. Sample Input and Execution

### Input
```text
6
9
1 2 4
1 3 4
2 3 2
3 4 3
3 6 2
3 5 4
4 5 3
6 5 3
2 4 1
```

### Output
```text
===============================================================
   DESIGN AND ANALYSIS OF ALGORITHMS - PROJECT 1
   Network Design Using Greedy Algorithm (Kruskal's MST)
===============================================================
 Contributors:
   Student 1: Edge Structure
   Student 2: Disjoint Set Union (DSU)
   Student 3: Kruskal's MST Algorithm
   Student 4: User Input & Graph Validation
   Student 5: Testing, Documentation, Integration Lead
===============================================================

[RESULT] Minimum Spanning Tree successfully generated:
Source      Destination     Cost (Weight)
---------------------------------------------------------------
2           4               1
2           3               2
3           6               2
4           5               3
1           2               4
---------------------------------------------------------------
Total Minimum Network Installation Cost: 12
Number of Network Links in MST: 5 (Expected V - 1 = 5)
===============================================================
```

---

## 9. Comprehensive Testing & Verification Results

All 12 required test cases were executed against the compiled C++17 binary:

| Test ID | Test Category | Input Configuration | Expected Output | Actual Output | Result |
| :---: | :--- | :--- | :--- | :--- | :---: |
| **1** | Normal connected graph | $V=6, E=9$ with varied weights | Total Cost = 12, $V-1=5$ edges | Total Cost = 12, 5 edges | **PASS** |
| **2** | Disconnected graph | $V=4, E=2$ (1-2 and 3-4 isolated) | Returns -1 (No MST exists) | Returned -1 | **PASS** |
| **3** | Cycle prevention | Triangle $V=3, E=3$ weights 1, 2, 3 | Skips edge (1,3); Cost = 3 | Cost = 3, 2 edges chosen | **PASS** |
| **4** | Single vertex | $V=1, E=0$ | Cost = 0, 0 edges | Cost = 0, 0 edges | **PASS** |
| **5** | Invalid vertex numbers | $V=4$, edge references vertex 9 | Input rejected with bounds error | Rejected invalid index | **PASS** |
| **6** | Negative vertex count | $V=-5, E=2$ | Input rejected ($V \le 0$) | Rejected negative vertices | **PASS** |
| **7** | Negative edge count | $V=4, E=-3$ | Input rejected ($E < 0$) | Rejected negative edges | **PASS** |
| **8** | Non-numeric input | `four 3` | Stream fail-bit caught & rejected | Rejected non-numeric input | **PASS** |
| **9** | Missing input values | Declared 2 edges, only 1 supplied | Detects incomplete stream | Detected missing values | **PASS** |
| **10** | Negative edge weights | Edge with weight -5 | Input rejected (non-negative required) | Rejected negative weight | **PASS** |
| **11** | Multiple components | $V=5, E=3$, vertex 5 isolated | Returns -1 (Incomplete spanning tree) | Returned -1 | **PASS** |
| **12** | Equal edge weights | Square $V=4, E=4$, all weights 5 | Picks any 3 edges, Cost = 15 | Cost = 15, 3 edges chosen | **PASS** |
