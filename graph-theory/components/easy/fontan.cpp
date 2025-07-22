#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int currentComponent;

int main() {
    int N, M;
    cin >> N >> M;
    cin.ignore();

    vector<vector<char>> grid(N, vector<char>(M));
    for (int n = 0; n < N; n++) {
        string line;
        getline(cin, line);
        vector<char> chars(line.begin(), line.end());
        grid[n] = chars;
    }

    queue<pair<int, int>> q;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == 'V') {
                q.push({i, j});
            }
        }
    }

    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        if (i + 1 == N) {
            continue;
        }
        if (grid[i + 1][j] == '.') {
            grid[i + 1][j] = 'V';
            q.push({i + 1, j});
            continue;
        }
        if (grid[i + 1][j] == 'V') {
            continue;
        }
        // Cell below is stone, can we go around?
        if ((j - 1 >= 0) && (grid[i][j - 1] == '.')) {
            grid[i][j - 1] = 'V';
            q.push({i, j - 1});
        }
        if ((j + 1 < M) && (grid[i][j + 1] == '.')) {
            grid[i][j + 1] = 'V';
            q.push({i, j + 1});
        }
    }

    for (const vector<char> &row : grid) {
        for (const char &cell : row) {
            cout << cell;
        }
        cout << endl;
    }

    return 0;
}
