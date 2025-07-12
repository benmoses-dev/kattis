#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

bool isPrime(int num) {
    for (int m = 2; m <= sqrt(num); m++) {
        if (num % m == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    vector<int> primes;
    
    // Initialise prime numbers
    for (int i = 2; i <= 1000; i++) {
        if (isPrime(i)) {
            primes.push_back(i);
        }
    }
    
    int cases;
    scanf("%d", &cases);
    
    for (int j = 0; j < cases; j++) {
        long n, e;
        scanf("%ld %ld", &n, &e);
        int p, q;
        long eulerN;
        for (int k = 0; k < primes.size() - 1; k++) {
            if (n % primes[k] == 0) {
                p = primes[k];
                q = n / p;
                break;
            }
        }
        eulerN = (p - 1) * (q - 1);
        int d;
        for (int x = 1; x <= eulerN; x++) {
            if ((e * x) % eulerN == 1) {
                printf("%d\n", x);
            }
        }
    }
}
