#include <iostream>

using namespace std;

void cutTwoHeads(int &H, int &moves) {
    H -= 2;
    moves++;
}
void cutTail(int &T, int &moves) {
    T++;
    moves++;
}
void cutTwoTails(int &H, int &T, int &moves) {
    T -= 2;
    H++;
    moves++;
}

int main() {
    while (true) {
        int H, T;
        cin >> H >> T;

        if (H == 0 && T == 0) {
            return 0;
        }

        // The goal is to remove all tails and have an even number of heads remaining.
        int moves = 0;
        while (H > 0 || T > 0) {
            if (T > 2) {
                cutTwoTails(H, T, moves);
                continue;
            }
            if (T == 2) {
                if (H % 2 == 0) {
                    cutTail(T, moves);
                    continue;
                }
                cutTwoTails(H, T, moves);
                continue;
            }
            if (T == 1) {
                cutTail(T, moves);
                continue;
            }
            if (H % 2 == 0) {
                cutTwoHeads(H, moves);
                continue;
            } else {
                cout << -1 << endl;
                break;
            }
        }

        cout << moves << endl;
    }

    return 0;
}
