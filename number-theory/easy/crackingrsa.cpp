#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

bool isPrime(int num) {
  int squirt = sqrt(num);
  for (int m = 2; m <= squirt; m++) {
    if (num % m == 0) {
      return false;
    }
  }
  return true;
}

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

long long modInverse(long long b, long long m) {
  // Find x where (a * x) - (b * y) = gcd(a, b)
  long long x, y;
  long long gcd = extendedGCD(b, m, x, y);

  if (gcd != 1) {
    return -1; // Inverse doesn't exist if base and modulus are not coprime
  }

  // Handle negative x
  return (x % m + m) % m;
}

int main() {
  vector<int> primes;

  // Initialise prime numbers
  for (int i = 2; i <= 1000; i++) {
    if (isPrime(i)) {
      primes.push_back(i);
    }
  }

  int cases;
  cin >> cases;

  for (int j = 0; j < cases; j++) {
    long n, e;
    cin >> n >> e;
    int p, q;
    long long eulerN;
    for (int k = 0; k < primes.size() - 1; k++) {
      if (n % primes[k] == 0) {
        p = primes[k];
        q = n / p;
        break;
      }
    }
    eulerN = (p - 1) * (q - 1);
    long long d = modInverse(e, eulerN);
    cout << d << "\n";
  }
}
