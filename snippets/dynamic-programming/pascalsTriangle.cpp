#include <vector>

using namespace std;

/**
 * Use DP (Pascal's triangle) to pre compute binomial coefficients.
 */
vector<vector<long long>> pascalsTriangle(int maxN, int maxR) {
    vector<vector<long long>> dp(maxN + 1, vector<long long>(maxR + 1, 0));
    for (int i = 0; i <= maxN; i++) {
        dp[i][0] = 1;
        for (int j = 1; j <= min(i, maxR); j++) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
        }
    }
    return dp;
}
