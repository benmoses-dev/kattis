#include <algorithm>
#include <vector>

using namespace std;

int timer;
int currentComponent;

struct DFSResult {
    bool hasCycle;
    vector<int> components;
    vector<int> entry;
    vector<int> exit;
    vector<int> parent;
    vector<int> topoOrder;
};

void dfs(vector<vector<int>> &adj, vector<int> &visited, DFSResult &res, int u,
         int p = -1, bool isDirected = true) {
    visited[u] = 1; // mark as visiting
    res.parent[u] = p;
    res.components[u] = currentComponent;
    res.entry[u] = timer++;

    for (int v : adj[u]) {
        if (visited[v] == 0) {
            dfs(adj, visited, res, v, u, isDirected);
        } else if (visited[v] == 1) {
            if (isDirected || v != p) {
                // Back edge => cycle
                res.hasCycle = true;
            }
        }
        // if visited[v] == 2, it's a forward/cross edge
    }

    visited[u] = 2; // mark as finished
    res.exit[u] = timer++;
    res.topoOrder.push_back(u);
}

DFSResult runDFS(vector<vector<int>> &adj, bool isDirected) {
    int n = adj.size();

    DFSResult res;
    res.parent.assign(n, -1);
    res.components.assign(n, -1);
    res.entry.resize(n);
    res.exit.resize(n);
    res.hasCycle = false;

    vector<int> visited(n, 0);
    timer = 0;
    currentComponent = 0;

    for (int u = 0; u < n; ++u) {
        if (!visited[u]) {
            dfs(adj, visited, res, u, -1, isDirected);
            currentComponent++;
        }
    }

    reverse(res.topoOrder.begin(), res.topoOrder.end());
    return res;
}

vector<int> getPath(int u, DFSResult &res) {
    vector<int> path;
    while (u != -1) {
        path.push_back(u);
        u = res.parent[u];
    }
    reverse(path.begin(), path.end());
    return path;
}

bool isAncestor(int u, int v, const DFSResult &res) {
    return (res.entry[u] <= res.entry[v]) && (res.exit[v] <= res.exit[u]);
}
