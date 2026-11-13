
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Edge structure
struct Edge
{
    int source;
    int destination;
    int weight;
};

struct DisjointSet
{
    vector<int> parent;
    vector<int> rank;

    explicit DisjointSet(int vertices) : parent(vertices + 1), rank(vertices + 1, 0)
    {
        for (int i = 0; i <= vertices; i++)
            parent[i] = i;
    }

    int find(int node)
    {
        if (parent[node] != node)
            parent[node] = find(parent[node]);
        return parent[node];
    }

    bool unite(int a, int b)
    {
        int rootA = find(a);
        int rootB = find(b);

        if (rootA == rootB)
            return false;

        if (rank[rootA] < rank[rootB])
            swap(rootA, rootB);

        parent[rootB] = rootA;
        if (rank[rootA] == rank[rootB])
            rank[rootA]++;
        return true;
    }
};

// Kruskal's algorithm for finding a Minimum Spanning Tree
void kruskal(vector<Edge> edges, int vertices)
{
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
         { return a.weight < b.weight; });

    DisjointSet sets(vertices);

    long long totalWeight = 0;
    vector<Edge> mst;

    for (const Edge &edge : edges)
    {
        if (sets.unite(edge.source, edge.destination))
        {
            mst.push_back(edge);
            totalWeight += edge.weight;

            if (mst.size() == static_cast<size_t>(vertices - 1))
                break;
        }
    }

    if (mst.size() != static_cast<size_t>(vertices - 1))
    {
        cout << "No spanning tree exists for this graph." << endl;
        return;
    }

    cout << "\nMinimum Spanning Tree edges:" << endl;
    for (const Edge &edge : mst)
    {
        cout << edge.source << " -- " << edge.destination << " : " << edge.weight << endl;
    }

    cout << "\nTotal MST weight: " << totalWeight << endl;
}

int main()
{
    int vertices, edgesCount;

    // Read number of vertices
    cout << "Enter the number of vertices: ";

    if (!(cin >> vertices) || vertices <= 0)
    {
        cout << "Error: Invalid number of vertices!" << endl;
        return 1;
    }

    // Read number of edges
    cout << "Enter the number of edges: ";

    if (!(cin >> edgesCount) || edgesCount < 0)
    {
        cout << "Error: Invalid number of edges!" << endl;
        return 1;
    }

    vector<Edge> edges;

    // Read each edge
    cout << "\nEnter edges (source destination weight):\n";

    for (int i = 0; i < edgesCount; i++)
    {
        int source, destination, weight;

        cout << "Edge " << i + 1 << ": ";

        if (!(cin >> source >> destination >> weight))
        {
            cout << "Error: Invalid edge input!" << endl;
            return 1;
        }

        // Validate vertex numbers
        if (source < 1 || source > vertices ||
            destination < 1 || destination > vertices)
        {

            cout << "Error: Invalid vertex number!" << endl;
            return 1;
        }

        // Validate weight
        if (weight < 0)
        {
            cout << "Error: Negative edge weight is not allowed!"
                 << endl;
            return 1;
        }

        Edge e;
        e.source = source;
        e.destination = destination;
        e.weight = weight;

        edges.push_back(e);
    }

    // Display input graph
    cout << "\nGraph successfully created!" << endl;
    cout << "\nVertices: " << vertices << endl;
    cout << "Edges: " << edgesCount << endl;

    // Call Kruskal's algorithm
    cout << "\nCalculating Minimum Spanning Tree...\n";

    kruskal(edges, vertices);

    return 0;
}
