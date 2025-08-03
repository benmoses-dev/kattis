#include <iostream>
#include <vector>

using namespace std;

void dfs(int target, const vector<int> &legs, vector<int> &current, int index,
         vector<vector<int>> &results) {
    if (target == 0) {
        results.push_back(current);
        return;
    }

    for (int i = index; i < 3; i++) {
        if (legs[i] > target)
            continue;
        current.push_back(i);
        dfs(target - legs[i], legs, current, i, results);
        current.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> legs(3);
    int l;
    cin >> legs[0] >> legs[1] >> legs[2] >> l;

    vector<int> current;
    vector<vector<int>> results;
    dfs(l, legs, current, 0, results);

    if (results.empty()) {
        cout << "impossible" << endl;
        return 0;
    }

    for (int at = results.size() - 1; at >= 0; at--) {
        vector<int> result = results[at];
        vector<int> output(3, 0);
        for (const int &i : result) {
            output[i]++;
        }
        cout << output[0] << " " << output[1] << " " << output[2] << endl;
    }

    return 0;
}
