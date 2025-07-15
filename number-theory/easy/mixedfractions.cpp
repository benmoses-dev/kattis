#include <iostream>

using namespace std;

int main() {
  while (true) {
    int n, d;
    cin >> n >> d;
    if (n == 0 && d == 0)
      break;

    int i = n / d;
    int r = n % d;
    cout << i << " " << r << " / " << d << "\n";
  }
  return 0;
}
