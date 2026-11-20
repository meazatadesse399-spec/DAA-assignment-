#include "InputHandler.h"
#include <iostream>

bool InputHandler::readFromStream(std::istream& in, GraphInput& outGraph) {
    int vertices = 0, edgeCount = 0;

    if (!(in >> vertices) || vertices <= 0) {
        std::cerr << "Error: Invalid number of vertices (must be > 0).\n";
        return false;
    }

    if (!(in >> edgeCount) || edgeCount < 0) {
        std::cerr << "Error: Invalid number of edges (must be >= 0).\n";
        return false;
    }

    outGraph.vertices = vertices;
    outGraph.edges.clear();
    outGraph.isOneIndexed = true; // User input default is 1-based indexing

    for (int i = 0; i < edgeCount; i++) {
        int u = 0, v = 0, w = 0;
        if (!(in >> u >> v >> w)) {
            std::cerr << "Error: Invalid edge input at edge " << (i + 1) << ".\n";
            return false;
        }

        // Check if endpoints are 1-based
        if (u < 1 || u > vertices || v < 1 || v > vertices) {
            std::cerr << "Error: Vertex index out of bounds [1, " << vertices << "] at edge ("
                      << u << ", " << v << ").\n";
            return false;
        }

        if (w < 0) {
            std::cerr << "Error: Negative edge weight is not allowed for network cost ("
                      << w << ").\n";
            return false;
        }

        // Normalize 1-based input to 0-based internal representation
        outGraph.edges.push_back(Edge(u - 1, v - 1, w));
    }

    return true;
}

bool InputHandler::readFromConsole(GraphInput& outGraph) {
    std::cout << "==========================================\n";
    std::cout << "  Network Design - Graph Input Setup      \n";
    std::cout << "==========================================\n";

    std::cout << "Enter number of vertices: ";
    int vertices = 0;
    if (!(std::cin >> vertices) || vertices <= 0) {
        std::cout << "Error: Invalid number of vertices!\n";
        return false;
    }

    std::cout << "Enter number of edges: ";
    int edgeCount = 0;
    if (!(std::cin >> edgeCount) || edgeCount < 0) {
        std::cout << "Error: Invalid number of edges!\n";
        return false;
    }

    outGraph.vertices = vertices;
    outGraph.edges.clear();
    outGraph.isOneIndexed = true;

    std::cout << "\nEnter each edge (source destination weight):\n";
    std::cout << "Note: Vertices are numbered 1 to " << vertices << "\n";

    for (int i = 0; i < edgeCount; i++) {
        int u = 0, v = 0, w = 0;
        std::cout << "Edge " << (i + 1) << ": ";
        if (!(std::cin >> u >> v >> w)) {
            std::cout << "Error: Invalid edge input format!\n";
            return false;
        }

        if (u < 1 || u > vertices || v < 1 || v > vertices) {
            std::cout << "Error: Vertex number must be between 1 and " << vertices << "!\n";
            return false;
        }

        if (w < 0) {
            std::cout << "Error: Negative weights are not permitted!\n";
            return false;
        }

        outGraph.edges.push_back(Edge(u - 1, v - 1, w));
    }

    return true;
}
