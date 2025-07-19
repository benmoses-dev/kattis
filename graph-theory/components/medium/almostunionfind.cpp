#include <iostream>
#include <vector>

using namespace std;

vector<int> parents;
vector<int> sizes;
vector<long long> sums; // This can get very large
vector<int> actual;
int actualCounter;

int find(int a) {
    if (parents[a] != a) {
        parents[a] = find(parents[a]);
    }
    return parents[a];
}

void unite(int p, int q) {
    p = actual[p];
    q = actual[q];
    int rootP = find(p);
    int rootQ = find(q);
    if (rootP == rootQ) return;
    parents[rootP] = rootQ;
    sizes[rootQ] += sizes[rootP];
    sizes[rootP] = 0;
    sums[rootQ] += sums[rootP];
    sums[rootP] = 0;
}

void move(int p, int q) {
    int actualP = actual[p];
    int rootP = find(actualP);
    int actualQ = actual[q];
    int rootQ = find(actualQ);
    if (rootP == rootQ) return;
    
    sums[rootP] -= p;
    sizes[rootP] --;
    
    int newID = actualCounter++;
    actual[p] = newID; // Use this to track the real p, parents[p] just holds a component id
    parents[newID] = rootQ;
    sizes[newID] = 0; // Initialise but leave empty - it is in the set of rootQ now
    sums[newID] = 0;
    
    sums[rootQ] += p;
    sizes[rootQ] ++;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        int maxN = n + m + 1;
        parents.assign(maxN, 0);
        sizes.assign(maxN, 0);
        sums.assign(maxN, 0);
        actual.assign(n + 1, 0);
        actualCounter = n + 1;
        for (int i = 1; i <= n; i++) {
            parents[i] = i;
            sizes[i] = 1;
            sums[i] = i;
            actual[i] = i;
        }
        for (int k = 0; k < m; k++) {
            int x, p;
            cin >> x >> p;
            if (x == 1) {
                int q;
                cin >> q;
                unite(p, q);
            }
            if (x == 2) {
                int q;
                cin >> q;
                move(p, q);
            }
            if (x == 3) {
                int actualP = actual[p];
                int rootP = find(actualP);
                cout << sizes[rootP] << " " << sums[rootP] << "\n";
            }
        }
    }
}

