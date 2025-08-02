#include <vector>

using namespace std;

/**
 * Simple backtracking to build up combinations summing to a target.
 */
void backtrack(int target, const vector<int> &options, vector<int> &current, int index,
               vector<vector<int>> &results) {
    if (target == 0) {
        results.push_back(current);
        return;
    }
    for (int i = index; i < 3; i++) {
        if (options[i] > target)
            continue;
        current.push_back(options[i]);
        backtrack(target - options[i], options, current, i, results);
        current.pop_back();
    }
}
