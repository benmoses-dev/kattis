#include <algorithm>
#include <cfloat>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<double> canisters(n);
    for (int i = 0; i < n; i++) {
        cin >> canisters[i];
    }
    sort(canisters.begin(), canisters.end());

    double minFraction = DBL_MAX;
    for (int i = 1; i <= n; i++) {
        double c = canisters[i - 1];
        if (c > i) {
            cout << "impossible" << endl;
            return 0;
        }
        double fraction = c / i;
        if (fraction < minFraction) {
            minFraction = fraction;
        }
    }

    cout << fixed << setprecision(10) << minFraction << endl;
    return 0;
}
