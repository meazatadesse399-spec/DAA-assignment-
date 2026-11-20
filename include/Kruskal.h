#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <vector>
#include "Edge.h"

// ============================================================
// Student 3: Kruskal's Algorithm (Greedy MST)
// Sorts edges by weight, selects non-cycle edges using DSU,
// stops at V - 1 edges, and computes minimum total cost.
// ============================================================

/**
 * Runs Kruskal's algorithm on a graph with V vertices.
 * @param V Number of vertices (0 to V-1)
 * @param edges Input edge list
 * @param mstEdges Output parameter to receive edges chosen in the MST
 * @return Total minimum cost, or -1 if graph is disconnected
 */
long long kruskalMST(int V, const std::vector<Edge>& edges, std::vector<Edge>& mstEdges);

#endif // KRUSKAL_H
