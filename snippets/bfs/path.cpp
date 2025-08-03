#include <algorithm>
#include <vector>

using namespace std;

vector<int> reconstructPath(int end, const vector<int> &prev) {
    vector<int> path;
    for (int curr = end; curr != -1; curr = prev[curr]) {
        path.push_back(curr);
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<pair<int, int>> reconstructGridPath(int endRow, int endCol,
                                           const vector<vector<pair<int, int>>> &prev) {
    vector<pair<int, int>> path;
    for (pair<int, int> curr = {endRow, endCol}; curr.first != -1 && curr.second != -1;
         curr = prev[curr.first][curr.second]) {
        path.push_back({curr.first, curr.second});
    }
    reverse(path.begin(), path.end());
    return path;
}
