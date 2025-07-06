#include <string>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    // Store all the strings - we will then ignore this until the end
    vector<string> strings;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        strings.push_back(s);
    }
    if (strings.size() == 1) {
        cout << strings[0] << "\n";
        return 0;
    }
    
    vector<int> links(n, -1); // Link all the strings together using pointers (like a linked list)
    vector<int> tails(n); // So that we can join the end of one list to the start of the next
    for (int i = 0; i < n; i++) tails[i] = i;
    
    vector<bool> hasPrevious(n, false); // This is for the final step - we need to find the first string to start the output
    
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--; // Index from zero
        
        int tail = tails[a]; // Get a's tail
        links[tail] = b; // Set the next string from the tail to the string at index b
        tails[a] = tails[b]; // Expand the tail of a to the tail of b (the next concat with append to the tail of b)
        hasPrevious[b] = true;
    }
    
    // Start at the first string and output until the end
    int root = -1;
    for (int i = 0; i < n; i++) {
        if (hasPrevious[i] == false) {
            root = i;
            break;
        }
    }
    while (root != -1) {
        cout << strings[root];
        root = links[root];
    }
    
    cout << "\n";
    return 0;
}
