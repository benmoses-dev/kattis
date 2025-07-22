#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<pair<double, string>> passwords(N);
    for (int n = 0; n < N; n++) {
        string password;
        double probability;
        cin >> password >> probability;
        passwords[n] = {probability, password};
    }

    sort(passwords.begin(), passwords.end(),
         [](const pair<double, string> &a, const pair<double, string> &b) {
             return a.first > b.first;
         });

    double expectedValue = 0.0;
    int attempts = 1;
    for (const auto &[probability, password] : passwords) {
        expectedValue += (attempts * probability);
        attempts++;
    }

    cout << fixed << setprecision(4) << expectedValue << endl;
    return 0;
}
