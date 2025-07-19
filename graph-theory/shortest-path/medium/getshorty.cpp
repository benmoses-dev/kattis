#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <queue>

using namespace std;

int main() {
    while (true) {
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0) break;
        
        vector<vector<pair<int, double>>> adjacencyList(n);
        for (int i = 0; i < m; i++) {
            int x, y;
            double f;
            cin >> x >> y >> f;
            // Take the log to convert it to a sum problem (log(x * y) = log(x) + log(y))
            double df = -log(f); // Take the negative as we need positive values (log(f) will be negative)
            
            // Build adjacency list - undirected graph
            adjacencyList[x].push_back({y, df});
            adjacencyList[y].push_back({x, df});
        }
        
        vector<double> distances(n, 1e18); // Set all nodes to (effective) infinity distance from start
        distances[0] = 0;
        
        // Use a min-priority queue to always process the next shortest path first
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq; // distance first so that it orders by distance, not node number!
        pq.push({0, 0});
        
        while (!pq.empty()) {
            // Get all neighbours of the next node
            pair<double, int> nextNode = pq.top();
            pq.pop(); // Remove so it doesn't get processed again
            if (nextNode.first > distances[nextNode.second]) continue;
            vector<pair<int, double>> neighbours = adjacencyList[nextNode.second];
            for (pair<int, double>& neighbour : neighbours) {
                // Update distance if shorter
                double currentDist = distances[neighbour.first];
                double newDist = nextNode.first + neighbour.second;
                if (newDist < currentDist) {
                    distances[neighbour.first] = newDist;
                    // Push this neighbour onto the pq (always expand outwards from the current shortest path)
                    pq.push({newDist, neighbour.first});
                }
            }
        }
        
        // The distance to the final node has now been calculated
        double finalDist = distances[n - 1];
        double finalMikael = -finalDist; // The closer to zero, the closer Mikael is to 1.0 (log(1) == 0)
        cout << fixed << setprecision(4) << exp(finalMikael) << "\n"; // Convert from logarithm back to 0 <= Mikael <= 1
    }
}
