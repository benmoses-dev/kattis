#include <climits>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;
using pii = pair<int, int>;
using vpii = vector<pii>;
using vvpii = vector<vpii>;
using vi = vector<int>;
using vvi = vector<vi>;
using tiii = tuple<int, int, int>;

void dijkstra(vvpii &adjacencyList, vi &prev, int start, int n) {
    // Initialise distances
    vi distances(n, INT_MAX);

    // Queue of pair<distance, index> sorted by smallest distance
    priority_queue<pii, vpii, greater<pii>> pq;
    pq.push({0, start});

    distances[start] = 0;
    prev[start] = -1;

    while (!pq.empty()) {
        auto [d, i] = pq.top();
        pq.pop();
        if (d > distances[i])
            continue; // Stale value on queue

        // Process neighbours
        for (const auto &[index, weight] : adjacencyList[i]) {
            // Neighbour are in the form pair<index, weight>
            int currDist = distances[index];
            int newDist = d + weight;
            if (newDist < currDist) {
                /**
                 * Going to the neighbour through the current node is better
                 * than the current route.
                 */
                distances[index] = newDist;
                prev[index] = i;
                pq.push({newDist, index});
            }
        }
    }
}

void gridDijkstra(vvi &grid, vvpii &prev, int sr, int sc) {
    int r = grid.size();
    int c = grid[0].size();
    prev.resize(r, vpii(c));

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    vvi distances(r, vi(c, INT_MAX)); // Set all nodes to (effective) infinity
    distances[sr][sc] = 0;
    prev[sr][sc] = {-1, -1};

    // Distance, Row, Column
    priority_queue<tiii, vector<tiii>, greater<tiii>> pq;
    pq.push({0, sr, sc});

    while (!pq.empty()) {
        auto [distance, row, col] = pq.top();
        pq.pop();
        if (distance > distances[row][col])
            continue; // Stale value on queue

        // Process neighbours
        for (int d = 0; d < 4; d++) {
            int nr = dr[d] + row;
            int nc = dc[d] + col;
            if (nr < 0 || nr >= r)
                continue;
            if (nc < 0 || nc >= c)
                continue;
            int currDist = distances[nr][nc];
            int newDist = distance + grid[nr][nc];
            if (newDist < currDist) {
                distances[nr][nc] = newDist;
                pq.push({newDist, nr, nc});
                prev[nr][nc] = {row, col};
            }
        }
    }
}
