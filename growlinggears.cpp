#include <iostream>

using namespace std;

int main() {
  cin.sync_with_stdio(false);
  cin.tie(nullptr);
  int C;
  cin >> C;
  for (int c = 0; c < C; c++) {
    int n;
    cin >> n;
    double max = -1 * 1e+9;
    int index = -1;
    for (int i = 0; i < n; i++) {
      double a, b, c;
      cin >> a >> b >> c;
      a = -a;
      double R = -b / (2 * a);
      double T = (a * (R * R)) + (b * R) + c;
      if (T > max) {
        index = i;
        max = T;
      }
    }
    cout << index + 1 << endl;
  }
  return 0;
}

