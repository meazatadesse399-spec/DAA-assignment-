#include <iostream>
#include <vector>
using namespace std;

// Define the Edge structure
struct Edge {
    int source;       // Starting vertex
    int destination;  // Ending vertex
    int weight;       // Cost of the connection

    Edge(int source, int destination, int weight)
        : source(source), destination(destination), weight(weight) {}
};

// Store all edges of the graph
vector<Edge> edges;

int main() {

    // Example communication network
    edges.push_back(Edge(0, 1, 10));
    edges.push_back(Edge(0, 2, 6));
    edges.push_back(Edge(0, 3, 5));
    edges.push_back(Edge(1, 3, 15));
    edges.push_back(Edge(2, 3, 4));

    // Display the edges
    cout << "Communication Network Edges:\n";

    for (size_t i = 0; i < edges.size(); ++i) {
        const Edge& edge = edges[i];
        cout << edge.source << " - "
             << edge.destination
             << " : Cost = " << edge.weight << endl;
    }

    return 0;
}