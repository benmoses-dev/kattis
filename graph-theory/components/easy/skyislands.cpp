#include <iostream>
#include <queue>
#include <vector>

using namespace std;

bool bfs(vector<vector<int>> &adj) {
    size_t n = adj.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(0);

    size_t count = 0;
    while (!q.empty()) {
        int at = q.front();
        q.pop();

        if (visited[at]) {
            continue;
        }

        visited[at] = true;
        count++;

        for (const int &neighbour : adj[at]) {
            if (!visited[neighbour]) {
                q.push(neighbour);
            }
        }
    }

    return count == n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    cin >> N >> M;

    vector<vector<int>> adj(N);
    for (int m = 0; m < M; m++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    bool connected = bfs(adj);
    cout << (connected ? "YES" : "NO") << endl;
    return 0;
}
