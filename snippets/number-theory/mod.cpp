#include <numeric>
#include <stdexcept>
#include <vector>

using namespace std;

/**
 * Helper function for normalising inputs mod m.
 * This ensures that inputs are not negative or too large.
 */
long long normalise(long long x, long long m) { return (x % m + m) % m; }

/**
 * EEA to find gcd and Bezout coefficients.
 * gcd(a, b) = gcd(b, a % b)
 */
long long extendedGCD(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        // gcd(a,0) = a
        // a * x + 0 * y = a
        // a * 1 + 0 * 0 = a
        x = 1;
        y = 0;
        return a;
    }

    // Recurse until the remainder is 0 - found the gcd
    long long x1, y1;
    long long gcd = extendedGCD(b, a % b, x1, y1);

    // Return calls - update x and y and return up the stack
    // gcd(b, a % b) = (b * x) + ((a % b) * y) = gcd(a, b)
    // a % b = a - (a / b) * b
    // (b * x) + ((a - (a / b) * b) * y) = gcd(a, b)
    // (b * x) + (a * y) - ([a / b] * b * y)
    // (a * y) + b * (x) - b * ([a / b] * y)
    // a * y + b * (x - [a / b] * y)
    // Therefore:
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

/**
 * Helper function to ensure the modulus is greater than 1.
 */
void checkMod(long long m) {
    if (m <= 1)
        throw invalid_argument("Modulus must be greater than 1");
}

/**
 * Use if m is not prime but is coprime with b.
 * Do not call directly, use modInv wrapper function.
 */
long long modInvEEA(long long b, long long m) {
    long long x, y; // Find x, y where (b * x) - (m * y) = gcd(b, m)
    long long gcd = extendedGCD(b, m, x, y);
    return normalise(x, m); // Handle negative x
}

/**
 * Fast binary exponentiation using modular arithmetic
 */
long long modPow(long long b, long long exp, long long m) {
    checkMod(m);
    b = normalise(b, m);
    long long r = 1;
    while (exp > 0) {
        if (exp & 1) { // If odd, just multiply by the base
            r = (r * b) % m;
        }
        b = (b * b) % m; // Otherwise, square the base and halve the exponent
        exp >>= 1;
    }
    return r;
}

/**
 * Use if m is prime.
 * Do not call directly, use modInv wrapper function.
 */
long long modInvFermat(long long b, long long m) {
    long long exp = m - 2; // b^-1 is modular congruent with b^m-2 mod m
    return modPow(b, exp, m);
}

/**
 * This is a wrapper around Fermat's Little Theorem and the Extended Euclidean
 * Algorithm. Ensure that m is coprime with b. If m is prime, it will use
 * Fermat's, otherwise it will use EEA.
 */
long long modInv(long long b, long long m, bool isPrime = false) {
    checkMod(m);
    // Inverse doesn't exist if base and modulus are not coprime
    if (gcd(b, m) != 1)
        throw invalid_argument("modInv: b and m are not coprime!");
    b = normalise(b, m);
    if (isPrime)
        return modInvFermat(b, m);
    return modInvEEA(b, m);
}

/**
 * Easy if m is prime, otherwise ensure that it is coprime with b.
 */
long long modDivide(long long a, long long b, long long m, bool isPrime = false) {
    long long invB = modInv(b, m, isPrime);
    a = normalise(a, m);
    return (a * invB) % m; // Multiply by the inverse
}

long long modAdd(long long a, long long b, long long m) {
    checkMod(m);
    a = normalise(a, m);
    b = normalise(b, m);
    long long res = a + b;
    if (res >= m)
        res -= m;
    return res;
}

long long modSub(long long a, long long b, long long m) {
    checkMod(m);
    a = normalise(a, m);
    b = normalise(b, m);
    long long res = a - b;
    if (res < 0)
        res += m;
    return res;
}

/**
 * This could overflow, consider using uint_128.
 */
long long modMul(long long a, long long b, long long m) {
    checkMod(m);
    a = normalise(a, m);
    b = normalise(b, m);
    return (a * b) % m;
}

/**
 * Handy struct to precalculate modular factorials and their inverses.
 * Calculates all factorials and their inverses mod m up to n.
 * Also supports constant time nCr calculations.
 */
struct ModFact {
    vector<long long> fact, invFact;
    long long mod;

    ModFact(int n, long long m) : fact(n + 1), invFact(n + 1), mod(m) {
        checkMod(m);
        fact[0] = 1;
        for (int i = 1; i <= n; i++) {
            fact[i] = (fact[i - 1] * i) % mod;
        }
        // If mod is prime, otherwise ensure coprime and pass false
        invFact[n] = modInv(fact[n], mod, true);
        for (int i = (n - 1); i >= 0; i--) {
            invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
        }
    }

    long long nCr(int n, int r) {
        if (r > n || r < 0)
            return 0;
        return (fact[n] * ((invFact[r] * invFact[n - r]) % mod)) % mod;
    }
};

vector<long long> modInverseAll(int n, long long m) {
    checkMod(m);
    vector<long long> inv(n + 1, 1);
    for (int i = 2; i <= n; i++) {
        inv[i] = m - (m / i) * inv[m % i] % m;
    }
    return inv;
}

long long modCombination(long long n, long long r, long long m) {
    checkMod(m);
    if (r > n)
        return 0;
    long long numerator = 1, denominator = 1;
    for (long long i = 1; i <= r; i++) {
        numerator = (numerator * (n - i + 1)) % m;
        denominator = (denominator * i) % m;
    }
    return modDivide(numerator, denominator, m,
                     true); // If m prime, otherwise set false and ensure coprime
}

/**
 * Calculate the value that results in the remainders a[i] when divided by m[i]
 * for all i from 1 to the length of a and m.
 * Ensure that all m are pairwise coprime, and ensure that a and m have the same length.
 */
pair<long long, long long> crt(const vector<long long> &a, const vector<long long> &m) {
    size_t n = m.size();
    if (n != a.size()) {
        throw invalid_argument("Number of remainders and moduli do not match");
    }
    long long M = 1;
    for (int i = 0; i < n; i++) {
        checkMod(m[i]);
        M *= m[i];
    }
    long long x = 0;
    for (int i = 0; i < n; i++) {
        long long Mi = M / m[i];
        // Could potentially pre-compute modular inverses if there are many.
        x += modMul(modMul(a[i], Mi, M), modInv(Mi, m[i]), M);
    }
    return {normalise(x, M), M};
}

/**
 * Use when moduli are not coprime (otherwise use the function above).
 */
pair<long long, long long> generalisedCRT(const vector<long long> &a,
                                          const vector<long long> &m) {
    long long x = a[0];
    long long lcm = m[0];
    for (int i = 1; i < a.size(); i++) {
        long long x1, y1;
        long long g = extendedGCD(lcm, m[i], x1, y1);
        if ((a[i] - x) % g != 0) {
            throw invalid_argument("Congruences are incompatible");
        }
        long long mod = m[i] / g;
        long long delta = ((a[i] - x) / g) % mod;
        long long temp = (delta * x1) % mod;
        if (temp < 0)
            temp += mod;
        x += lcm * temp;
        lcm = (lcm / g) * m[i];
        x = normalise(x, lcm);
    }
    return {x, lcm};
}
