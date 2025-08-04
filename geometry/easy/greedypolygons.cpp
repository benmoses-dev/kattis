#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int n, l, d, g;
        cin >> n >> l >> d >> g;
        int te = d * g;
        // Area of original polygon = (n * (l * l)) / (4 * tan(pi / n))
        double area = (n * l * l) / (4.0 * tan(M_PI / n));
        // Add a rectangle buffer for each side.
        double ba = l * te * n;
        // Add an arc at each corner (cirlce over all corners)
        double ca = M_PI * te * te;
        double fa = area + ba + ca;
        cout << fixed << setprecision(10) << fa << endl;
    }
    return 0;
}
