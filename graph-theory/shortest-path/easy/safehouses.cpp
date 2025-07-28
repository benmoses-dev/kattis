#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;

    vector<vector<char>> grid(N, vector<char>(N));
    vector<vector<int>> dist(N, vector<int>(N, INT_MAX));
    queue<pair<int, int>> q;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'H') {
                q.push({i, j});
                dist[i][j] = 0;
            }
        }
    }

    int dr[] = {0, 0, -1, 1};
    int dc[] = {-1, 1, 0, 0};
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nr = dr[i] + r;
            int nc = dc[i] + c;
            if (nr < 0 || nr >= N || nc < 0 || nc >= N) {
                continue;
            }
            int currDist = dist[nr][nc];
            int newDist = dist[r][c] + abs(dr[i]) + abs(dc[i]);
            if (newDist < currDist) {
                dist[nr][nc] = newDist;
                q.push({nr, nc});
            }
        }
    }

    int maxDist = -1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] != 'S') {
                continue;
            }
            int d = dist[i][j];
            if (d > maxDist) {
                maxDist = d;
            }
        }
    }

    cout << maxDist << endl;
    return 0;
}
