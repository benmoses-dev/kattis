#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    if (n == 0 || n == 1) {
        cout << 0 << endl;
        return 0;
    }
    // 2^n - (n choose 1) - (n choose 0)
    long long subsets = (1LL << n) - n - 1;
    cout << subsets << endl;
    return 0;
}
