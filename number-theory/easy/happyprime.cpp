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

vector<int> getDigits(long long n) {
    long long temp = n;
    vector<int> digits;
    while (temp > 9) {
        int r = temp % 10;
        digits.push_back(r);
        temp /= 10;
    }
    digits.push_back(temp);
    return digits;
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

        vector<int> digits = getDigits(m);
        set<long long> nums;
        bool isHappy = true;
        long long sum = 0;
        while (isHappy && sum != 1) {
            sum = 0;
            for (const int digit : digits) {
                long long d = digit * digit;
                sum += d;
            }
            if (nums.count(sum) > 0) {
                isHappy = false;
            }
            nums.insert(sum);
            digits = getDigits(sum);
        }

        if (isHappy) {
            cout << " YES" << endl;
            continue;
        }

        cout << " NO" << endl;
    }

    return 0;
}
