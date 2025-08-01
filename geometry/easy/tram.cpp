#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    // Perpendicular square distance = ((xi - yi + a)^2) / 2
    // Total over all points = sum(((xi - yi + a)^2) / 2)
    // let zi = xi - yi.
    // => sum((zi + a)^2) / 2 = sum(zi^2 + a^2 + (2 * zi * a)) / 2
    // => sum((zi^2 / 2) + (a * zi) + (a^2 / 2))
    // => (sum(zi^2) / 2) + (a * sum(zi)) + (n * (a^2 / 2))
    // Minimise the quadratic at the vertex = -(sum(zi)) / (2 * (n / 2))
    // => -(sum(xi - yi)) / n
    // This is also equal to the average of the signed distances from each point to y = x + 0

    double sum = 0;
    for (int i = 0; i < n; i++) {
        double x, y;
        cin >> x >> y;
        sum += (x - y);
    }

    double a = -sum / n;
    cout << fixed << setprecision(6) << a;
    return 0;
}
