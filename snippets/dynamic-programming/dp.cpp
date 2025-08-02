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
