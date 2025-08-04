#include <numeric>
#include <vector>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

struct DSU {
    vi parents;
    vi size;
    vi maxVal;
    vll sums;
    int numComponents;

    DSU(const vi &values) {
        int n = values.size();
        parents.resize(n);
        iota(parents.begin(), parents.end(), 0);
        size.assign(n, 1);
        maxVal.resize(n);
        sums.resize(n);
        for (int i = 0; i < n; i++) {
            maxVal[i] = values[i];
            sums[i] = values[i];
        }
        numComponents = n;
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
        sums[rootA] += sums[rootB];
        maxVal[rootA] = max(maxVal[rootA], maxVal[rootB]);
        maxVal[rootB] = 0;
        numComponents--;
    }

    int getSize(int i) { return size[find(i)]; }

    int getMaxVal(int i) { return maxVal[find(i)]; }

    ll getSum(int i) { return sums[find(i)]; }

    int getComponents() { return numComponents; }
};
