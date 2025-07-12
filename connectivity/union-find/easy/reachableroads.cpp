#include <iostream>
#include <vector>
#include <set>

using namespace std;

int find(int x, vector<int>& parents) {
    if (parents[x] != x) parents[x] = find(parents[x], parents);
    return parents[x];
}

void unite(int a, int b, vector<int>& parents) {
    int rootA = find(a, parents);
    int rootB = find(b, parents);
    if (rootA == rootB) return;
    parents[rootA] = rootB;
}

int main() {
    int n;
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        int m, r;
        cin >> m >> r;
        vector<int> parents(m); for (int j = 0; j < m; j++) parents[j] = j;
        
        for (int j = 0; j < r; j++) {
            int x, y;
            cin >> x >> y;
            unite(x, y, parents);
        }
        
        set<int> roots;
        for (int j = 0; j < m; j++) {
            int rootJ = find(j, parents);
            roots.insert(rootJ);
        }
        
        int connections = roots.size() - 1;
        cout << connections << "\n";
    }
    
    return 0;
}
