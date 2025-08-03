#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<long long> registers = {2, 3, 5, 7, 11, 13, 17, 19};
    vector<long long> steps(8);
    vector<long long> values(8);
    long long at = 0;
    steps[0] = 1;
    for (int i = 0; i < 8; i++) {
        cin >> values[i];
        if (i > 0) {
            steps[i] = steps[i - 1] * registers[i - 1];
        }
        at += steps[i] * values[i];
    }
    long long explosion = steps[7] * 19;
    cout << explosion - at - 1 << endl;
    return 0;
}
