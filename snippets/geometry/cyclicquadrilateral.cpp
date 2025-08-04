#include <cmath>

using namespace std;
using ld = long double;

ld area(ld a, ld b, ld c, ld d) {
    ld s = (a + b + c + d) / 2.0;
    return sqrt((s - a) * (s - b) * (s - c) * (s - d));
}
