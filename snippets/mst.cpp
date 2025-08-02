#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

struct Edge {
    int u, v, w;

    bool operator<(const Edge &other) const { return w < other.w; }
};

struct DSU {
    vector<int> parents;
    vector<int> size;
    int numComponents;

    DSU(const int n) {
        parents.resize(n);
        iota(parents.begin(), parents.end(), 0);
        size.assign(n, 1);
        numComponents = n;
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
        numComponents--;
        return true;
    }

    int getSize(int i) { return size[find(i)]; }

    int getComponents() { return numComponents; }
};

// Find the minimum spanning tree using Kruskal's (edge-based)

vector<Edge> mst(vector<Edge> edges, int n) {
    DSU dsu(n);
    vector<Edge> mst;
    sort(edges.begin(), edges.end());
    int count = 0;
    for (const auto &edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            mst.push_back(edge);
            if (++count == n - 1)
                break;
        }
    }
    return mst;
}

int main() {
    int n;
    cin >> n;
    vector<Edge> edges;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int w;
            cin >> w;
            if (j > i) {
                edges.push_back({i, j, w});
            }
        }
    }
    vector<Edge> minTree = mst(edges, n);
    return 0;
}
