#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parents;
    vector<int> size;

    DSU(const vector<int> &values) {
        size_t n = values.size();
        parents.resize(n);
        iota(parents.begin(), parents.end(), 0);
        size.assign(n, 1);
    }

    int find(int x) {
        if (parents[x] != x)
            parents[x] = find(parents[x]);
        return parents[x];
    }

    void unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA == rootB)
            return;
        if (size[rootA] < size[rootB]) {
            swap(rootA, rootB);
        }
        parents[rootB] = rootA;
        size[rootA] += size[rootB];
    }

    int getSize(int i) { return size[find(i)]; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    cin >> N >> M;

    vector<int> houses(N);
    iota(houses.begin(), houses.end(), 0);
    DSU dsu(houses);

    for (int m = 0; m < M; m++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        dsu.unite(a, b);
    }

    if (dsu.getSize(0) == N) {
        cout << "Connected" << endl;
        return 0;
    }

    int first = dsu.find(0);
    for (const int house : houses) {
        if (dsu.find(house) != first) {
            cout << (house + 1) << endl;
        }
    }

    return 0;
}
