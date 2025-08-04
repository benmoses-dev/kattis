#include <algorithm>
#include <vector>

using namespace std;
using vi = vector<int>;
using pii = pair<int, int>;
using vpii = vector<pii>;

vi reconstructPath(int end, const vi &prev) {
    vi path;
    for (int curr = end; curr != -1; curr = prev[curr]) {
        path.push_back(curr);
    }
    reverse(path.begin(), path.end());
    return path;
}

vpii reconstructGridPath(int endRow, int endCol, const vector<vpii> &prev) {
    vpii path;
    for (pii curr = {endRow, endCol}; curr.first != -1 && curr.second != -1;
         curr = prev[curr.first][curr.second]) {
        path.push_back({curr.first, curr.second});
    }
    reverse(path.begin(), path.end());
    return path;
}
