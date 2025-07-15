#include <iostream>
#include <set>

using namespace std;

int main() {
    set<int> mods;
    for (int i = 0; i < 10; i++) {
        int n;
        cin >> n;
        int modResult = n % 42;
        mods.insert(modResult);
    }
    cout << mods.size() << endl;
}
