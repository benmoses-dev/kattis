#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

struct Edge {
    int u, v, w;

    bool operator<(const Edge &other) const { return w < other.w; }
};

struct DSU {
    vector<int> parents;
    vector<int> size;

    DSU(const int n) {
        parents.resize(n);
        iota(parents.begin(), parents.end(), 0);
        size.assign(n, 1);
    }

    int find(int x) {
        if (parents[x] != x)
            parents[x] = find(parents[x]);
        return parents[x];
    }

    bool unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA == rootB)
            return false;
        if (size[rootA] < size[rootB]) {
            swap(rootA, rootB);
        }
        parents[rootB] = rootA;
        size[rootA] += size[rootB];
        return true;
    }
};

// Find the minimum spanning tree using Kruskal's (edge-based)

int mst(vector<Edge> &tree, vector<Edge> edges, int n) {
    DSU dsu(n);
    sort(edges.begin(), edges.end());
    int count = 0;
    int unlikeliness = 0;
    for (const auto &edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            tree.push_back(edge);
            unlikeliness += edge.w;
            if (++count == n - 1)
                break;
        }
    }
    return unlikeliness;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;

    vector<string> dna(n);
    for (int i = 0; i < n; i++) {
        cin >> dna[i];
    }

    vector<Edge> edges;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int w = 0;
            string a = dna[i];
            string b = dna[j];
            for (int x = 0; x < k; x++) {
                if (a[x] != b[x])
                    w++;
            }
            if (j > i) {
                edges.push_back({i, j, w});
            }
        }
    }

    vector<Edge> minTree;
    int unlikeliness = mst(minTree, edges, n);
    cout << unlikeliness << endl;
    for (const Edge edge : minTree) {
        cout << edge.u << " " << edge.v << endl;
    }

    return 0;
}
