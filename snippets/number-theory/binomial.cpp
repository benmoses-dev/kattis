long long nCr(long long n, long long k) {
    if (k > n)
        return 0;

    if (k > n - k)
        k = n - k;

    long long result = 1;
    for (long long i = 1; i <= k; i++) {
        result = result * (n - i + 1) / i;
    }

    return result;
}
