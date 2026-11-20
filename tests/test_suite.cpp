#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cassert>
#include "Edge.h"
#include "DSU.h"
#include "Kruskal.h"
#include "InputHandler.h"

// Struct to store results of each test case
struct TestCaseResult {
    int testId;
    std::string description;
    std::string input;
    std::string expected;
    std::string actual;
    bool passed;
};

std::vector<TestCaseResult> results;

void recordTest(int id, const std::string& desc, const std::string& input,
                const std::string& expected, const std::string& actual, bool passed) {
    results.push_back({id, desc, input, expected, actual, passed});
    std::cout << "Test " << id << " [" << desc << "]: "
              << (passed ? "PASS" : "FAIL") << "\n";
    if (!passed) {
        std::cout << "   Expected: " << expected << "\n";
        std::cout << "   Actual:   " << actual << "\n";
    }
}

// 1. Normal connected graph
void test1_NormalConnected() {
    std::string input = "6 9\n1 2 4\n1 3 4\n2 3 2\n3 4 3\n3 6 2\n3 5 4\n4 5 3\n6 5 3\n2 4 1\n";
    std::stringstream ss(input);
    GraphInput g;
    bool ok = InputHandler::readFromStream(ss, g);
    std::vector<Edge> mst;
    long long cost = kruskalMST(g.vertices, g.edges, mst);

    bool pass = ok && (cost == 12) && (mst.size() == 5);
    std::string actual = "Cost=" + std::to_string(cost) + ", Edges=" + std::to_string(mst.size());
    recordTest(1, "Normal connected graph", input, "Cost=12, Edges=5 (V-1)", actual, pass);
}

// 2. Disconnected graph
void test2_Disconnected() {
    std::string input = "4 2\n1 2 10\n3 4 20\n";
    std::stringstream ss(input);
    GraphInput g;
    bool ok = InputHandler::readFromStream(ss, g);
    std::vector<Edge> mst;
    long long cost = kruskalMST(g.vertices, g.edges, mst);

    bool pass = ok && (cost == -1);
    std::string actual = "Return=" + std::to_string(cost) + " (Disconnected)";
    recordTest(2, "Disconnected graph", input, "Return=-1 (Disconnected)", actual, pass);
}

// 3. Cycle prevention
void test3_CyclePrevention() {
    // Triangle graph: 1-2 (1), 2-3 (2), 1-3 (3).
    // Greedy should pick 1-2 and 2-3, and skip 1-3 to prevent cycle.
    std::string input = "3 3\n1 2 1\n2 3 2\n1 3 3\n";
    std::stringstream ss(input);
    GraphInput g;
    InputHandler::readFromStream(ss, g);
    std::vector<Edge> mst;
    long long cost = kruskalMST(g.vertices, g.edges, mst);

    bool pass = (cost == 3) && (mst.size() == 2);
    std::string actual = "Cost=" + std::to_string(cost) + ", Edges=" + std::to_string(mst.size());
    recordTest(3, "Cycle prevention", input, "Cost=3, Edges=2 (Skip cycle edge)", actual, pass);
}

// 4. Single vertex
void test4_SingleVertex() {
    std::string input = "1 0\n";
    std::stringstream ss(input);
    GraphInput g;
    bool ok = InputHandler::readFromStream(ss, g);
    std::vector<Edge> mst;
    long long cost = kruskalMST(g.vertices, g.edges, mst);

    bool pass = ok && (cost == 0) && (mst.empty());
    std::string actual = "Cost=" + std::to_string(cost) + ", Edges=" + std::to_string(mst.size());
    recordTest(4, "Single vertex", input, "Cost=0, Edges=0", actual, pass);
}

// 5. Invalid vertex numbers
void test5_InvalidVertexNumbers() {
    // Vertices is 4, but edge references vertex 9
    std::string input = "4 1\n1 9 10\n";
    std::stringstream ss(input);
    GraphInput g;
    bool ok = InputHandler::readFromStream(ss, g);

    bool pass = !ok;
    std::string actual = ok ? "Accepted invalid vertex" : "Rejected invalid vertex";
    recordTest(5, "Invalid vertex numbers", input, "Rejected invalid vertex", actual, pass);
}

// 6. Negative vertex count
void test6_NegativeVertexCount() {
    std::string input = "-5 2\n1 2 10\n";
    std::stringstream ss(input);
    GraphInput g;
    bool ok = InputHandler::readFromStream(ss, g);

    bool pass = !ok;
    std::string actual = ok ? "Accepted negative vertices" : "Rejected negative vertices";
    recordTest(6, "Negative vertex count", input, "Rejected negative vertices", actual, pass);
}

