#include <cmath>
bool isPrime(int x) {
    if (x < 2)
        return false;
    int squirt = sqrt(x);
    for (int i = 2; i <= squirt; i++) {
        if (x % i == 0)
            return false;
    }
    return true;
}
