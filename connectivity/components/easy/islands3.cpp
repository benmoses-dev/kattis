#include <iostream>
#include <vector>

using namespace std;

vector<int> components;
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
int r, c;
vector<vector<char>> grid;

// DFS flood-fill with component ids
void dfs(int row, int col, int componentId) {
  int flattened = row * c + col;
  components[flattened] = componentId;

  for (int dir = 0; dir < 4; dir++) {
    int nr = row + dr[dir];
    int nc = col + dc[dir];

    if (nr >= 0 && nr < r && nc >= 0 && nc < c) {
      int neighbour = nr * c + nc;
      // Expand out from land squares to neighbouring land or cloud squares
      if ((grid[nr][nc] == 'L' || grid[nr][nc] == 'C') &&
          components[neighbour] == 0) {
        dfs(nr, nc, componentId);
      }
    }
  }
}

int main() {
  cin >> r >> c;
  grid.resize(r, vector<char>(c));
  components.resize(r * c, 0);

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      cin >> grid[i][j];
    }
  }

  int componentId = 1;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      int flattened = i * c + j;
      if (grid[i][j] == 'L' && components[flattened] == 0) {
        dfs(i, j, componentId++);
      }
    }
  }

  cout << componentId - 1 << endl;
  return 0;
}
