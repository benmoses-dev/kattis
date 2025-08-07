#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vpii = vector<pii>;

ll cross(pii a, pii b, pii c) {
    ll x1 = b.first - a.first;
    ll y1 = b.second - a.second;
    ll x2 = c.first - a.first;
    ll y2 = c.second - a.second;
    return x1 * y2 - x2 * y1;
}

bool onSegment(pii a, pii b, pii p) {
    if (cross(a, b, p) != 0)
        return false;
    int minX = min(a.first, b.first);
    int maxX = max(a.first, b.first);
    int minY = min(a.second, b.second);
    int maxY = max(a.second, b.second);
    return minX <= p.first && p.first <= maxX && minY <= p.second && p.second <= maxY;
}

int iwnpip(const vpii &poly, pii p, bool ccw) {
    int wn = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        pii a = poly[i];
        pii b = poly[(i + 1) % n];
        if (onSegment(a, b, p)) {
            return 2;
        }
        bool aBelow = a.second <= p.second;
        bool bAbove = b.second > p.second;
        ll c = cross(a, b, p);
        bool leftTurn = c > 0;
        bool rightTurn = c < 0;
        if (aBelow && bAbove && (leftTurn ^ !ccw)) {
            wn++;
            continue;
        }
        bool aAbove = !aBelow;
        bool bBelow = !bAbove;
        if (aAbove && bBelow && (rightTurn ^ !ccw)) {
            wn--;
        }
    }
    if (wn == 0) {
        return 0;
    }
    return 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int n;
        cin >> n;
        if (n == 0)
            break;

        vpii poly;
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            poly.emplace_back(x, y);
        }
        bool ccw = poly[0].first > poly[1].first;

        int m;
        cin >> m;

        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            int inside = iwnpip(poly, {x, y}, ccw);
            if (inside == 0) {
                cout << "out" << endl;
                continue;
            }
            if (inside == 1) {
                cout << "in" << endl;
                continue;
            }
            cout << "on" << endl;
        }
    }

    return 0;
}
