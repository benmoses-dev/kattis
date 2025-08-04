using ll = long long;

ll nCr(ll n, ll k) {
    if (k > n)
        return 0;

    if (k > n - k)
        k = n - k;

    ll result = 1;
    for (ll i = 1; i <= k; i++) {
        result = result * (n - i + 1) / i;
    }

    return result;
}
