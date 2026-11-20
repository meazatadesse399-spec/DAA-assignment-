#include "Kruskal.h"
#include "DSU.h"
#include <algorithm>

long long kruskalMST(int V, const std::vector<Edge>& edges, std::vector<Edge>& mstEdges) {
    mstEdges.clear();

    if (V <= 0) return 0;
    if (V == 1) return 0; // Single vertex requires 0 edges

    // Step 1: Sort a copy of edges in ascending order of weight
    std::vector<Edge> sortedEdges = edges;
    std::sort(sortedEdges.begin(), sortedEdges.end());

    DisjointSet dsu(V);
    long long totalCost = 0;
    int edgesCount = 0;

    // Step 2 & 3: Greedily pick cheapest edges that do not form a cycle
    for (const Edge& edge : sortedEdges) {
        if (edgesCount == V - 1) {
            break;
        }

        // Validate endpoints
        if (edge.source < 0 || edge.source >= V ||
            edge.destination < 0 || edge.destination >= V) {
            continue;
        }

        if (dsu.unite(edge.source, edge.destination)) {
            mstEdges.push_back(edge);
            totalCost += edge.weight;
            edgesCount++;
        }
    }

    // Step 4: Verify connectivity (MST must contain V - 1 edges)
    if (edgesCount != V - 1) {
        return -1; // Disconnected graph: no spanning tree exists
    }

    return totalCost;
}
