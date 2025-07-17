#include <vector>
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        int d1, d2;
        cin >> d1;
        vector<int> c1(d1 + 1, 0);

        for (int i = 0; i <= d1; i++) {
            cin >> c1[i];
        }

        cin >> d2;
        vector<int> c2(d2 + 1, 0);

        for (int i = 0; i <= d2; i++) {
            cin >> c2[i];
        }

        // Use a vector to index the degree of the result
        vector<int> r(d1 + d2 + 1, 0);
        for (int i = 0; i <= d1; i++) {
            for (int j = 0; j <= d2; j++) {
                int d = i + j;
                int m = c1[i] * c2[j];
                r[d] += m;
            }
        }

        cout << r.size() - 1 << endl;
        for (const int& i : r) {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}
