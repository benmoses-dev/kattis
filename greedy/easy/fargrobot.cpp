#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  cin.ignore();
  string colours;
  getline(cin, colours);
  int rgb[] = {0, 0, 0}; // To keep track of when we hit all colours (r, g, b)
  vector<char> cOrder;
  for (const char &c : colours) {
    if (n == 0)
      break;
    if (c == 'R')
      rgb[0] = 1;
    if (c == 'G')
      rgb[1] = 1;
    if (c == 'B')
      rgb[2] = 1;
    if (rgb[0] == 1 && rgb[1] == 1 && rgb[2] == 1) {
      cOrder.push_back(c);
      rgb[0] = 0;
      rgb[1] = 0;
      rgb[2] = 0;
      n--;
    }
  }
  for (const char &o : cOrder)
    cout << o;
  return 0;
}
