#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using vb = vector<bool>;

pair<ll, vb> sieve(ll N) {
    vb isPrime(N + 1, true);
    isPrime[0] = isPrime[1] = false;
    ll n = N - 1;
    for (ll i = 2; i <= (N / i); i++) {
        if (isPrime[i]) {
            for (ll j = (i * i); j <= N; j += i) {
                if (isPrime[j]) {
                    isPrime[j] = false;
                    n--;
                }
            }
        }
    }
    return {n, isPrime};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    pair<ll, vb> s = sieve(n);
    cout << s.first << endl;
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        if (s.second[x]) {
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
    }
    return 0;
}
