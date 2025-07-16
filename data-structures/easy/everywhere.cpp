#include <set>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        cin.ignore();
        set<string> names;
        
        for (int j = 0; j < n; j++) {
            string name;
            getline(cin, name);
            names.insert(name);
        }

        cout << names.size() << endl;
    }

    return 0;
}
