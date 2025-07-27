#include <iostream>
#include <set>
#include <vector>

using namespace std;

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

long long getSum(long long n) {
    long long sum = 0;
    while (n > 0) {
        int r = n % 10;
        long long d = r * r;
        sum += d;
        n /= 10;
    }
    return sum;
}

int main() {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;

    const int M = 10000;
    vector<bool> isPrime = sieve(M);

    for (int n = 0; n < N; n++) {
        int K, m;
        cin >> K >> m;
        cout << K << " " << m;

        if (!isPrime[m]) {
            cout << " NO" << endl;
            continue;
        }

        set<long long> nums;
        bool isHappy = true;
        long long sum = m;
        while (sum != 1) {
            if (nums.count(sum) > 0) {
                isHappy = false;
                break;
            }
            nums.insert(sum);
            sum = getSum(sum);
        }

        if (isHappy) {
            cout << " YES" << endl;
            continue;
        }

        cout << " NO" << endl;
    }

    return 0;
}
