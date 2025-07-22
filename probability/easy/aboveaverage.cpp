#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int C;
    cin >> C;
    for (int c = 0; c < C; c++) {
        int N;
        cin >> N;
        vector<int> grades(N, -1);
        double total = 0;
        for (int n = 0; n < N; n++) {
            cin >> grades[n];
            total += grades[n];
        }
        double average = total / N;
        sort(grades.begin(), grades.end(), greater<double>());
        double aboveAverage = 0.0;
        for (const double &grade : grades) {
            if (grade > average) {
                aboveAverage++;
            }
        }
        double percent = (aboveAverage / N) * 100;
        cout << fixed << setprecision(3) << percent << "%" << endl;
    }
    return 0;
}
