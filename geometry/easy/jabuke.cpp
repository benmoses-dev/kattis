#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

const double EPS = 1e-8;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto area = [](vector<pair<int, int>> triangle) {
        const auto [x1, y1] = triangle[0];
        const auto [x2, y2] = triangle[1];
        const auto [x3, y3] = triangle[2];
        return fabs((x1 * (y2 - y3)) + (x2 * (y3 - y1)) + (x3 * (y1 - y2))) / 2.0;
    };

    vector<pair<int, int>> land(3);
    for (int i = 0; i < 3; i++) {
        cin >> land[i].first >> land[i].second;
    }
    double a = area(land);
    cout << fixed << setprecision(1) << a << endl;

    int N;
    cin >> N;
    int treeCount = 0;
    for (int n = 0; n < N; n++) {
        vector<pair<int, int>> test(3);
        cin >> test[0].first >> test[0].second;
        double totalArea = 0.0;
        for (int i = 0; i < 3; i++) {
            test[1] = land[i];
            test[2] = land[(i + 1) % 3];
            totalArea += area(test);
        }
        if (totalArea <= a + EPS && totalArea >= a - EPS)
            treeCount++;
    }

    cout << treeCount << endl;
    return 0;
}
