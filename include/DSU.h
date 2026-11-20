#ifndef DSU_H
#define DSU_H

#include <vector>

// ============================================================
// Student 2: Disjoint Set Union (DSU) Data Structure
// Cycle detection via path compression and union by rank
// ============================================================

class DisjointSet {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    // Initialize DSU for V vertices (0 to V-1)
    explicit DisjointSet(int vertices);

    // Find root representative with path compression
    int find(int node);

    // Unite two subsets by rank. Returns true if merged, false if already in same set
    bool unite(int u, int v);
};

#endif // DSU_H
