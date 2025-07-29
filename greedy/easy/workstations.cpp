#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, m;
    cin >> N >> m;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>
        coming;

    for (int n = 0; n < N; n++) {
        int a, s;
        cin >> a >> s;
        coming.push({a, s});
    }

    priority_queue<int, vector<int>, greater<int>> workstations;
    int saved = 0;

    while (!coming.empty()) {
        auto [entry, duration] = coming.top();
        int exit = entry + duration;
        workstations.push(exit);
        coming.pop();

        while (!workstations.empty()) {
            int t = entry - workstations.top();
            if (t < 0)
                break;
            workstations.pop();
            // Take the earliest vacated workstation that is unlocked.
            if (t <= m) {
                saved++;
                break;
            }
        }
    }

    cout << saved << endl;
    return 0;
}
