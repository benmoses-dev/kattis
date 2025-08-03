#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int findGold(const vector<vector<char>> &grid, pair<int, int> start) {
    int r = grid.size();
    int c = grid[0].size();

    vector<vector<bool>> visited(r, vector<bool>(c, false));

    int i = start.first;
    int j = start.second;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    queue<pair<int, int>> q;
    q.push({i, j});
    visited[i][j] = true;

    int gold = 0;
    while (!q.empty()) {
        auto [row, col] = q.front();
        q.pop();
        if (grid[row][col] == 'G') {
            gold++;
        }
        bool backtrack = false;
        for (int d = 0; d < 4; d++) {
            int nr = dr[d] + row;
            int nc = dc[d] + col;
            if (nr < 0 || nr >= r)
                continue;
            if (nc < 0 || nc >= c)
                continue;
            if (grid[nr][nc] == 'T') {
                backtrack = true;
            }
        }
        if (backtrack)
            continue;
        for (int d = 0; d < 4; d++) {
            int nr = dr[d] + row;
            int nc = dc[d] + col;
            if (nr < 0 || nr >= r)
                continue;
            if (nc < 0 || nc >= c)
                continue;
            if (grid[nr][nc] == '#')
                continue;
            if (visited[nr][nc] == false) {
                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }

    return gold;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int c, r;
    cin >> c >> r;

    pair<int, int> player;
    vector<vector<char>> grid(r, vector<char>(c));
    for (int i = 0; i < r; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < c; j++) {
            grid[i][j] = row[j];
            if (row[j] == 'P') {
                player = {i, j};
            }
        }
    }

    int gold = findGold(grid, player);
    cout << gold << endl;
    return 0;
}
