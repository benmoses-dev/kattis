#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Find the minimum spanning tree using Kruskal's (edge-based)

vector<int> parents; // DSU

struct Edge {
    int u, v, w;

    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

int find(int x) {
    if (parents[x] != x) {
        parents[x] = find(parents[x]);
    }
    return parents[x];
}

bool unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY) return false;
    parents[rootX] = rootY;
    return true;
}

int main() {
    int n;
    cin >> n;
    vector<Edge> edges;
    parents.resize(n + 1); for (int i = 1; i <= n; i++) parents[i] = i;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int u = min(i, j);
            int v = max(i, j); // Avoid duplicates in a symmetrical graph (make it directed)
            int w;
            cin >> w;
            Edge e;
            e.u = u;
            e.v = v;
            e.w = w;
            edges.push_back(e);
        }
    }

    sort(edges.begin(), edges.end());
    int count = 0;

    for (const auto& edge : edges) {
        if (unite(edge.u, edge.v)) {
            count++;
            cout << edge.u << " " << edge.v << "\n";
            if (count == n - 1) break;
        }
    }

    return 0;
}
