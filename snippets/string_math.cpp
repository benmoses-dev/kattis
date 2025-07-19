#include <climits>

int doMath(char op, int a, int b) {
    if (op == '-')
        return a - b;
    if (op == '+')
        return a + b;
    if (op == '*')
        return a * b;
    if (op == '/') {
        if (b == 0)
            return INT_MAX;
        return a / b;
    }
    return INT_MAX;
}
