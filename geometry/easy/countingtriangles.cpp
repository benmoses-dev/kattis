#include <cmath>
#include <iostream>
#include <vector>

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

bool intersects(Point start1, Point end1, Point start2, Point end2,
                Point &intersection) {
  Point r = end1 - start1;
  Point s = end2 - start2;
  double area = crossProduct(r, s);
  if (equal(area, 0))
    return false; // Parallel or colinear

  Point startDiff = start2 - start1;
  // P(t) = start1 + (t * r)
  // P(u) = start2 + (u * s)
  // We want P(u) == P(t)
  // start1 + (t * r) = start2 + (u * s)
  // => (t * r) - (u * s) = start2 - start1 = startDiff
  // => (t * r - u * s) x s = startDiff x s
  // => (t * (r x s)) - (u * (s x s)) = startDiff x s
  // => (t * (r x s)) - (u * 0) = startDiff x s
  // => t = (startDiff x s) / (r x s) = startDiff x s / area
  // => u = (startDiff x r) / (s x r) = startDiff x r / area
  double t = crossProduct(startDiff, s) / area;
  double u = crossProduct(startDiff, r) / area;

  // Both t and u need to be between 0 and 1 for the intersection point to be
  // along both segments
  if (t < 0 - EPSILON)
    return false;
  if (t > 1 + EPSILON)
    return false;
  if (u < 0 - EPSILON)
    return false;
  if (u > 1 + EPSILON)
    return false;

  // t is the intersection point along r, so just use the parametric for t to
  // find how far along it is
  double distanceX = t * r.x;
  double distanceY = t * r.y;
  intersection = {start1.x + distanceX, start1.y + distanceY};
  return true;
}

struct Segment {
  Point start;
  Point end;
};

int main() {
  while (true) {
    int n;
    cin >> n;
    if (n == 0)
      return 0;
    vector<Segment> segments(n);

    for (int i = 0; i < n; i++) {
      double x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;

      Point start = {x1, y1};
      Point end = {x2, y2};
      Segment segment;
      segment.start = start;
      segment.end = end;
      segments[i] = segment;
    }

    int triangleCount = 0;

    // Brute-force all triples of segments
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        for (int k = j + 1; k < n; ++k) {
          Point ab, bc, ac;

          // Check that all three pairs intersect pair-wise
          if (!intersects(segments[i].start, segments[i].end, segments[j].start,
                          segments[j].end, ab))
            continue;
          if (!intersects(segments[j].start, segments[j].end, segments[k].start,
                          segments[k].end, bc))
            continue;
          if (!intersects(segments[i].start, segments[i].end, segments[k].start,
                          segments[k].end, ac))
            continue;

          triangleCount++;
        }
      }
    }

    cout << triangleCount << "\n";
  }

  return 0;
}
