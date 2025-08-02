#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int permutations(vector<int> options, int total) {
    // Dynamic programming to find ways to sum to an increasing amount (i)
    vector<long long> dp(total + 1, 0);
    dp[0] = 1; // The empty set
    for (int i = 1; i <= total; i++) {
        /**
         * If you can sum to x using y permutations, then you can sum to (x + option = i)
         * by using y + 1 permutations - simply add the option. Repeat for every possible
         * option.
         */
        for (const int option : options) {
            if (option <= i) {
                dp[i] += dp[i - option];
            }
        }
    }
    return dp[total];
}

int combinations(vector<int> options, int total) {
    vector<long long> dp(total + 1, 0);
    dp[0] = 1;
    /**
     * Fix the options to preserve order and prevent permutations.
     */
    for (const int option : options) {
        for (int i = option; i <= total; i++) {
            dp[i] += dp[i - option];
        }
    }
    return dp[total];
}

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

/**
 * Build up a DP recurrence based on the fact that the current shortest supersequence
 * depends on whether we can merge the two latest characters or not, and on the length
 * of the shortest supersequence found so far.
 */
string shortestSupersequence(string a, string b) {
    int m = a.size();
    int n = b.size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    // The first i characters (0-indexed) compared with the empty string (base cases).
    for (int i = 0; i <= m; i++)
        dp[i][0] = i;
    for (int j = 0; j <= n; j++)
        dp[0][j] = j;

    /**
     * Compare characters from b to characters from a (in increasing length).
     * Recurrence:
     * scs(a, b) =>
     * a[i - 1] == b[j -1] => scs(a[i - 1], b[j - 1]) + 1
     * a[i - 1] != b[j -1] => min(scs(a[i - 1], b[j]), scs(a[i], b[j - 1])) + 1
     */
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1]);
            }

    // Reconstruct the string.
    string result;
    int i = m;
    int j = n;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) { // We only added this once, move diagonally.
            result += a[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] <= dp[i][j - 1]) {
            /**
             * We added a[i - 1] and recursed scs(a[i - 1], b[j])
             * If they are the same, min() prefers the first
             */
            result += a[i - 1];
            i--; // Move the pointer in the direction that we recursed into
        } else {
            // We added b[j - 1] and recursed scs(a[i], b[j - 1])
            result += b[j - 1];
            j--;
        }
    }

    // Add remaining characters (only one string will remain).
    while (i > 0) {
        result += a[i - 1];
        i--;
    }
    while (j > 0) {
        result += b[j - 1];
        j--;
    }

    // We built in reserve, so we need to reverse the reversed!
    reverse(result.begin(), result.end());
    return result;
}
