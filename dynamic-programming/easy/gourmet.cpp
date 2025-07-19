#include <iostream>
#include <vector>

using namespace std;

int main() {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    vector<int> courses(N);
    for (int n = 0; n < N; n++) {
        if (n > M) {
            courses.resize(n);
            break;
        }
        cin >> courses[n];
    }

    // Dynamic programming to find ways to sum to an increasing amount (i)
    vector<long long> dp(M + 1, 0);
    dp[0] = 1; // The empty set
    for (int i = 1; i <= M; i++) {
        /**
         * If you can sum to x using y permutations, then you can sum to (x + course = i)
         * by using y + 1 permutations - simply add the course. Repeat for every possible
         * course.
         */
        for (const int course : courses) {
            if (course <= i) { // The course is possible to eat in the current timeframe
                dp[i] += dp[i - course];
            }
        }
    }

    cout << dp[M] << endl;
    return 0;
}
