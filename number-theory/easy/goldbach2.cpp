#include <iostream>
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

int main() {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;

    const int M = 32000;
    vector<bool> isPrime = sieve(M);
    vector<int> primes;
    for (int i = 2; i <= M; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    for (int n = 0; n < N; n++) {
        int num;
        cin >> num;

        int i = 0;
        int j = primes.size() - 1;
        vector<pair<int, int>> results;

        while (i <= j) {
            int sum = primes[i] + primes[j];
            if (sum == num) {
                results.emplace_back(primes[i], primes[j]);
                i++;
                j--;
            } else if (sum < num) {
                i++;
            } else {
                j--;
            }
        }

        int s = results.size();
        cout << num << " has " << s << " representation(s)" << endl;
        for (const auto &[first, second] : results) {
            cout << first << "+" << second << endl;
        }
        cout << endl;
    }

    return 0;
}
