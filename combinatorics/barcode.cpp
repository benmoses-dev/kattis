#include <iostream>
#include <vector>

using namespace std;

vector<long long> factorials(2, 1);
vector<long long> fibonaccis(2);

long long nChooseK(long long n, long long k) {
    return factorials[n] / (factorials[k] * factorials[n - k]);
}

int main() {
    fibonaccis[0] = 1;
    fibonaccis[1] = 2;
    
    int datasets;
    cin >> datasets;
    
    for (int i = 0; i < datasets; i++) {
        int n, m;
        cin >> n >> m;
        
        // Cache the factorials and fibonacci sequences as they are huge
        int pf = factorials.size();
        if (n >= pf) {
            // Update missing entries
            factorials.resize(n + 1);
            fibonaccis.resize(n + 1);
            for (int f = pf; f <= n; f++) {
                factorials[f] = factorials[f - 1] * f;
                fibonaccis[f] = fibonaccis[f - 1] + fibonaccis[f - 2];
            }
        }
        
        
        long long k;
        // A OR B is the same as A + B - (A and B), so work out A, B, and AB
        if (n % 2 != 0) {
            long long a = 0;
            long long b = fibonaccis[n] % m; // We have two ways to end the sequence, R and RB, and they both rely on a valid n - 1 and n - 2, respectively...
            long long ab = 0;
            k = a + b - ab;
        } else {
            int blues = n / 2;
            long long a = nChooseK(n, blues); // How many ways to choose blues in the total sequence
            long long b = fibonaccis[n];
            // We need to essentially go B R B R or R B R B = n / 2 reds/blues and n / 2 + 1 possible blue positions (including both ends)
            int bluePositions = n / 2 + 1;
            long long ab = nChooseK(bluePositions, blues);
            // Can we even do this without taking mods along the way? Probably need to use fermat?
            k = a + b - ab;
        }
        
        cout << (k % m) << "\n";
    }
}
