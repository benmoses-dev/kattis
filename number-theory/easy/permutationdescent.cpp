#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int P;
    cin >> P;

    const int m = 1001113;
    int maxN = 100;

    // dp[N][v] is the count of permutations with length N and k descents
    vector<vector<long long>> dp(maxN + 1, vector<long long>(maxN, 0));
    dp[1][0] = 1;
    dp[1][1] = 0;

    for (int n = 2; n <= maxN; n++) {
        for (int k = 0; k < n; k++) {
            if (k == 0 || k == n - 1) {
                dp[n][k] = 1;
                continue;
            }
            /**
             * For each permutation where we need to preserve the descents:
             * dp[n - 1][k]
             * Add the current n between descents or at the back.
             */
            long long count = (dp[n - 1][k] * (k + 1)) % m;
            /**
             * For each permutation where we need to increase the descents:
             * dp[n - 1][k - 1]
             * Add the current n between non-descents or at the front.
             */
            count += (dp[n - 1][k - 1] * (n - k)) % m;
            dp[n][k] = count % m;
        }
    }

    for (int p = 0; p < P; p++) {
        int K, N, v;
        cin >> K >> N >> v;
        cout << K << " " << dp[N][v] << endl;
    }

    return 0;
}
