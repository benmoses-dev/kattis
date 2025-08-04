#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
using vpii = vector<pair<int, int>>;
using ld = long double;

/**
 * Using winding cross-product:
 * Area = abs(sum((Xi * Yi+1) - (Xi+1 * Yi))) / 2
 */
ld area(const vpii &c) {
    ld sum = 0.0;
    int n = c.size();
    if (n < 3)
        return 0.0;
    for (int i = 0; i < n; i++) {
        ld Xi = c[i].first;
        ld Yi = c[i].second;
        ld Ynext = c[(i + 1) % n].second;
        ld Xnext = c[(i + 1) % n].first;
        sum += (Xi * Ynext) - (Xnext * Yi);
    }
    return fabsl(sum) / 2.0;
}

int main() {
    int N;
    cin >> N;
    for (int n = 0; n < N; n++) {
        int m;
        cin >> m;
        vpii c;
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            c.emplace_back(x, y);
        }
        cout << fixed << setprecision(6) << area(c) << endl;
    }
    return 0;
}
