#include <cstdio>
#include <vector>

using namespace std;

vector<int> parents;

// O(1)
int find(int x) {
    // If the root of x is itself, just return it
    // Otherwise, compress the tree and return the root of x
    if (parents[x] != x) {
        parents[x] = find(parents[x]); // This compresses the tree (amortised O(1))
    }
    return parents[x];
}


// O(1)
void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) { // If the roots are different, set the parent of one to the other
        parents[rootX] = rootY;
    }
}

// Total complexity = O((3r * 3c) + k)
int main() {
    // Initialise DSU
    int r, c;
    scanf("%d %d", &r, &c);
    parents.resize(r * c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) { // O(r * c)
            int flattened = i * c + j;
            parents[flattened] = flattened;
        }
    }
    
    // Build Grid
    vector<vector<char>> grid(r, vector<char>(c));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) { // O(r * c)
            char digit;
            scanf(" %c", &digit);
            grid[i][j] = digit;
        }
    }
    
    // Process grid into DSU
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) { // O(r * c)
            int flattened = i * c + j;
            for (int k = 0; k < 4; k++) {
                int nr = i + dr[k];
                int nc = j + dc[k];
                // Bounds check - cannot go below 0 or above the row and column max index
                if (nr < 0 || nc < 0) {
                    continue;
                }
                if (nr >= r || nc >= c) {
                    continue;
                }
                // If the digit is the same as the neighbour, unite the two flattened points
                if (grid[i][j] == grid[nr][nc]) {
                    int neighbour = nr * c + nc;
                    unite(flattened, neighbour);
                }
            }
        }
    }
    
    // Process queries
    int n;
    scanf("%d", &n);
    for (int k = 0; k < n; k++) { // O(k)
        // Get query
        int r1, c1, r2, c2;
        scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
        r1--; c1--; r2--; c2--; // 0-based indexing
        
        int start = r1 * c + c1; // Flatten
        int end = r2 * c + c2;
        
        if (find(start) != find(end)) {
            printf("neither\n");
        } else {
            if (grid[r1][c1] == '1') {
                printf("decimal\n");
            } else {
                printf("binary\n");
            }
        }
    }
}
