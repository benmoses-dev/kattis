#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int getDist(pair<double, double> a, pair<double, double> b) {
    double xDiff = fabs(b.first - a.first);
    double yDiff = fabs(b.second - a.second);
    double distance = sqrt((xDiff * xDiff) + (yDiff * yDiff));
    return static_cast<int>(round(distance));
}

vector<int> greedyTour(const int N, const vector<pair<double, double>> cities) {
    vector<int> tour(N, -1);
    vector<bool> visited(N, false);
    tour[0] = 0;
    visited[0] = true;
    for (int i = 1; i < N; i++) {
        int best = -1;
        int bestDist = INT_MAX;
        for (int j = 0; j < N; j++) {
            if (visited[j])
                continue;

            int distance = getDist(cities[tour[i - 1]], cities[j]);
            if (distance < bestDist) {
                best = j;
                bestDist = distance;
            }
        }
        tour[i] = best;
        visited[best] = true;
    }
    return tour;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;

    vector<pair<double, double>> cities(N);
    for (int n = 0; n < N; n++) {
        cin >> cities[n].first >> cities[n].second;
    }

    vector<int> tour = greedyTour(N, cities);

    for (const int &city : tour) {
        cout << city << endl;
    }

    return 0;
}
