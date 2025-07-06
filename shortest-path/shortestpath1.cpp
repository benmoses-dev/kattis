#include <vector>
#include <iostream>
#include <queue>
#include <climits>

using namespace std;

int main() {
    int loop = 0;
    while (true) {
        int n, m, q, s;
        cin >> n >> m >> q >> s;
        if (n == 0 && m == 0 && q == 0 && s == 0) break;
        
        loop++;
        if (loop > 1) {
            cout << "\n";
        }
        vector<vector<pair<int, int>>> adjacencyList(n);
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            
            adjacencyList[u].push_back({v, w}); // Directed adjacency list
        }
        
        vector<int> distances(n, INT_MAX); // Set all nodes to (effective) infinity
        distances[s] = 0; // s is the start node
        
        // Use a min-priority queue for efficiency
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, s});
        
        while (!pq.empty()) {
            auto nextNode = pq.top();
            pq.pop(); // Remove so it doesn't get processed again
            if (nextNode.first > distances[nextNode.second]) continue; // Stale value on queue
            
            // Process neighbours
            for (const auto& neighbour : adjacencyList[nextNode.second]) {
                int currentDist = distances[neighbour.first];
                int newDist = nextNode.first + neighbour.second;
                if (newDist < currentDist) {
                    // Update the distance list with the new value (this path is shorter)
                    distances[neighbour.first] = newDist;
                    // Push this neighbour onto the pq (process the closest neighbour next)
                    pq.push({newDist, neighbour.first});
                }
            }
        }
        
        // Get the distances from s to each query
        for (int i = 0; i < q; i++) {
            int last;
            cin >> last;
            if (distances[last] == INT_MAX) {
                cout << "Impossible\n";
            } else {
                cout << distances[last] << "\n";
            }
        }
    }
}
