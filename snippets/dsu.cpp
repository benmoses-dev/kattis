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