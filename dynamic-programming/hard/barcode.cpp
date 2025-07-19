#include <iostream>
#include <vector>

using namespace std;

long long modInverse(long long num, long long m) {
    long long result = 1;
    long long exponent = m - 2;
    num = num % m;
    while (exponent > 0) {
        if (exponent & 1) result = (result * num) % m;
        num = (num * num) % m;
        exponent = exponent >> 1;
    }
    return result;
}

long long nChooseK(long long n, long long k, long long m, const vector<long long>& factorials, const vector<long long>& modInvFactorials) {
    if (n % 2 != 0) return 0;
    long long nMod = factorials[n] % m;
    long long kMod = modInvFactorials[k] % m;
    long long nModkMod = (nMod * kMod) % m;
    long long nkMod = modInvFactorials[n - k] % m;
    return (nModkMod * nkMod) % m; // all the mods
}

long long countExclusion(int n, int m) {
    if (n % 2 != 0) return 0;

    int reds = n / 2;
    int blues = n / 2;

    vector<long long> endsWithRed(reds + 1, 0);
    vector<long long> endsWithBlue(reds + 1, 0);

    // Base case: sequence of length 0
    endsWithRed[0] = 1;

    for (int len = 1; len <= n; ++len) {
        vector<long long> newRed(reds + 1, 0);
        vector<long long> newBlue(reds + 1, 0);

        for (int r = 0; r <= reds; ++r) {
            int b = len - 1 - r;
            if (b < 0 || b > blues) continue;

            long long fromRed = endsWithRed[r];
            long long fromBlue = endsWithBlue[r];

            // Add red
            if (r + 1 <= reds) {
                newRed[r + 1] = (fromRed + fromBlue) % m;
            }

            // Add blue — only after red
            if (b + 1 <= blues) {
                newBlue[r] = fromRed % m;
            }
        }

        endsWithRed = newRed;
        endsWithBlue = newBlue;
    }

    return (endsWithRed[reds] + endsWithBlue[reds]) % m;
}

int main() {
    int datasets;
    cin >> datasets;
    
    for (int i = 0; i < datasets; i++) {
        int n, m;
        cin >> n >> m;
        
        vector<long long> factorials(2);
        vector<long long> fibonaccis(2);
        vector<long long> modInvFactorials(2);
        
        fibonaccis[0] = 1;
        fibonaccis[1] = 2;
        factorials[0] = 1;
        factorials[1] = 1;
        // Cache the factorials and fibonacci sequences as they are huge
        factorials.resize(n + 1);
        fibonaccis.resize(n + 1);
        for (int f = 2; f <= n; f++) {
            factorials[f] = (factorials[f - 1] * f) % m;
            fibonaccis[f] = (fibonaccis[f - 1] + fibonaccis[f - 2]) % m;
        }
        modInvFactorials.resize(n + 1);
        for (int f = 0; f <= n; f++) {
            modInvFactorials[f] = modInverse(factorials[f], m);
        }
        
        // A OR B is the same as A + B - (A and B), so work out A, B, and AB (we need to work out the overlap anyway - is there a better way to do this?)
        long long a = nChooseK(n, n / 2, m, factorials, modInvFactorials);
        long long b = fibonaccis[n] % m; // We have two ways to end the sequence, R and RB, and they both rely on a valid n - 1 and n - 2, respectively...
        long long ab = countExclusion(n, m);
        long long k = a + b - ab;
        if (k < 0) k += m;
        
        cout << (k % m) << "\n";
    }
}
