#include <cmath>

using namespace std;

// Used for error correction when carrying out floating point arithmetic
const double EPSILON = 1e-8;

// Geometry Helpers

bool equal(double a, double b) { return fabs(a - b) < EPSILON; }

struct Point {
    double x, y;

    bool operator<(const Point &other) const {
        if (!equal(x, other.x))
            return x < other.x;
        return y < other.y - EPSILON;
    }

    bool operator==(const Point &other) const {
        return equal(other.x, x) && equal(other.y, y);
    }

    bool operator!=(const Point &other) const { return !(*this == other); }
};

// Vector between two points
Point operator-(Point a, Point b) { return {a.x - b.x, a.y - b.y}; }

// Area of the parallelogram
double crossProduct(Point a, Point b) { return (a.x * b.y) - (a.y * b.x); }

struct Segment {
    Point start;
    Point end;
};

/**
 * Check whether two line segments intersect, and if so, compute the intersection point.
 *
 * Given two line segments, determine whether they intersect at a single point (excluding
 * colinear overlaps), and if they do, compute the intersection coordinates.
 *
 * This is carried out using parametric line equations:
 *   Segment 1: P(t) = start1 + t * vone, for t in [0, 1]
 *   Segment 2: Q(u) = start2 + u * vtwo, for u in [0, 1]
 *
 * Solve for t and u such that P(t) == Q(u) - the intersection point lies on both
 * segments.
 *
 * This reduces to a 2D cross-product system: start1 + t * vone = start2 + u * vtwo
 * => t = cross(startDiff, vtwo) / cross(vone, vtwo)
 * => u = cross(startDiff, vone) / cross(vone, vtwo)
 */
bool intersects(Segment one, Segment two, Point &intersection) {
    Point start1 = one.start;
    Point end1 = one.end;
    Point start2 = two.start;
    Point end2 = two.end;

    // Direction vectors of the two segments.
    Point vone = end1 - start1;
    Point vtwo = end2 - start2;

    // Area of the parallelogram formed by the two direction vectors
    double area = crossProduct(vone, vtwo);
    if (equal(area, 0))
        return false; // Segments are parallel or colinear

    Point startDiff = start2 - start1;

    /**
     * Parametric intersection derivation:
     *
     * Let P(t) = start1 + t * vone
     *     Q(u) = start2 + u * vtwo
     *
     * Find t and u such that P(t) = Q(u):
     *   => start1 + t * vone = start2 + u * vtwo
     *   => t * vone - u * vtwo = start2 - start1 = startDiff
     *
     * Take the cross product with vtwo:
     *   => cross(t * vone - u * vtwo, vtwo) = cross(startDiff, vtwo)
     *   => t * cross(vone, vtwo) = cross(startDiff, vtwo)
     *   => t = cross(startDiff, vtwo) / cross(vone, vtwo)
     *
     * Take the cross product with vone:
     *   => u = cross(startDiff, vone) / cross(vone, vtwo)
     */
    double t = crossProduct(startDiff, vtwo) / area;
    double u = crossProduct(startDiff, vone) / area;

    // Both t and u must be in [0, 1] for the intersection to lie on both segments
    if (t < 0 - EPSILON || t > 1 + EPSILON || u < 0 - EPSILON || u > 1 + EPSILON)
        return false;

    // Compute the intersection point using parametric form: P(t) = start1 + t * vone
    double distanceX = t * vone.x;
    double distanceY = t * vone.y;
    intersection = {start1.x + distanceX, start1.y + distanceY};

    return true;
}
