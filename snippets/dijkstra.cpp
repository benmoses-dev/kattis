#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <tuple>

using namespace std;

void dijkstra(vector<vector<pair<int, int>>>& adjacencyList, vector<int>& prev, int start, int n) {
    // Initialise distances
    vector<int> distances(n, INT_MAX);

    // Queue of pair<distance, index> sorted by smallest distance
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    distances[start] = 0;
    prev[start] = -1;

    while (!pq.empty()) {
        auto [d, i] = pq.top();
        pq.pop();
        if (d > distances[i]) continue; // Stale value on queue

        // Process neighbours
        for (const auto& [index, weight] : adjacencyList[i]) {
            // Neighbour are in the form pair<index, weight>
            int currDist = distances[index];
            int newDist = d + weight;
            if (newDist < currDist) { // Going to the neighbour through the current node is better than the current route
                distances[index] = newDist;
                prev[index] = i;
                pq.push({newDist, index});
            }
        }
    }
}

vector<int> reconstructPath(int end, const vector<int>& prev) {
    vector<int> path;
    for (int curr = end; curr != -1; curr = prev[curr]) {
        path.push_back(curr);
    }
    reverse(path.begin(), path.end());
    return path;
}

void gridDijkstra(vector<vector<int>>& grid, vector<vector<pair<int, int>>>& prev, int sr, int sc) {
    int r = grid.size();
    int c = grid[0].size();
    prev.resize(r, vector<pair<int, int>>(c));

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    vector<vector<int>> distances(r, vector<int>(c, INT_MAX)); // Set all nodes to (effective) infinity
    distances[sr][sc] = 0;
    prev[sr][sc] = {-1, -1};

    // Distance, Row, Column
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    pq.push({0, sr, sc});

    while (!pq.empty()) {
        auto [distance, row, col] = pq.top();
        pq.pop();
        if (distance > distances[row][col]) continue; // Stale value on queue

        // Process neighbours
        for (int d = 0; d < 4; d++) {
            int nr = dr[d] + row;
            int nc = dc[d] + col;
            if (nr < 0 || nr >= r) continue;
            if (nc < 0 || nc >= c) continue;
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

vector<pair<int, int>> reconstructGridPath(int endRow, int endCol, const vector<vector<pair<int, int>>>& prev) {
    vector<pair<int, int>> path;
    for (pair<int, int> curr = {endRow, endCol}; curr.first != -1 && curr.second != -1; curr = prev[curr.first][curr.second]) {
        path.push_back({curr.first, curr.second});
    }
    reverse(path.begin(), path.end());
    return path;
}
