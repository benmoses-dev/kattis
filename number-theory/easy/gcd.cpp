#include <iostream>

using namespace std;

long long GCD(long long a, long long b) {
  if (b == 0) {
    return a;
  }
  return GCD(b, a % b);
}

int main() {
  long long n, e;
  cin >> n >> e;
  long long d = GCD(n, e);
  cout << d << "\n";
}
