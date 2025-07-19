#include <queue>
#include <vector>

using namespace std;

/**
 * Generic BFS algorithm for an undirected graph.
 * Tracks whether the graph has cycles or is bipartite, components, and shortest paths.
 */
bool undirectedBfs(vector<vector<int>> &adj) {
    int n = adj.size();
    int start = 0;

    // Track state
    bool hasCycle = false;
    bool isBipartite = true;
    vector<int> parent(n, -1);
    vector<int> colours(n, -1);
    vector<int> distances(n, -1);

    // Assign component IDs
    int componentId = 0;
    vector<int> components(n, -1);

    for (int i = start; i < n; i++) {
        if (colours[i] != -1)
            continue;

        queue<int> q;
        q.push(i);
        colours[i] = 0;
        components[i] = componentId;
        distances[i] = 0;

        while (!q.empty()) {
            int next = q.front();
            q.pop();

            /**
             * Start a BFS through all neighbours.
             * If we get back to a node that has already been visited, we have a cycle.
             */
            for (const int &neighbour : adj[next]) {
                if (colours[neighbour] == -1) {
                    colours[neighbour] = colours[next] ^ 1;
                    components[neighbour] = componentId;
                    distances[neighbour] = distances[next] + 1;
                    parent[neighbour] = next;
                    q.push(neighbour);
                } else {
                    if (parent[next] != neighbour) {
                        hasCycle = true;
                        if (colours[next] == colours[neighbour]) {
                            isBipartite = false;
                        }
                    }
                }
            }
        }
        componentId++;
    }

    return hasCycle &&
           isBipartite; // Is there a cycle that is valid? Alter this as necessary.
}
