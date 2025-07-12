#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

// Used for error correction when carrying out floating point arithmetic
const double EPSILON = 1e-8;

// Geometry Helpers

bool equal(double a, double b) { return fabs(a - b) < EPSILON; }

struct Point {
  double x, y;
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
  intersection = {start1.x + t * r.x, start1.y + t * r.y};
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

    vector<Point> intersections;
    vector<vector<int>> adjacencyList;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        Point intersection;
        if (intersects(segments[i].start, segments[i].end, segments[j].start,
                       segments[j].end, intersection)) {
          intersections.push_back(intersection);
        }
      }
    }

    adjacencyList.resize(intersections.size());
    // Iterate through each segment line and update the adjacency list using all
    // intersections along the line
    for (int i = 0; i < segments.size(); i++) {
      Segment segment = segments[i];

      vector<pair<double, int>> pointsAlongSegment;

      Point u = segment.start;
      Point v = segment.end;
      Point r = v - u;

      for (int j = 0; j < intersections.size(); j++) {
        Point intersection = intersections[j];

        // P = start1 + (t * r)
        // t = (start1 - P(t)) / r
        double t;
        if (r.x > r.y) {
          t = (u.x - intersection.x) / r.x;
        } else {
          t = (u.y - intersection.y) / r.y;
        }
        if (t < 0 - EPSILON || t > 1 + EPSILON)
          continue;

        pointsAlongSegment.push_back({t, j});
      }

      sort(pointsAlongSegment.begin(), pointsAlongSegment.end());
      int first = pointsAlongSegment[0].second;
      for (const auto &point : pointsAlongSegment) {
        if (point.second == pointsAlongSegment[0].second)
          continue;
        int second = point.second;
        adjacencyList[first].push_back(second);
        adjacencyList[second].push_back(first);
        first = second;
      }
    }

    set<tuple<int, int, int>> triangles;
    for (int u = 0; u < adjacencyList.size(); u++) {
      vector<int> uList = adjacencyList[u];
      for (int v = 0; v < uList.size(); v++) {
        vector<int> vList = adjacencyList[uList[v]];
        for (int w = 0; w < vList.size(); w++) {
          vector<int> wList = adjacencyList[vList[w]];
          for (const int &last : wList) {
            if (last == u) {
              vector<int> tri = {u, v, w};
              sort(tri.begin(), tri.end());
              // Prevent duplicates if the triangles are walked in a different
              // order
              triangles.insert({tri[0], tri[1], tri[2]});
              break;
            }
          }
        }
      }
    }
  }
}
