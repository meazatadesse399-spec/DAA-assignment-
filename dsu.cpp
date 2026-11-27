#include <iostream>
#include <vector>
using namespace std;

class DSU {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i == root_j) {
            return false; 
        }

        if (rank[root_i] < rank[root_j]) {
            parent[root_i] = root_j;
        } else if (rank[root_i] > rank[root_j]) {
            parent[root_j] = root_i;
        } else {
            parent[root_j] = root_i;
            rank[root_i]++;
        }
        return true;
    }

    void display(int n) {
        cout << "\nFinal Parent Array: ";
        for (int i = 0; i < n; i++) {
            cout << parent[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    int n = 6; 
    DSU dsu(n);

    cout << "--- Testing DSU Functions ---" << endl;
    cout << "Union(0, 1): " << (dsu.unite(0, 1) ? "Successful" : "Cycle") << endl;
    cout << "Union(1, 2): " << (dsu.unite(1, 2) ? "Successful" : "Cycle") << endl;
    cout << "Union(3, 4): " << (dsu.unite(3, 4) ? "Successful" : "Cycle") << endl;
    cout << "Union(0, 2): " << (dsu.unite(0, 2) ? "Successful" : "Cycle") << endl;
    dsu.display(n);

    return 0;
}