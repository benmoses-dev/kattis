#include <iostream>

using namespace std;

long long myFib(long long num) { // Rewrite using DP
    if (num == 0) return 1; // Empty string is still a barcode, technically?
    if (num == 1) return 2; // Either R or B
    return myFib(num - 1) + myFib(num - 2);
}

long long factorial(long long num) { // Rewrite using DP
    if (num == 0 || num == 1) return 1;
    return num * factorial(num - 1);
}

long long nChooseK(long long n, long long k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

int main() {
    int datasets;
    cin >> datasets;
    
    for (int i = 0; i < datasets; i++) {
        int n, m;
        cin >> n >> m;
        long long k;
        // A OR B is the same as A + B - (A and B), so work out A, B, and AB (we need to work out the overlap anyway - is there a better way to do this?)
        if (n % 2 != 0) {
            long long a = 0; // Impossible
            long long b = myFib(n) % m; // We have two ways to end the sequence, R and RB, and they both rely on a valid n - 1 and n - 2, respectively...
            long long ab = 0; // Impossible due to point a above
            k = a + b - ab;
        } else {
            int blues = n / 2;
            long long a = nChooseK(n, blues); // How many ways to choose blues in the total sequence
            long long b = myFib(n);
            // We need to essentially go B R B R or R B R B = n / 2 reds/blues and n / 2 + 1 possible blue positions (including both ends)
            int bluePositions = n / 2 + 1;
            long long ab = nChooseK(bluePositions, blues);
            // Can we even do this without taking mods along the way? Probably need to use fermat?
            k = a + b - ab;
        }
        
        cout << (k % m) << "\n";
    }
}