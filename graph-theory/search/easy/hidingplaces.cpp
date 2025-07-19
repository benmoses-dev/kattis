#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

int dr[] = {-2, -2, -1, 1, 2, 2, -1, 1};
int dc[] = {-1, 1, -2, -2, -1, 1, 2, 2};
char mappings[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int r; char l;
        cin >> l >> r;
        r--; // Convert row to an index
        int c;
        for (int m = 0; m < 8; m++) {
            if (mappings[m] == l){
                c = m; // Convert letters to a number
            } 
        }

        map<int, int> visited; // Don't visit any square more than once, keeping track of the moves until the visit
        vector<pair<int, int>> sorted; // Use a map for easy access, and a vector to sort by total moves
        queue<pair<int, int>> next; // Queue for BFS tracking
        next.push({r, c}); // Starting square

        int moves = 0;
        while (!next.empty()) {
            int s = next.size();
            while (s-- > 0) { // Empty the queue from this point to track total moves
                pair<int, int> move = next.front();
                next.pop();
                for (int nm = 0; nm < 8; nm++) {
                    int nr = move.first + dr[nm];
                    int nc = move.second + dc[nm];
                    if (nr < 0 || nr > 7) continue;
                    if (nc < 0 || nc > 7) continue;
                    int flattened = nr * 8 + nc; // We don't need to track actual values of the square, just the indexes
                    if (!visited.contains(flattened)) {
                        // Set this square as visited and move to it
                        next.push({nr, nc});
                        visited.insert({flattened, moves + 1});
                        sorted.push_back({moves + 1, flattened});
                    }
                }
            }
            moves++; // BFS iteration
        }

        // Find all the equal highest hiding places and output the total moves
        sort(sorted.begin(), sorted.end(), greater<>());
        int highest = sorted[0].first;
        cout << highest;
        vector<int> hiding;
        for (const pair<int, int>& it : sorted) {
            if (it.first < highest) break;
            hiding.push_back(it.second);
        }

        // All these are equal, we just need to sort ready for the final output
        vector<pair<int, int>> hidingPlaces;
        for (const int& h : hiding) {
            // Convert flattened index to grid index
            int c = h % 8;
            int r = h / 8;
            hidingPlaces.push_back({r, c});
        }
        // Sort by row descending, then by column ascending
        sort(hidingPlaces.begin(), hidingPlaces.end(), [](pair<int, int> a, pair<int, int> b) {
            if (a.first == b.first) {
                return a.second < b.second;
            }
            return a.first > b.first;
        });

        // Final output, converting column index back to the initial letter
        for (const pair<int, int> hp : hidingPlaces) {
            cout << " " << mappings[hp.second] << (hp.first + 1);
        }
        cout << "\n";
    }

    return 0;
}
