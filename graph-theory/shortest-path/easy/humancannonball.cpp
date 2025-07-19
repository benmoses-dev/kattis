#include <iomanip>
#include <vector>
#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

struct Point {
    double x, y;
    bool cannon;
};

double getDistance(Point a, Point b) {
    double distX = fabs(b.x - a.x);
    double distY = fabs(b.y - a.y);
    return sqrt(distX * distX + distY * distY);
}

double getSeconds(Point a, Point b) {
    double dist = getDistance(a, b);
    double w = dist / 5.0;
    if (!a.cannon) return w;
    dist = fabs(dist - 50.0);
    double f = dist / 5.0 + 2.0;
    return min(w, f);
}

int main() {
    Point start;
    start.cannon = false;
    cin >> start.x >> start.y;
    Point end;
    end.cannon = false;
    cin >> end.x >> end.y;

    int n;
    cin >> n;

    vector<vector<double>> adjacencyList(n + 2, vector<double>(n + 2, 1e+10));
    vector<Point> points(n + 2);

    points[0] = start;
    points[n + 1] = end;

    for (int i = 0; i < n; i++) {
        Point p;
        p.cannon = true;
        cin >> p.x >> p.y;
        points[i + 1] = p;
    }

    for (int i = 0; i < points.size(); i++) {
        for (int j = 0; j < points.size(); j++) {
            if (i == j) adjacencyList[i][j] = 0.0;
            adjacencyList[i][j] = getSeconds(points[i], points[j]);
        }
    }

    // Dijkstra
    vector<double> distances(n + 2, 1e+10); // Set all nodes to (effective) infinity
    distances[0] = 0.0;
        
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({0.0, 0});
    
    while (!pq.empty()) {
        auto nextNode = pq.top();
        pq.pop();
        if (nextNode.first > distances[nextNode.second]) continue; // Stale value on queue
        
        // Process neighbours
        for (int i = 0; i < points.size(); i++) {
            double neighbourDist = adjacencyList[nextNode.second][i];
            double currentDist = distances[i];
            double newDist = nextNode.first + neighbourDist;
            if (newDist < currentDist) {
                distances[i] = newDist;
                pq.push({newDist, i});
            }
        }
    }
    
    cout << fixed << setprecision(6) << distances[n + 1] << "\n";
    return 0;
}
