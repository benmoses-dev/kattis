#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

char ops[] = {'-', '+', '*', '/'};

int doMath(char op, int a, int b) {
    if (op == '-') return a - b;
    if (op == '+') return a + b;
    if (op == '*') return a * b;
    if (op == '/') {
        if (b == 0) return 1000000;
        return a / b;
    }
    return 1000000;
}

int main() {
    map<int, string> values;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                vector<char> operands = {ops[i], ops[j], ops[k]};
                vector<int> nums(4, 4);
                for (int x = 0; x < operands.size(); x++) {
                    if (operands[x] == '*' || operands[x] == '/') {
                        nums[x] = doMath(operands[x], nums[x], nums[x + 1]);
                        nums.erase(nums.begin() + x + 1);
                        operands.erase(operands.begin() + x);
                        x--;
                    }
                }
                for (int x = 0; x < operands.size(); x++) {
                    if (operands[x] == '+' || operands[x] == '-') {
                        nums[x] = doMath(operands[x], nums[x], nums[x + 1]);
                        nums.erase(nums.begin() + x + 1);
                        operands.erase(operands.begin());
                        x--;
                    }
                }
                string calculation = "4 " + string(1, ops[i]) + " 4 " + string(1, ops[j]) + " 4 " + string(1, ops[k]) + " 4 = " + to_string(nums[0]);
                values.insert({nums[0], calculation});
            }
        }
    }
    
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int n;
        cin >> n;
        if (values.contains(n)) {
            cout << values.at(n) << "\n";
            continue;
        }
        cout << "no solution\n";
    }
    return 0;
}
