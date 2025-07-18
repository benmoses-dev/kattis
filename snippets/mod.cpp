#include <numeric>
#include <stdexcept>
#include <vector>

using namespace std;

// EEA to find gcd and Bezout coefficients
// gcd(a, b) = gcd(b, a % b)
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

long long modInvEEA(long long b, long long m) {
  b = (b % m + m) % m;
  // Find x, y where (b * x) - (m * y) = gcd(b, m)
  long long x, y;
  long long gcd = extendedGCD(b, m, x, y);

  if (gcd != 1)
    return -1; // Inverse doesn't exist if base and modulus are not coprime

  // Handle negative x
  return (x % m + m) % m;
}

long long modPow(long long b, long long exp, long long m) {
  if (m <= 1) {
    throw invalid_argument("Modulus must be greater than 1");
  }
  b = (b % m + m) % m; // Normalise for negative values and take modulus m
  long long r = 1;
  while (exp > 0) {
    if (exp & 1) // If odd, just multiply by the base
      r = (r * b) % m;
    // Otherwise, square the base and halve the exponent
    b = (b * b) % m;
    exp >>= 1;
  }
  return r;
}

long long modInvFermat(long long b, long long m) { // m must be prime
  b = (b % m + m) % m; // Normalise for negative values and take modulus m
  if (gcd(b, m) != 1)
    return -1;
  long long exp = m - 2; // b^-1 is modular congruent with b^m-2 mod m
  return modPow(b, exp, m);
}

long long modInv(long long b, long long m, bool isPrime = false) {
  if (m <= 1) {
    throw invalid_argument("Modulus must be greater than 1");
  }
  if (isPrime)
    return modInvFermat(b, m);
  return modInvEEA(b, m);
}

long long modDivide(long long a, long long b, long long m,
                    bool isPrime = false) {
  if (m <= 1) {
    throw invalid_argument("Modulus must be greater than 1");
  }
  a = (a % m + m) % m;
  long long invB = modInv(b, m, isPrime);
  if (invB == -1) {
    throw invalid_argument("Invalid Division");
  }
  return (a * invB) % m;
}

long long modAdd(long long a, long long b, long long m) {
  if (m <= 1) {
    throw invalid_argument("Modulus must be greater than 1");
  }
  a = (a % m + m) % m;
  b = (b % m + m) % m;
  long long res = a + b;
  if (res >= m)
    res -= m;
  return res;
}

long long modSub(long long a, long long b, long long m) {
  if (m <= 1) {
    throw invalid_argument("Modulus must be greater than 1");
  }
  a = (a % m + m) % m;
  b = (b % m + m) % m;
  long long res = a - b;
  if (res < 0)
    res += m;
  return res;
}

long long modMul(long long a, long long b, long long m) {
  if (m <= 1) {
    throw invalid_argument("Modulus must be greater than 1");
  }
  a = (a % m + m) % m;
  b = (b % m + m) % m;
  return (a * b) % m;
}

struct ModFact {
  vector<long long> fact, invFact;
  long long mod;

  ModFact(int n, long long m) : fact(n + 1), invFact(n + 1), mod(m) {
    if (m <= 1) {
      throw invalid_argument("Modulus must be greater than 1");
    }
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
      fact[i] = (fact[i - 1] * i) % mod;
    }
    invFact[n] = modInv(fact[n], mod, true); // If mod is prime
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

vector<long long> modInverseAll(int n, long long m) { // m must be prime here
  if (m <= 1) {
    throw invalid_argument("Modulus must be greater than 1");
  }
  vector<long long> inv(n + 1, 1);
  for (int i = 2; i <= n; i++) {
    inv[i] = m - (m / i) * inv[m % i] % m;
  }
  return inv;
}

long long modCombination(long long n, long long r, long long m) {
  if (m <= 1) {
    throw invalid_argument("Modulus must be greater than 1");
  }
  if (r > n)
    return 0;
  long long numerator = 1, denominator = 1;
  for (long long i = 1; i <= r; i++) {
    numerator = (numerator * (n - i + 1)) % m;
    denominator = (denominator * i) % m;
  }
  return modDivide(numerator, denominator, m,
                   true); // If m prime, otherwise set false
}
