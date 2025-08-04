#include <cmath>
#include <vector>

using namespace std;
using vpii = vector<pair<int, int>>;
using ld = long double;

ld area(vpii triangle) {
    const auto [x1, y1] = triangle[0];
    const auto [x2, y2] = triangle[1];
    const auto [x3, y3] = triangle[2];
    return fabsl(((ld)x1 * (y2 - y3)) + ((ld)x2 * (y3 - y1)) + ((ld)x3 * (y1 - y2))) /
           2.0;
};
