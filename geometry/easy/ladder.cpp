#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double h, v;
    cin >> h >> v;
    double l = h / sin(v * M_PI / 180.0);
    int r = ceil(l);
    cout << r << endl;
}
