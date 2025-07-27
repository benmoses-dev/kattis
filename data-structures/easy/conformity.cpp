#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;

    map<vector<int>, int> courseCounts;

    int maxCount = 0;
    int totalMax = 0;
    for (int n = 0; n < N; n++) {
        int a, b, c, d, e;
        cin >> a >> b >> c >> d >> e;
        vector<int> courses = {a, b, c, d, e};
        sort(courses.begin(), courses.end());
        int cc = ++courseCounts[courses];
        if (cc > maxCount) {
            maxCount = cc;
            totalMax = cc;
        } else if (cc == maxCount) {
            totalMax += cc;
        }
    }

    cout << totalMax << endl;
    return 0;
}
