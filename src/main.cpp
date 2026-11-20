#include <iostream>
#include <vector>
#include <iomanip>
#include "Edge.h"
#include "DSU.h"
#include "Kruskal.h"
#include "InputHandler.h"

// ============================================================
// Student 5: Integration Driver & Testing Program
// Integrates modules from Students 1, 2, 3, 4, 5
// ============================================================

void printBanner() {
    std::cout << "===============================================================\n";
    std::cout << "   DESIGN AND ANALYSIS OF ALGORITHMS - PROJECT 1               \n";
    std::cout << "   Network Design Using Greedy Algorithm (Kruskal's MST)       \n";
    std::cout << "===============================================================\n";
    std::cout << " Contributors:\n";
    std::cout << "   Student 1: Edge Structure\n";
    std::cout << "   Student 2: Disjoint Set Union (DSU)\n";
    std::cout << "   Student 3: Kruskal's MST Algorithm\n";
    std::cout << "   Student 4: User Input & Graph Validation\n";
    std::cout << "   Student 5: Testing, Documentation, Integration Lead\n";
    std::cout << "===============================================================\n\n";
}

int main() {
    printBanner();

    GraphInput graph;
    if (!InputHandler::readFromConsole(graph)) {
        std::cerr << "\nTerminating due to input error.\n";
        return 1;
    }

    std::cout << "\n---------------------------------------------------------------\n";
    std::cout << "Executing Kruskal's Minimum Spanning Tree Algorithm...\n";
    std::cout << "---------------------------------------------------------------\n";

    std::vector<Edge> mstEdges;
    long long totalCost = kruskalMST(graph.vertices, graph.edges, mstEdges);

    if (totalCost == -1) {
        std::cout << "\n[RESULT] Graph is DISCONNECTED!\n";
        std::cout << "No spanning tree exists because one or more communication nodes\n";
        std::cout << "cannot reach the rest of the network.\n";
        return 0;
    }

    std::cout << "\n[RESULT] Minimum Spanning Tree successfully generated:\n";
    std::cout << std::left << std::setw(12) << "Source"
              << std::setw(16) << "Destination"
              << "Cost (Weight)\n";
    std::cout << "---------------------------------------------------------------\n";

    for (const Edge& edge : mstEdges) {
        // Output back in 1-based indexing for user clarity
        int u = edge.source + 1;
        int v = edge.destination + 1;
        std::cout << std::left << std::setw(12) << u
                  << std::setw(16) << v
                  << edge.weight << "\n";
    }

    std::cout << "---------------------------------------------------------------\n";
    std::cout << "Total Minimum Network Installation Cost: " << totalCost << "\n";
    std::cout << "Number of Network Links in MST: " << mstEdges.size()
              << " (Expected V - 1 = " << (graph.vertices - 1) << ")\n";
    std::cout << "===============================================================\n";

    return 0;
}
