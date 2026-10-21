#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128_t;

struct Point {
    i64 x, y;

    bool operator<(const Point &other) const {
        return tie(x, y) < tie(other.x, other.y);
    }

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }
};

i128 cross(const Point &o, const Point &a, const Point &b) {
    i128 ax = (i128)a.x - o.x;
    i128 ay = (i128)a.y - o.y;
    i128 bx = (i128)b.x - o.x;
    i128 by = (i128)b.y - o.y;
    return ax * by - ay * bx;
}

i128 distance_squared(const Point &a, const Point &b) {
    i128 dx = (i128)a.x - b.x;
    i128 dy = (i128)a.y - b.y;
    return dx * dx + dy * dy;
}

// Returns the convex hull counter-clockwise, without collinear inner points.
vector<Point> convex_hull(vector<Point> points) {
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    if (points.size() <= 1) {
        return points;
    }

    vector<Point> hull(2 * points.size());
    int size = 0;
    for (const Point &p : points) {
        while (size >= 2 && cross(hull[size - 2], hull[size - 1], p) <= 0) {
            --size;
        }
        hull[size++] = p;
    }
    int lower_size = size;
    for (int i = (int)points.size() - 2; i >= 0; --i) {
        while (size > lower_size && cross(hull[size - 2], hull[size - 1], points[i]) <= 0) {
            --size;
        }
        hull[size++] = points[i];
    }
    hull.resize(size - 1);
    return hull;
}

struct Diameter {
    Point a{}, b{};
    i128 squared_distance = 0;
};

Diameter convex_hull_diameter(vector<Point> points) {
    vector<Point> hull = convex_hull(move(points));
    int n = hull.size();
    if (n <= 1) {
        return {hull.empty() ? Point{} : hull[0], hull.empty() ? Point{} : hull[0], 0};
    }

    Diameter answer{hull[0], hull[1], distance_squared(hull[0], hull[1])};
    auto update = [&](int i, int j) {
        i128 d = distance_squared(hull[i], hull[j]);
        if (d > answer.squared_distance) {
            answer = {hull[i], hull[j], d};
        }
    };
    if (n == 2) {
        return answer;
    }

    int j = 1;
    for (int i = 0; i < n; ++i) {
        int next_i = (i + 1) % n;
        auto area = [&](int k) {
            return cross(hull[i], hull[next_i], hull[k]);
        };
        while (area((j + 1) % n) > area(j)) {
            j = (j + 1) % n;
        }
        update(i, j);
        update(next_i, j);
        if (area((j + 1) % n) == area(j)) {
            update(i, (j + 1) % n);
            update(next_i, (j + 1) % n);
        }
    }
    return answer;
}
