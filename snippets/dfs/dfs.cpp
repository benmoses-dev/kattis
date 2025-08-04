#include <algorithm>
#include <stack>
#include <vector>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

int timer;
int currentComponent;
int currSCC;

/**
 * Store the results of the DFS.
 * This allows us to solve multiple different types of graph/tree traversal problems.
 */
struct DFSResult {
    bool hasCycle;         // Detect cycles in undirected or directed graphs.
    vi parent;             // Used to recreate the path through the graph.
    vi components;         // Used for connectivity checks.
    vi entry;              // Track the order of processing.
    vi exit;               // Used to track ancestors.
    vi low;                // Used to find the critical components of a graph.
    vi postOrder;          // Track post order of traversal.
    vi articulationPoints; // Critical nodes in an undirected graph.
    vpii bridges;          // Critical edges in an undirected graph.
    vvi sccs;              // Strongly-connected components in a directed graph.
    stack<int> sccStack;   // Track current component stack.
    vector<bool> onStack;  // Tarjan's SCC algorithm.
    vi sccIndex;           // Component ID for each node in Tarjan's.
    vi topoOrder;          // Only useful in a DAG.
};

void undirectedDfs(vvi &adj, vi &visited, DFSResult &res, int u, int p = -1) {
    /**
     * 0 = not visited
     * 1 = visiting
     */
    visited[u] = 1;

    res.parent[u] = p;
    res.components[u] = currentComponent; // Flood fill all nodes in the same DFS.

    res.entry[u] = res.low[u] = timer++;
    int children = 0;
    bool isArticulation = false;

    for (int v : adj[u]) {
        if (v == p) // Don't go back up the edge.
            continue;

        if (visited[v] == 0) {
            undirectedDfs(adj, visited, res, v, u);
            // v has now been processed (and is a descendant) - use its low-link value.
            res.low[u] = min(res.low[u], res.low[v]);

            /**
             * If v cannot get back up to u (or above) via another path, this is a bridge.
             * Remove this edge disconnects the graph.
             */
            if (res.low[v] > res.entry[u]) {
                res.bridges.emplace_back(u, v);
            }

            /**
             * If v cannot get back above u, this is an articulation point (even if it
             * can get back to u). Removing this node disconnects the graph.
             */
            if (res.low[v] >= res.entry[u] && p != -1) {
                isArticulation = true;
            }

            children++;
        } else {
            /**
             * v is being processed (we are still recursing, so it doesn't have a low-link
             * value yet).
             * Use its entry time as the low-link for everything on this route.
             */
            res.low[u] = min(res.low[u], res.entry[v]);

            if (v != p) {
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

void directedDfs(vvi &adj, vi &visited, DFSResult &res, int u, int p = -1) {
    /**
     * 0 = not visited
     * 1 = visiting
     * We can track cycles using the stack.
     */
    visited[u] = 1;

    res.parent[u] = p;
    res.components[u] = currentComponent; // Track weakly connected components.

    // Detect bridges and articulation points
    res.entry[u] = res.low[u] = timer++;

    res.sccStack.push(u);
    res.onStack[u] = true;

    for (int v : adj[u]) {
        if (visited[v] == 0) {
            // Recurse and then update the low-link.
            directedDfs(adj, visited, res, v, u);
            res.low[u] = min(res.low[u], res.low[v]);
        } else if (res.onStack[v]) { // Currently being processed.
            res.low[u] = min(res.low[u], res.entry[v]);
            // Back edge => cycle
            res.hasCycle = true;
        }
        // Otherwise, it's a forward/cross edge
    }

    if (res.low[u] == res.entry[u]) {
        // Root of SCC - process all strongly connected components in this group.
        vi components;
        while (!res.sccStack.empty()) {
            int v = res.sccStack.top();
            res.sccStack.pop();
            res.onStack[v] = false;
            components.push_back(v);
            res.sccIndex[v] = currSCC; // Track strongly connected component IDs.
            if (v == u)                // We have reached the root.
                break;
        }
        res.sccs.push_back(components);
        currSCC++;
    }

    res.exit[u] = timer++;
    res.postOrder.push_back(u);
}

/**
 * DFS driver function. Pass isDirected depending on whether the graph is directed or not.
 */
DFSResult runDFS(vvi &adj, bool isDirected = false) {
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

    vi visited(n, 0);
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

    // If the graph is a DAG, we can get the topological order.
    if (isDirected && !res.hasCycle) {
        res.topoOrder = res.postOrder;
        reverse(res.topoOrder.begin(), res.topoOrder.end());
    }

    return res;
}

/**
 * Re-construct the recursion path using the parent vector.
 */
vi getPath(int u, DFSResult &res) {
    vi path;
    while (u != -1) {
        path.push_back(u);
        u = res.parent[u];
    }
    reverse(path.begin(), path.end());
    return path;
}

/**
 * Is u an ancestor of v?
 */
bool isAncestor(int u, int v, const DFSResult &res) {
    return (res.entry[u] <= res.entry[v]) && (res.exit[v] <= res.exit[u]);
}
