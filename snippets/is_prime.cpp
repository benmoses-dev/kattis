#include <vector>

using namespace std;

bool isPrime(long long n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    for (long long i = 5; i <= n / i; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

vector<bool> sieve(long long N) {
    vector<bool> isPrime(N + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (long long i = 2; i <= (N / i); i++) {
        if (isPrime[i]) {
            for (long long j = (i * i); j <= N; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return isPrime;
}
