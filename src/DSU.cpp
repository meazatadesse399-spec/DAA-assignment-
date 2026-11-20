#include "DSU.h"
#include <utility>

DisjointSet::DisjointSet(int vertices) : parent(vertices), rank(vertices, 0) {
    for (int i = 0; i < vertices; i++) {
        parent[i] = i;
    }
}

int DisjointSet::find(int node) {
    if (parent[node] != node) {
        // Path compression
        parent[node] = find(parent[node]);
    }
    return parent[node];
}

bool DisjointSet::unite(int u, int v) {
    int rootA = find(u);
    int rootB = find(v);

    if (rootA == rootB) {
        return false; // Already in the same set, would form a cycle
    }

    // Union by rank
    if (rank[rootA] < rank[rootB]) {
        std::swap(rootA, rootB);
    }
    parent[rootB] = rootA;
    if (rank[rootA] == rank[rootB]) {
        rank[rootA]++;
    }
    return true;
}
