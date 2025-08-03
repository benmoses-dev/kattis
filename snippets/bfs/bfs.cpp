#include <queue>
#include <vector>

using namespace std;

/**
 * Generic BFS algorithm.
 * Tracks whether the graph has cycles or is bipartite, components, and shortest paths.
 */
bool adjBFS(const vector<vector<int>> &adj) {
    int n = adj.size();

    // Track state
    bool hasCycle = false;
    bool isBipartite = true;
    vector<int> prev(n, -1);
    vector<int> colours(n, -1);
    vector<int> distances(n, -1);

    // Assign component IDs
    int componentId = 0;
    vector<int> components(n, -1);

    /**
     * Remove the loop and pass in an index to only carry out a BFS from one starting node
     * instead of all nodes.
     */
    for (int i = 0; i < n; i++) {
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
                    prev[neighbour] = next;
                    q.push(neighbour);
                } else {
                    if (prev[next] != neighbour) {
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

/**
 * BFS on a grid. No need to track cycles.
 */
vector<vector<pair<int, int>>> gridBFS(const vector<vector<int>> &grid) {
    int r = grid.size();
    int c = grid[0].size();

    vector<vector<pair<int, int>>> prev(r, vector<pair<int, int>>(c));

    // Track state
    vector<vector<int>> colours(r, vector<int>(c, -1));
    vector<vector<int>> distances(r, vector<int>(c, -1));

    // Assign component IDs
    int componentId = 0;
    vector<vector<int>> components(r, vector<int>(c, -1));

    /**
     * Remove the loop and pass in an index to only carry out a BFS from one starting node
     * instead of all nodes.
     */
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (colours[i][j] != -1)
                continue;

            int dr[] = {-1, 1, 0, 0};
            int dc[] = {0, 0, -1, 1};

            prev[i][j] = {-1, -1};

            queue<pair<int, int>> q;
            q.push({i, j});
            colours[i][j] = 0;
            components[i][j] = componentId;
            distances[i][j] = 0;

            while (!q.empty()) {
                auto [row, col] = q.front();
                q.pop();
                for (int d = 0; d < 4; d++) {
                    int nr = dr[d] + row;
                    int nc = dc[d] + col;
                    if (nr < 0 || nr >= r)
                        continue;
                    if (nc < 0 || nc >= c)
                        continue;
                    if (colours[nr][nc] == -1) {
                        colours[nr][nc] = colours[row][col] ^ 1;
                        components[nr][nc] = componentId;
                        distances[nr][nc] = distances[row][col] + 1;
                        prev[nr][nc] = {row, col};
                        q.push({nr, nc});
                    }
                }
            }
            componentId++;
        }
    }

    return prev;
}
