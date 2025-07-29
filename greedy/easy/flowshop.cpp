#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    cin >> N >> M;
    vector<vector<int>> dp(N, vector<int>(M, 0));

    // Process first swather.
    cin >> dp[0][0];
    for (int j = 1; j < M; j++) {
        int t;
        cin >> t;
        dp[0][j] = dp[0][j - 1] + t;
    }

    for (int i = 1; i < N; i++) {
        int s;
        cin >> s;
        dp[i][0] = dp[i - 1][0] + s;
        for (int j = 1; j < M; j++) {
            int t;
            cin >> t;
            dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]) + t;
        }
    }

    int end = M - 1;
    cout << dp[0][end];
    for (int i = 1; i < N; i++) {
        cout << " " << dp[i][end];
    }
    cout << endl;

    return 0;
}