// 7. Negative edge count
void test7_NegativeEdgeCount() {
    std::string input = "4 -3\n";
    std::stringstream ss(input);
    GraphInput g;
    bool ok = InputHandler::readFromStream(ss, g);

    bool pass = !ok;
    std::string actual = ok ? "Accepted negative edge count" : "Rejected negative edge count";
    recordTest(7, "Negative edge count", input, "Rejected negative edge count", actual, pass);
}

// 8. Non-numeric input
void test8_NonNumericInput() {
    std::string input = "four 3\n1 2 10\n";
    std::stringstream ss(input);
    GraphInput g;
    bool ok = InputHandler::readFromStream(ss, g);

    bool pass = !ok;
    std::string actual = ok ? "Accepted non-numeric" : "Rejected non-numeric input";
    recordTest(8, "Non-numeric input", input, "Rejected non-numeric input", actual, pass);
}

// 9. Missing input values
void test9_MissingInputValues() {
    // Declared 2 edges, but only 1 provided
    std::string input = "3 2\n1 2 5\n";
    std::stringstream ss(input);
    GraphInput g;
    bool ok = InputHandler::readFromStream(ss, g);

    bool pass = !ok;
    std::string actual = ok ? "Accepted missing values" : "Detected missing input values";
    recordTest(9, "Missing input values", input, "Detected missing input values", actual, pass);
}

// 10. Negative edge weights
void test10_NegativeEdgeWeights() {
    std::string input = "3 2\n1 2 -5\n2 3 4\n";
    std::stringstream ss(input);
    GraphInput g;
    bool ok = InputHandler::readFromStream(ss, g);

    bool pass = !ok;
    std::string actual = ok ? "Accepted negative weight" : "Rejected negative edge weight";
    recordTest(10, "Negative edge weights", input, "Rejected negative edge weight", actual, pass);
}

// 11. Multiple connected components (isolated node 5)
void test11_MultipleComponents() {
    // 5 vertices, but vertex 5 is completely isolated
    std::string input = "5 3\n1 2 2\n2 3 3\n3 4 4\n";
    std::stringstream ss(input);
    GraphInput g;
    InputHandler::readFromStream(ss, g);
    std::vector<Edge> mst;
    long long cost = kruskalMST(g.vertices, g.edges, mst);

    bool pass = (cost == -1);
    std::string actual = "Cost=" + std::to_string(cost) + " (Disconnected)";
    recordTest(11, "Multiple connected components", input, "Cost=-1 (Disconnected graph)", actual, pass);
}

// 12. Graph with equal edge weights
void test12_EqualWeights() {
    // Square graph where all 4 edges have weight 5
    // Any spanning tree must choose exactly 3 edges (cost = 15)
    std::string input = "4 4\n1 2 5\n2 3 5\n3 4 5\n4 1 5\n";
    std::stringstream ss(input);
    GraphInput g;
    InputHandler::readFromStream(ss, g);
    std::vector<Edge> mst;
    long long cost = kruskalMST(g.vertices, g.edges, mst);

    bool pass = (cost == 15) && (mst.size() == 3);
    std::string actual = "Cost=" + std::to_string(cost) + ", Edges=" + std::to_string(mst.size());
    recordTest(12, "Graph with equal edge weights", input, "Cost=15, Edges=3", actual, pass);
}

int main() {
    std::cout << "===============================================================\n";
    std::cout << "   RUNNING FORMAL 12-POINT VERIFICATION SUITE (STUDENT 5)      \n";
    std::cout << "===============================================================\n";

    test1_NormalConnected();
    test2_Disconnected();
    test3_CyclePrevention();
    test4_SingleVertex();
    test5_InvalidVertexNumbers();
    test6_NegativeVertexCount();
    test7_NegativeEdgeCount();
    test8_NonNumericInput();
    test9_MissingInputValues();
    test10_NegativeEdgeWeights();
    test11_MultipleComponents();
    test12_EqualWeights();

    std::cout << "===============================================================\n";
    int passCount = 0;
    for (const auto& r : results) {
        if (r.passed) passCount++;
    }
    std::cout << "SUMMARY: " << passCount << " / " << results.size()
              << " TEST CASES PASSED.\n";
    std::cout << "===============================================================\n";

    return (passCount == (int)results.size()) ? 0 : 1;
}
