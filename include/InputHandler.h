#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <vector>
#include <string>
#include <istream>
#include "Edge.h"

// ============================================================
// Student 4: User Input & Graph Construction
// Handles user and stream input, validates vertex numbers and weights,
// and normalizes 1-based user input to 0-based internal indexing.
// ============================================================

struct GraphInput {
    int vertices;
    std::vector<Edge> edges;
    bool isOneIndexed;
};

class InputHandler {
public:
    // Read graph from standard input (interactive)
    static bool readFromConsole(GraphInput& outGraph);

    // Read graph from an input stream (for tests and automated runs)
    static bool readFromStream(std::istream& in, GraphInput& outGraph);
};

#endif // INPUT_HANDLER_H
