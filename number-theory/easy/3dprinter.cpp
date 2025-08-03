#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    int printers = 1;
    int day = 0;
    while (printers < n) {
        printers <<= 1; // Exponential is always best!
        day++;
    }
    cout << day + 1 << endl;
    return 0;
}
