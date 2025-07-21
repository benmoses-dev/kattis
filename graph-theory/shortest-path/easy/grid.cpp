#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

vector<int> bfs(vector<vector<int>> &adj, int start) {
    int n = adj.size();

    // Track state
    vector<int> colours(n, -1);
    vector<int> distances(n, -1);

    queue<int> q;
    q.push(start);
    colours[start] = 0;
    distances[start] = 0;

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
                distances[neighbour] = distances[next] + 1;
                q.push(neighbour);
            }
        }
    }

    return distances;
}

int main() {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    cin >> N >> M;
    cin.ignore();

    // Build up adjacency list (flattening it makes it slightly simpler).
    vector<vector<int>> adj(N * M, vector<int>(0));

    for (int n = 0; n < N; n++) {
        string line; // Read the line in as a whole, because they are being awkward.
        getline(cin, line);

        int m = 0; // Track the current column.

        for (char ch : line) {
            int num = (ch - '0'); // Convert the single digit to an int.
            if (num == 0) {       // Can we actually move?
                m++;
                continue;
            }

            int flattened = n * M + m;
            int dr[] = {0, 0, -num, num};
            int dc[] = {-num, num, 0, 0};

            for (int i = 0; i < 4; i++) {
                int nr = n + dr[i];
                int nc = m + dc[i];

                // Bounds check.
                if (nr < 0 || nr >= N)
                    continue;
                if (nc < 0 || nc >= M)
                    continue;

                int f = nr * M + nc;
                adj[flattened].push_back(f);
            }

            m++;
        }
    }

    // Carry out BFS and get the shortest path.
    vector<int> distances = bfs(adj, 0);
    int distance = distances[N * M - 1];
    cout << distance << endl;
    return 0;
}
