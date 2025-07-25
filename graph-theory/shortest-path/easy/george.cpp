#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

vector<int> dijkstra(vector<vector<int>> &adj, int start, int n,
                     map<pair<int, int>, int> &george, int startTime) {
    vector<int> distances(n, INT_MAX);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({startTime, start});

    distances[start] = startTime;

    while (!pq.empty()) {
        auto [t, u] = pq.top();
        pq.pop();

        if (t > distances[u])
            continue;

        for (int v = 0; v < n; v++) {
            int time = adj[u][v];
            if (time == -1) {
                continue;
            }

            /**
             * Modify distance to take into account the amount of added time if george is
             * on this street.
             */
            int wait = 0;
            if (george.find({u, v}) != george.end()) {
                int gStart = george[{u, v}];
                int gEnd = gStart + time;
                if ((gStart <= t) && (gEnd > t)) {
                    wait = gEnd - t;
                }
            }

            int currTime = distances[v];
            int newTime = t + time + wait;

            if (newTime < currTime) {
                distances[v] = newTime;
                pq.push({newTime, v});
            }
        }
    }

    return distances;
}

int main() {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    int start, end, diff, G;
    cin >> start >> end >> diff >> G;
    start--; // Make intersections 0-indexed as we don't actually care about the number.
    end--;
    vector<vector<int>> adj(N, vector<int>(N, -1));
    vector<int> georgePath(G);
    map<pair<int, int>, int> george;

    for (int g = 0; g < G; g++) {
        int at;
        cin >> at;
        georgePath[g] = at - 1;
    }

    for (int m = 0; m < M; m++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u][v] = w;
        adj[v][u] = w;
    }

    int gTime = 0;
    for (int g = 0; g < G - 1; g++) {
        int u = georgePath[g];
        int v = georgePath[g + 1];
        int w = adj[u][v];
        george[{u, v}] = gTime;
        george[{v, u}] = gTime;
        gTime += w;
    }

    vector<int> dist = dijkstra(adj, start, N, george, diff);
    cout << dist[end] - diff << endl;

    return 0;
}
