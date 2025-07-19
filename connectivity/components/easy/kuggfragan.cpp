#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/**
 * Walk the adjacency list and check that all adjoining nodes have a different rotation
 */
int main() {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    cin >> N >> M;

    vector<vector<int>> adj(N, vector<int>(0));
    vector<int> rotation(N, -1); // -1 for unvisited, due to undirected graph

    for (int m = 0; m < M; m++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    /**
     * Process all connected graphs in turn.
     * Fail at the first odd-numbered cycle.
     */
    for (int i = 0; i < N; i++) {
        if (rotation[i] != -1)
            continue;
        queue<int> q;
        q.push(i);
        rotation[i] = 0;
        while (!q.empty()) {
            int next = q.front();
            q.pop();
            for (const int &neighbour : adj[next]) {
                /**
                 * Start a BFS through all neighbours.
                 * If we get back to a gear that already has a rotation, we have a cycle.
                 * We then need to check whether it has a different rotation.
                 * If it has the same rotation, The cycle has an odd number of gears.
                 */
                if (rotation[neighbour] == -1) {
                    rotation[neighbour] = rotation[next] ^ 1;
                    q.push(neighbour);
                } else {
                    // We have a cycle
                    if (rotation[next] == rotation[neighbour]) {
                        cout << "no way" << endl;
                        return 0;
                    }
                }
            }
        }
    }

    cout << "attend here" << endl;
    return 0;
}
