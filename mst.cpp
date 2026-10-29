
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// STUDENT 1: Define the Edge structure
struct Edge {
    int source;
    int destination;
    int weight;
};

// STUDENT 2: Disjoint Set Union (DSU)
vector<int> parent;
vector<int> rankValue;

// Find the representative of a set
int find(int vertex) {
    if (parent[vertex] != vertex) {
        parent[vertex] = find(parent[vertex]);
    }
    return parent[vertex];
}

// Combine two sets
bool unite(int u, int v) {
    int rootU = find(u);
    int rootV = find(v);

    if (rootU == rootV) {
        return false;
    }

    if (rankValue[rootU] < rankValue[rootV]) {
        parent[rootU] = rootV;
    }
    else if (rankValue[rootU] > rankValue[rootV]) {
        parent[rootV] = rootU;
    }
    else {
        parent[rootV] = rootU;
        rankValue[rootU]++;
    }

    return true;
}

// STUDENT 3: Kruskal's Algorithm
void kruskal(vector<Edge>& edges, int vertices) {

    // Sort edges by increasing weight
    sort(edges.begin(), edges.end(),
         [](Edge a, Edge b) {
             return a.weight < b.weight;
         });

    parent.resize(vertices);
    rankValue.assign(vertices, 0);

    for (int i = 0; i < vertices; i++) {
        parent[i] = i;
    }

    vector<Edge> mst;
    int totalCost = 0;

    for (Edge edge : edges) {
        if (unite(edge.source, edge.destination)) {
            mst.push_back(edge);
            totalCost += edge.weight;

            if (mst.size() == vertices - 1) {
                break;
            }
        }
    }

    // STUDENT 5: Display the result
    if (mst.size() != vertices - 1) {
        cout << "\nThe network cannot connect all vertices.\n";
        return;
    }

    cout << "\nMinimum Spanning Tree (MST):\n";
    cout << "Selected Edges:\n";

    for (Edge edge : mst) {
        cout << edge.source << " - "
             << edge.destination
             << " : Cost = " << edge.weight << endl;
    }

    cout << "\nTotal Minimum Network Cost: "
         << totalCost << endl;
}

// STUDENT 4: Main function and input
int main() {
    int vertices, edgesCount;

    cout << "NETWORK DESIGN USING KRUSKAL'S ALGORITHM\n";

    cout << "Enter the number of vertices: ";
    cin >> vertices;

    cout << "Enter the number of edges: ";
    cin >> edgesCount;

    if (vertices <= 0 || edgesCount < 0) {
        cout << "Invalid number of vertices or edges.\n";
        return 1;
    }

    vector<Edge> edges;

    cout << "\nEnter each edge as: source destination weight\n";
    cout << "Use vertex numbers from 0 to "
         << vertices - 1 << ".\n";

    for (int i = 0; i < edgesCount; i++) {
        Edge edge;
        cin >> edge.source >> edge.destination >> edge.weight;

        if (edge.source < 0 || edge.source >= vertices ||
            edge.destination < 0 || edge.destination >= vertices ||
            edge.source == edge.destination || edge.weight < 0) {
            cout << "Invalid edge input.\n";
            return 1;
        }

        edges.push_back(edge);
    }

    kruskal(edges, vertices);

    return 0;
}
