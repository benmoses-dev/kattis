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