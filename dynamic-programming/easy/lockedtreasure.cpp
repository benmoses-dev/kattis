#include <iostream>
#include <vector>

using namespace std;

int main() {
    int C;
    cin >> C;

    // Use DP (Pascal's triangle) to pre compute binomial coefficients.
    vector<vector<long long>> dp(31, vector<long long>(31, 0));
    for (int i = 0; i <= 30; i++) {
        dp[i][0] = 1;
        dp[i][i] = 1;
        for (int j = 1; j < i; j++) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
        }
    }

    for (int c = 0; c < C; c++) {
        int n, m;
        cin >> n >> m;
        /**
         * For each combination of m - 1 bandits, we need to add a lock that they
         * cannot open. We can then give the key to this lock to the mth bandit (for
         * every combination of m - 1). During each combination, all bandits in the
         * combination can have the keys to all other locks (other than the one we add).
         * This is essentially just the binomial coefficient of n and m - 1.
         */
        long long addedLocks = dp[n][m - 1];
        cout << addedLocks << endl;
    }

    return 0;
}
