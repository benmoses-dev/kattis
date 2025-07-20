#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

int timer;
int currentComponent;
int currSCC;

/**
 * Store the results of the DFS.
 * This allows us to solve multiple different types of graph/tree traversal problems.
 */
struct DFSResult {
    bool hasCycle;                  // Detect cycles in undirected or directed graphs.
    vector<int> parent;             // Used to recreate the path through the graph.
    vector<int> components;         // Used for connectivity checks.
    vector<int> entry;              // Track the order of processing.
    vector<int> exit;               // Used to track ancestors.
    vector<int> low;                // Used to find the critical components of a graph.
    vector<int> postOrder;          // Track post order of traversal.
    vector<int> articulationPoints; // Critical nodes in an undirected graph.
    vector<pair<int, int>> bridges; // Critical edges in an undirected graph.
    vector<vector<int>> sccs;       // Strongly-connected components in a directed graph.
    stack<int> sccStack;            // Track current component stack.
    vector<bool> onStack;           // Tarjan's SCC algorithm.
    vector<int> sccIndex;           // Component ID for each node in Tarjan's.
    vector<int> topoOrder;          // Only useful in a DAG.
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
        if (v == p) // Don't go back up the edge.
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
    res.postOrder.push_back(u);
}

void directedDfs(vector<vector<int>> &adj, vector<int> &visited, DFSResult &res, int u,
                 int p = -1) {
    /**
     * 0 = not visited
     * 1 = visiting
     * We can track cycles using the stack.
     */
    visited[u] = 1;

    res.parent[u] = p;
    res.components[u] = currentComponent; // Flood fill all nodes in the same DFS.

    // Detect bridges and articulation points
    res.entry[u] = res.low[u] = timer++;

    res.sccStack.push(u);
    res.onStack[u] = true;

    for (int v : adj[u]) {
        if (visited[v] == 0) {
            directedDfs(adj, visited, res, v, u);
            res.low[u] = min(res.low[u], res.low[v]);
        } else if (res.onStack[v]) {
            res.low[u] = min(res.low[u], res.entry[v]);
            // Back edge => cycle
            res.hasCycle = true;
        }
        // It's a forward/cross edge
    }

    if (res.low[u] == res.entry[u]) {
        // Root of SCC
        vector<int> components;
        while (!res.sccStack.empty()) {
            int v = res.sccStack.top();
            res.sccStack.pop();
            res.onStack[v] = false;
            components.push_back(v);
            res.sccIndex[v] = currSCC;
            if (v == u)
                break;
        }
        res.sccs.push_back(components);
        currSCC++;
    }

    res.exit[u] = timer++;
    res.postOrder.push_back(u);
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

    res.onStack.assign(n, false);
    res.sccIndex.assign(n, -1);
    currSCC = 0;

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

    if (isDirected && !res.hasCycle) {
        res.topoOrder = res.postOrder;
        reverse(res.topoOrder.begin(), res.topoOrder.end());
    }
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
