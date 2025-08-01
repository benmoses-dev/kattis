#include <iostream>
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

long long sieve(long long N, long long K) {
    vector<bool> isPrime(N + 1, true);
    isPrime[0] = isPrime[1] = false;
    long long k = 0;
    for (long long i = 2; i <= N; i++) {
        if (isPrime[i]) {
            if (++k == K)
                return i;
            for (long long j = (i * i); j <= N; j += i) {
                if ((isPrime[j]) == true) {
                    if (++k == K)
                        return j;
                    isPrime[j] = false;
                }
            }
        }
    }
    return -1;
}

int main() {
    long long N, K;
    cin >> N >> K;
    cout << sieve(N, K) << endl;
    return 0;
}
