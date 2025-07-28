#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    const double EPS = 1e-8;
    double x, y;
    cin >> x >> y;
    if (y <= 1.0 + EPS && y >= 1.0 - EPS) {
        if (x < 0.0 + EPS && x > 0.0 - EPS) {
            cout << "ALL GOOD" << endl;
            return 0;
        } else {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }
    // B = yA + x
    // A = yA + x
    // A - yA = x
    // A(1 - y) = x
    // A = x / (1 - y)
    double A = x / (1 - y);
    cout << fixed << setprecision(10) << A << endl;
    return 0;
}
