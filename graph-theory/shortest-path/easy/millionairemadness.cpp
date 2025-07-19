#include <vector>
#include <iostream>
#include <queue>
#include <climits>
#include <tuple>

using namespace std;

int main() {
    int r, c;
    cin >> r >> c;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // No need for adjacency list - use grid directly
    vector<vector<int>> grid(r, vector<int>(c, 0));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> grid[i][j];
        }
    }

    // Dijkstra
    vector<vector<int>> heights(r, vector<int>(c, INT_MAX)); // Set all nodes to (effective) infinity
    heights[0][0] = 0;
        
    // Height, Row, Column
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    pq.push({0, 0, 0});
    
    while (!pq.empty()) {
        auto [height, row, col] = pq.top();
        pq.pop();
        if (height > heights[row][col]) continue; // Stale value on queue
        
        // Process neighbours
        for (int d = 0; d < 4; d++) {
            int nr = dr[d] + row;
            int nc = dc[d] + col;
            if (nr < 0 || nr >= r) continue;
            if (nc < 0 || nc >= c) continue;
            int diff = max(0, grid[nr][nc] - grid[row][col]); // Effectively ignore going down
            int costSoFar = max(height, diff);
            if (costSoFar < heights[nr][nc]) {
                heights[nr][nc] = costSoFar;
                pq.push({costSoFar, nr, nc});
            }
        }
    }

    cout << heights[r - 1][c - 1] << endl;
}
