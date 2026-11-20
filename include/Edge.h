#ifndef EDGE_H
#define EDGE_H

// ============================================================
// Student 1: Edge Structure
// Defines communication links with endpoints and cost (weight)
// ============================================================

struct Edge {
    int source;       // Starting vertex (0-based)
    int destination;  // Ending vertex (0-based)
    int weight;       // Cost / latency / cable length

    Edge() : source(0), destination(0), weight(0) {}
    Edge(int s, int d, int w) : source(s), destination(d), weight(w) {}

    // Comparator for sorting edges in ascending order of weight
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

#endif // EDGE_H
