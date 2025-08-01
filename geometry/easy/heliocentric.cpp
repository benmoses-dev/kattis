#include <iostream>

using namespace std;

int main() {
    int e, m;
    int c = 0;
    while (cin >> e >> m) {
        int count = 0;
        while (true) {
            if (e == 0 && m == 0) {
                cout << "Case " << ++c << ": " << count << endl;
                break;
            }
            e++;
            m++;
            e %= 365;
            m %= 687;
            count++;
        }
    }
    return 0;
}
