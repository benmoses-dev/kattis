#include <cmath>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vpii = vector<pii>;
using pdd = pair<double, double>;
using vpdd = vector<pdd>;

const double EPSILON = 1e-9;

bool approxEqual(double a, double b) { return fabs(a - b) < EPSILON; }

ll cross(pii a, pii b, pii c) {
    ll x1 = b.first - a.first;
    ll y1 = b.second - a.second;
    ll x2 = c.first - a.first;
    ll y2 = c.second - a.second;
    return x1 * y2 - x2 * y1;
}

double cross(pdd a, pdd b, pdd c) {
    double x1 = b.first - a.first;
    double y1 = b.second - a.second;
    double x2 = c.first - a.first;
    double y2 = c.second - a.second;
    return x1 * y2 - x2 * y1;
}

bool onSegment(pii a, pii b, pii p) {
    return cross(a, b, p) == 0 && min(a.first, b.first) <= p.first &&
           p.first <= max(a.first, b.first) && min(a.second, b.second) <= p.second &&
           p.second <= max(a.second, b.second);
}

bool onSegment(pdd a, pdd b, pdd p) {
    if (fabs(cross(a, b, p)) > EPSILON) {
        return false;
    }
    double minX = min(a.first, b.first);
    double maxX = max(a.first, b.first);
    double minY = min(a.second, b.second);
    double maxY = max(a.second, b.second);
    return p.first + EPSILON >= minX && p.first - EPSILON <= maxX &&
           p.second + EPSILON >= minY && p.second - EPSILON <= maxY;
}

/**
 * Simplest method for non-self-intersecting arbitrary polygons given using integer
 * vertices.
 */
bool rcpip(const vpii &poly, pii p) {
    int n = poly.size();
    bool inside = false;

    for (int i = 0, j = n - 1; i < n; j = i++) {
        pii a = poly[j];
        pii b = poly[i];

        if (onSegment(a, b, p)) {
            return true;
        }

        if ((a.second > p.second) != (b.second > p.second)) {
            ll orient = cross(a, b, p);
            if ((b.second > a.second) == (orient > 0)) {
                inside = !inside;
            }
        }
    }
    return inside;
}

/**
 * Use this if the inputs are floating point numbers, otherwise use the integer version
 * below.
 * Assumes vertices are given in CCW winding order.
 */
bool wnpip(const vpdd &poly, pdd p) {
    int wn = 0;
    int n = poly.size();

    for (int i = 0; i < n; ++i) {
        pdd a = poly[i];
        pdd b = poly[(i + 1) % n];

        if (onSegment(a, b, p)) {
            return true;
        }

        if (a.second <= p.second) {
            if (b.second > p.second && cross(a, b, p) > EPSILON) { // < -EPSILON if CW.
                wn++;
            }
        } else {
            if (b.second <= p.second && cross(a, b, p) < -EPSILON) { // > EPSILON if CW.
                wn--;
            }
        }
    }

    return wn != 0;
}

/**
 * Integer-based winding number algorithm to check whether a point is within an arbitrary
 * polygon.
 * Use this if inputs are integers.
 * Can be used on regular or irregular polygons.
 * Polygons do not need to be convex and they can include self-intersections.
 * Assumes vertices are given in CCW winding order.
 */
bool iwnpip(const vpii &poly, pii p) {
    int wn = 0;
    int n = poly.size();

    for (int i = 0; i < n; ++i) {
        pii a = poly[i];
        pii b = poly[(i + 1) % n];

        if (onSegment(a, b, p))
            return true;

        if (a.second <= p.second) {
            if (b.second > p.second && cross(a, b, p) > 0) { // < 0 if CW.
                wn++;
            }
        } else {
            if (b.second <= p.second && cross(a, b, p) < 0) { // > 0 if CW.
                wn--;
            }
        }
    }

    return wn != 0;
}

/**
 * Simple orientation check for a point in a convex polygon.
 * Use if given arbitrary vertices.
 * Assumes vertices are given in CCW winding order.
 */
bool simplepicp(const vpii &poly, pii p) {
    int n = poly.size();

    for (int i = 0; i < n; ++i) {
        pii a = poly[i];
        pii b = poly[(i + 1) % n];

        if (onSegment(a, b, p)) {
            return true;
        }

        if (cross(a, b, p) < 0) {
            return false; // Assuming CCW order. Change to > 0 if CW.
        }
    }

    return true;
}

/**
 * Use instead of above if given floating point numbers for vertices.
 * Assumes vertices are given in CCW winding order.
 */
bool simplepicp(const vpdd &poly, pdd p) {
    int n = poly.size();

    for (int i = 0; i < n; ++i) {
        pdd a = poly[i];
        pdd b = poly[(i + 1) % n];

        if (onSegment(a, b, p)) {
            return true;
        }

        if (cross(a, b, p) < -EPSILON) {
            return false; // Assuming CCW order. Change to > EPSILON if CW.
        }
    }

    return true;
}

/**
 * Binary search version for point in convex polygon. Vertices must be in winding order.
 * Assumes vertices are given in CCW winding order.
 */
bool binarypicp(const vpii &poly, pii p) {
    int n = poly.size();
    pii p0 = poly[0];

    if (cross(p0, poly[1], p) < 0) { // > 0 if CW.
        return false;
    }

    if (cross(p0, poly[n - 1], p) > 0) { // < 0 if CW.
        return false;
    }

    // Binary search between vertices 1 and n-1
    int low = 1;
    int high = n - 1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (cross(p0, poly[mid], p) > 0) { // < 0 if CW.
            low = mid;
        } else {
            high = mid;
        }
    }

    // Check if point lies inside triangle (p0, poly[low], poly[high])
    pii a = poly[low];
    pii b = poly[high];

    // Handle edge cases for point on edge
    if (onSegment(a, b, p) || onSegment(p0, a, p) || onSegment(p0, b, p)) {
        return true;
    }

    return cross(a, b, p) >= 0; // Use <= if vertices are in CW order.
}

/**
 * Floating point version (for example, lat and lon).
 * Assumes vertices are given in CCW winding order.
 */
bool binarypicp(const vpdd &poly, pdd p) {
    int n = poly.size();
    pdd p0 = poly[0];

    if (cross(p0, poly[1], p) < -EPSILON) { // Use > EPSILON if CW.
        return false;
    }

    if (cross(p0, poly[n - 1], p) > EPSILON) { // Use < -EPSILON if CW.
        return false;
    }

    int low = 1;
    int high = n - 1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (cross(p0, poly[mid], p) > EPSILON) { // Use < -EPSILON if CW.
            low = mid;
        } else {
            high = mid;
        }
    }

    pdd a = poly[low];
    pdd b = poly[high];

    if (onSegment(a, b, p) || onSegment(p0, a, p) || onSegment(p0, b, p)) {
        return true;
    }

    return cross(a, b, p) > -EPSILON; // Use < EPSILON if vertices are in CW order.
}

/**
 * Quick point in regular hexagon, assuming flat-top.
 * Would need to be rotated first if not flat-topped (probably just use orientation
 * checks).
 * Need the center point as well as the vertices.
 */
bool pirhexagon(double px, double py, double cx, double cy, double s) {
    // Translate to hexagon-centered coordinates
    double x = px - cx;
    double y = py - cy;

    // Hexagon bounding logic (flat-topped)
    double sqrt3 = sqrt(3.0);

    if (abs(x) > s) {
        return false;
    }
    if (abs(y) > sqrt3 * s / 2.0) {
        return false;
    }
    if (sqrt3 * abs(x) + abs(y) > sqrt3 * s) {
        return false;
    }

    return true;
}
