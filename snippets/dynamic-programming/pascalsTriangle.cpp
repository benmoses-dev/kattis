#include <vector>

using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;

/**
 * Use DP (Pascal's triangle) to pre compute binomial coefficients.
 */
vvll pascalsTriangle(int maxN, int maxR) {
    vvll dp(maxN + 1, vll(maxR + 1, 0));
    for (int i = 0; i <= maxN; i++) {
        dp[i][0] = 1;
        for (int j = 1; j <= min(i, maxR); j++) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
        }
    }
    return dp;
}
