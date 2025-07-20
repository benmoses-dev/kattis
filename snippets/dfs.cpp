#include <algorithm>
#include <vector>

using namespace std;

int timer;
int currentComponent;

/**
 * Store the results of the DFS.
 * This allows us to solve multiple different types of graph/tree traversal problems.
 */
struct DFSResult {
    bool hasCycle;          // Detect cycles in undirected or directed graphs.
    vector<int> parent;     // Used to recreate the path through the graph.
    vector<int> components; // Used for connectivity checks.
    vector<int> entry;      // Track the order of processing.
    vector<int> exit;       // Used to track ancestors.
    vector<int> topoOrder;  // Track post order and topological order of traversal.
    vector<int> low;        // Used to find the critical components of a graph.
    vector<int> articulationPoints; // Critical nodes in an undirected graph.
    vector<pair<int, int>> bridges; // Critical edges in an undirected graph.
    vector<vector<int>> sccs;       // Strongly-connected components in a directed graph.
};

void undirectedDfs(vector<vector<int>> &adj, vector<int> &visited, DFSResult &res, int u,
                   int p = -1) {
    /**
     * 0 = not visited
     * 1 = visiting
     */
    visited[u] = 1;

    res.parent[u] = p;
    res.components[u] = currentComponent; // Flood fill all nodes in the same DFS.

    // Detect bridges and articulation points
    res.entry[u] = res.low[u] = timer++;
    int children = 0;
    bool isArticulation = false;

    for (int v : adj[u]) {
        if (v == p) // Prevent infinite recursion.
            continue;

        if (visited[v] == 0) {
            undirectedDfs(adj, visited, res, v, u);
            res.low[u] = min(res.low[u], res.low[v]);

            if (res.low[v] > res.entry[u]) {
                res.bridges.emplace_back(u, v);
            }

            if (res.low[v] >= res.entry[u] && p != -1) {
                isArticulation = true;
            }

            children++;
        } else {
            res.low[u] = min(res.low[u], res.entry[v]);

            if (visited[v] == 1 && v != p) {
                // Back edge => cycle
                res.hasCycle = true;
            }
        }
    }

    // Root base case
    if (p == -1 && children > 1) {
        isArticulation = true;
    }

    if (isArticulation) {
        res.articulationPoints.push_back(u);
    }

    res.exit[u] = timer++;
    res.topoOrder.push_back(u);
}

void directedDfs(vector<vector<int>> &adj, vector<int> &visited, DFSResult &res, int u,
                 int p = -1) {
    /**
     * 0 = not visited
     * 1 = visiting
     * 2 = visited
     */
    visited[u] = 1;

    res.parent[u] = p;
    res.components[u] = currentComponent; // Flood fill all nodes in the same DFS.

    // Detect bridges and articulation points
    res.entry[u] = res.low[u] = timer++;
    int children = 0;

    for (int v : adj[u]) {
        if (v == p) // Prevent infinite recursion.
            continue;

        if (visited[v] == 0) {
            directedDfs(adj, visited, res, v, u);
            res.low[u] = min(res.low[u], res.low[v]);
            children++;
        } else {
            res.low[u] = min(res.low[u], res.entry[v]);

            if (visited[v] == 1 && v != p) {
                // Back edge => cycle
                res.hasCycle = true;
            }

            // If visited[v] == 2, it's a forward/cross edge
        }
    }

    visited[u] = 2; // Mark as finished
    res.exit[u] = timer++;
    res.topoOrder.push_back(u);
}

DFSResult runDFS(vector<vector<int>> &adj, bool isDirected = false) {
    int n = adj.size();

    DFSResult res;
    res.parent.assign(n, -1);
    res.components.assign(n, -1);
    res.entry.resize(n);
    res.exit.resize(n);
    res.low.resize(n);
    res.hasCycle = false;

    vector<int> visited(n, 0);
    timer = 0;
    currentComponent = 0;

    for (int u = 0; u < n; ++u) {
        if (!visited[u]) {
            if (isDirected) {
                directedDfs(adj, visited, res, u, -1);
            } else {
                undirectedDfs(adj, visited, res, u, -1);
            }
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
