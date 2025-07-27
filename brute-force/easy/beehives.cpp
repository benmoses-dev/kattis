#include <cmath>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

const double EPSILON = 1e-8;

double getDistance(pair<double, double> a, pair<double, double> b) {
    double xDiff = fabs(b.first - a.first);
    double yDiff = fabs(b.second - a.second);
    return sqrt((xDiff * xDiff) + (yDiff * yDiff));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        double d;
        int N;
        cin >> d >> N;

        if (d <= 0.0 + EPSILON && d >= 0.0 - EPSILON && N == 0)
            break;

        vector<pair<double, double>> hives;
        set<pair<double, double>> sour;
        for (int n = 0; n < N; n++) {
            pair<double, double> hive;
            cin >> hive.first >> hive.second;
            for (const pair<double, double> &h : hives) {
                double distance = getDistance(hive, h);
                if (distance < d + EPSILON) {
                    sour.insert(hive);
                    sour.insert(h);
                }
            }
            hives.push_back(hive);
        }

        int sweet = hives.size() - sour.size();
        cout << sour.size() << " sour, " << sweet << " sweet" << endl;
    }

    return 0;
}
