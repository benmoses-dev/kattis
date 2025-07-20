#include <iostream>
#include <set>

using namespace std;

int main() {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    int N, S, R;
    cin >> N >> S >> R;
    set<int> damaged;
    set<int> reserves;

    // Add all the teams with damaged kayaks to a set.
    for (int s = 0; s < S; s++) {
        int i;
        cin >> i;
        damaged.insert(i);
    }

    // Add teams with reserves, as long as they do not need them themselves.
    for (int r = 0; r < R; r++) {
        int i;
        cin >> i;
        if (damaged.count(i) == 0) {
            reserves.insert(i);
        } else {
            damaged.erase(i);
        }
    }

    // Process team numbers in order, checking left first then right.
    for (int i = 1; i <= N; i++) {
        if (reserves.count(i) == 1) {
            if (damaged.count(i - 1) == 1) {
                damaged.erase(i - 1);
                reserves.erase(i);
            } else if (damaged.count(i + 1) == 1) {
                damaged.erase(i + 1);
                reserves.erase(i);
            }
        }
    }

    int invalid = damaged.size();
    cout << invalid << endl;
    return 0;
}
