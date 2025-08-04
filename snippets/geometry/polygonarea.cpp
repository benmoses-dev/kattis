#include <cmath>
#include <vector>

using namespace std;
using vpii = vector<pair<int, int>>;
using ld = long double;

/**
 * Using winding cross-product:
 * Area = abs(sum((Xi * Yi+1) - (Xi+1 * Yi))) / 2
 */
ld irregularArea(const vpii &c) {
    ld sum = 0.0;
    size_t n = c.size();
    if (n < 3)
        return 0.0;
    for (int i = 0; i < n; i++) {
        ld Xi = c[i].first;
        ld Yi = c[i].second;
        ld Ynext = c[(i + 1) % n].second;
        ld Xnext = c[(i + 1) % n].first;
        sum += (Xi * Ynext) - (Xnext * Yi);
    }
    return fabsl(sum) / 2.0;
}

/**
 * For a regular polygon with n sides of length l:
 * Area = (n * l * l) / (4.0 * tan(pi / n))
 */
ld regularArea(int n, int l) {
    if (n < 3)
        return 0.0;
    return (n * l * l) / (4.0 * tanl(M_PI / n));
}
