#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;

    for (int n = 0; n < N; n++) {
        int M;
        cin >> M;
        vector<int> nums(M, 0);

        for (int m = 0; m < M; m++)
            cin >> nums[m];

        // Try standard sequence first
        int diff = nums[1] - nums[0];
        bool isArithmetic = true;
        for (int i = 2; i < M; i++) {
            if (nums[i] - nums[i - 1] != diff) {
                isArithmetic = false;
                break;
            }
        }

        if (isArithmetic) {
            cout << "arithmetic" << endl;
            continue;
        }

        sort(nums.begin(), nums.end());
        diff = nums[1] - nums[0];
        bool isPermuted = true;
        for (int i = 2; i < M; i++) {
            if (nums[i] - nums[i - 1] != diff) {
                isPermuted = false;
                break;
            }
        }

        if (isPermuted) {
            cout << "permuted arithmetic" << endl;
            continue;
        }

        cout << "non-arithmetic" << endl;
    }

    return 0;
}
