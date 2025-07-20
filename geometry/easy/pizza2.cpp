#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    double PI = 3.141592653589793238463;
    int R, C;
    cin >> R >> C;
    int inner = R - C;
    double areaInner = PI * (inner * inner);
    double area = PI * (R * R);
    double percent = (areaInner / area) * 100;
    cout << fixed << setprecision(10) << percent << endl;
}
