#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;

  while (true) {
    vector<int> digits;
    int t = n;

    while (true) {
      if (t < 10) {
        digits.push_back(t);
        break;
      }

      int next = t % 10;
      digits.push_back(next);
      t /= 10;
    }

    long long total = 0;
    for (const int &d : digits) {
      total += d;
    }

    if (n % total == 0) {
      cout << n << "\n";
      break;
    }

    n++;
  }

  return 0;
}
