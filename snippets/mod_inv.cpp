#include <stdexcept>

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

long long modInv(long long b, long long m) {
  // Find x, y where (b * x) - (m * y) = gcd(b, m)
  long long x, y;
  long long gcd = extendedGCD(b, m, x, y);

  if (gcd != 1) {
    return -1; // Inverse doesn't exist if base and modulus are not coprime
  }

  // Handle negative x
  return (x % m + m) % m;
}

long long modFermat(long long b, long long m) {
    long long result = 1;
    long long exponent = m - 2;
    b %= m;
    while (exponent > 0) {
        if (exponent & 1) result = (result * b) % m;
        b = (b * b) % m;
        exponent = exponent >> 1;
    }
    return result;
}

long long modDivide(long long a, long long b, long long m) {
    a %= m;
    long long invB = modInv(b, m);
    if (invB == -1) {
        throw invalid_argument('Invalid Division');
    }
    return (a * invB) % m;
}
