#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
  double a, b, c, d;
  cin >> a >> b >> c >> d;
  // Cyclic quadrilateral
  double s = (a + b + c + d) / 2.0;
  double area = sqrt((s - a) * (s - b) * (s - c) * (s - d));
  cout << fixed << setprecision(10) << area << "\n";
}
