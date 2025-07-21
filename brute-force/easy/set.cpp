#include <cstdio>
#include <vector>

using namespace std;

int main() {
    char shape[] = {'D', 'S', 'O'};
    char pattern[] = {'S', 'T', 'O'};
    char colour[] = {'R', 'G', 'P'};

    // Read in the cards, mapping characters to numbers.
    vector<vector<int>> cards(12);
    for (int i = 0; i < 12; i++) {
        vector<int> card(4, -1);
        int A;
        char B, C, D;
        scanf("%d%c%c%c", &A, &B, &C, &D);
        card[0] = A;
        for (int s = 0; s < 3; s++) {
            if (shape[s] == B)
                card[1] = s;
        }
        for (int p = 0; p < 3; p++) {
            if (pattern[p] == C)
                card[2] = p;
        }
        for (int c = 0; c < 3; c++) {
            if (colour[c] == D)
                card[3] = c;
        }
        cards[i] = card;
    }

    // Brute force all combinations.
    int count = 0;
    for (int x = 0; x < 12; x++) {
        for (int y = x + 1; y < 12; y++) {
            for (int z = y + 1; z < 12; z++) {
                auto cardA = cards[x];
                auto cardB = cards[y];
                auto cardC = cards[z];
                bool passed = true;
                for (int i = 0; i < 4; i++) {
                    if (!((cardA[i] == cardB[i] && cardB[i] == cardC[i]) ||
                          (cardA[i] != cardB[i] && cardB[i] != cardC[i]) &&
                              cardA[i] != cardC[i])) {
                        passed = false;
                        break;
                    }
                }
                if (passed == true) {
                    printf("%d %d %d\n", x + 1, y + 1, z + 1);
                    count++;
                }
            }
        }
    }

    if (count == 0) {
        printf("no sets\n");
    }

    return 0;
}
