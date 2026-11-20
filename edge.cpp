
#include <iostream>   // For input and output
#include <vector>     // For storing edges
#include <algorithm>  // For sorting edges
using namespace std;

// Define the Edge structure
struct Edge {
    int source;       // Starting vertex
    int destination;  // Ending vertex
    int weight;       // Cost of the connection
};

int main() {

    // Create example edges for testing
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    // Display the edges
    cout << "Network Edges:" << endl;

    for (size_t i = 0; i < edges.size(); i++) {
        cout << edges[i].source << " - "
             << edges[i].destination
             << " : Weight = "
             << edges[i].weight << endl;
    }

    return 0;
}
