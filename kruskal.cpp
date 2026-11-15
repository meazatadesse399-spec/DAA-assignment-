// ============================================================
// Branch 3: kruskal-algorithm
// Task: Implement the main greedy algorithm (Kruskal's MST)
//   - Sort edges in ascending order of weight
//   - Select the cheapest edge that does not create a cycle
//   - Stop when V - 1 edges have been selected
//   - Calculate the total minimum network cost
// File: kruskal.cpp
//
// NOTE: The Edge struct (Branch 1) and DSU (Branch 2) are
// included here ONLY so this file compiles and runs standalone.
// When merging into mst.cpp, replace them with the versions
// from the edge-structure and dsu-functions branches.
// ============================================================

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ---------- From Branch 1: edge-structure ----------
// A weighted graph stores communication links as edges.
// Each edge connects two vertices (source -> destination)
// and carries a weight, which represents the cost of that
// link (e.g. cable length, latency, or money).
struct Edge {
    int source;
    int destination;
    int weight;
};

// ---------- From Branch 2: dsu-functions ----------
// The Disjoint Set Union (DSU) tracks which vertices belong
// to the same connected component. Before adding an edge we
// check with find(): if both endpoints are already in the
// same set, the edge would close a cycle and must be skipped.
// This is how DSU prevents cycles in the network.

int find(vector<int>& parent, int x) {
    // Path compression: flatten the tree while searching,
    // so future find() calls run in nearly constant time.
    if (parent[x] != x)
        parent[x] = find(parent, parent[x]);
    return parent[x];
}

void unite(vector<int>& parent, vector<int>& rank_, int a, int b) {
    int rootA = find(parent, a);
    int rootB = find(parent, b);
    if (rootA == rootB) return;

    // Union by rank: attach the shorter tree under the taller
    // one to keep the trees shallow.
    if (rank_[rootA] < rank_[rootB]) {
        parent[rootA] = rootB;
    } else if (rank_[rootA] > rank_[rootB]) {
        parent[rootB] = rootA;
    } else {
        parent[rootB] = rootA;
        rank_[rootA]++;
    }
}

// ============================================================
// ============ BRANCH 3 SECTION: KRUSKAL ALGORITHM ===========
// ============================================================

// Kruskal's greedy algorithm:
// 1. Sort all edges by weight (ascending).
// 2. Walk through the sorted edges and greedily take the
//    cheapest edge that connects two DIFFERENT components
//    (i.e. does not create a cycle - checked with DSU).
// 3. Stop as soon as V - 1 edges have been selected, because
//    a spanning tree of V vertices has exactly V - 1 edges.
// 4. Return the total cost, which is the minimum possible
//    cost to connect the whole network.
//
// Returns -1 when the graph is disconnected (some vertex has
// no way to reach the others), because in that case no
// spanning tree exists at all.
//
// Notes:
// - The caller's edge list is NOT modified: we sort a copy.
// - Endpoints must be in the range 0 .. V-1; invalid edges
//   are skipped so they cannot cause out-of-bounds access.
// - totalCost is long long so big weights cannot overflow.
long long kruskalMST(int V, const vector<Edge>& edges, vector<Edge>& mstEdges) {
    mstEdges.clear(); // start fresh, ignore any old results

    // Step 1: sort a COPY of the edges in ascending order of weight
    vector<Edge> sortedEdges = edges;
    sort(sortedEdges.begin(), sortedEdges.end(),
         [](const Edge& a, const Edge& b) {
             return a.weight < b.weight;
         });

    vector<int> parent(V), rank_(V, 0);
    for (int i = 0; i < V; i++) parent[i] = i;

    long long totalCost = 0;
    int edgesUsed = 0;

    // Step 2 & 3: pick cheapest non-cycle edges until V - 1 chosen
    for (const Edge& e : sortedEdges) {
        if (edgesUsed == V - 1)
            break; // spanning tree complete

        // Ignore edges with invalid vertex ids (outside 0 .. V-1)
        if (e.source < 0 || e.source >= V ||
            e.destination < 0 || e.destination >= V) {
            continue;
        }

        int rootSource = find(parent, e.source);
        int rootDest   = find(parent, e.destination);

        // If the roots differ, adding this edge cannot create a cycle
        if (rootSource != rootDest) {
            unite(parent, rank_, rootSource, rootDest);
            totalCost += e.weight;
            mstEdges.push_back(e);
            edgesUsed++;
        }
        // else: both endpoints already connected -> cycle -> skip
    }

    // Step 4: check the graph was actually connected
    if (edgesUsed != V - 1)
        return -1; // some vertex is cut off from the network

    return totalCost; // the minimum network cost
}

// ============================================================
// ================== END OF BRANCH 3 SECTION =================
// ============================================================

int main() {
    // Example network: 6 vertices, 9 weighted links
    // (same graph used for testing the whole project)
    int V = 6;
    vector<Edge> edges = {
        {0, 1, 4},
        {0, 2, 4},
        {1, 2, 2},
        {2, 3, 3},
        {2, 5, 2},
        {2, 4, 4},
        {3, 4, 3},
        {5, 4, 3},
        {1, 3, 1}
    };

    vector<Edge> mstEdges;
    long long totalCost = kruskalMST(V, edges, mstEdges);

    if (totalCost == -1) {
        cout << "The network is disconnected - some towns cannot be "
             << "reached, so no spanning tree exists." << endl;
        return 1;
    }

    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (const Edge& e : mstEdges) {
        cout << "  " << e.source << " - " << e.destination
             << "  (cost " << e.weight << ")" << endl;
    }
    cout << "Total minimum network cost: " << totalCost << endl;

    return 0;
}
