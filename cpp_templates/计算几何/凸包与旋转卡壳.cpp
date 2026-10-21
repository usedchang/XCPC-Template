#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128_t;

struct Point {
    i64 x, y;

    bool operator<(const Point &o) const {
        return tie(x, y) < tie(o.x, o.y);
    }

    bool operator==(const Point &o) const {
        return x == o.x && y == o.y;
    }
};

i128 cross(const Point &o, const Point &a, const Point &b) {
    i128 ax = (i128)a.x - o.x;
    i128 ay = (i128)a.y - o.y;
    i128 bx = (i128)b.x - o.x;
    i128 by = (i128)b.y - o.y;
    return ax * by - ay * bx;
}

i128 dis2(const Point &a, const Point &b) {
    i128 dx = (i128)a.x - b.x;
    i128 dy = (i128)a.y - b.y;
    return dx * dx + dy * dy;
}

// 逆时针凸包，去掉边上的中间共线点
vector<Point> hull(vector<Point> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    if (p.size() <= 1) {
        return p;
    }

    vector<Point> h(2 * p.size());
    int sz = 0;
    for (const Point &x : p) {
        while (sz >= 2 && cross(h[sz - 2], h[sz - 1], x) <= 0) {
            --sz;
        }
        h[sz++] = x;
    }
    int lo = sz;
    for (int i = (int)p.size() - 2; i >= 0; --i) {
        while (sz > lo && cross(h[sz - 2], h[sz - 1], p[i]) <= 0) {
            --sz;
        }
        h[sz++] = p[i];
    }
    h.resize(sz - 1);
    return h;
}

struct Dia {
    Point a{}, b{};
    i128 d2 = 0;
};

Dia diameter(vector<Point> p) {
    vector<Point> h = hull(move(p));
    int n = h.size();
    if (n <= 1) {
        return {h.empty() ? Point{} : h[0], h.empty() ? Point{} : h[0], 0};
    }

    Dia ans{h[0], h[1], dis2(h[0], h[1])};
    auto upd = [&](int i, int j) {
        i128 d = dis2(h[i], h[j]);
        if (d > ans.d2) {
            ans = {h[i], h[j], d};
        }
    };
    if (n == 2) {
        return ans;
    }

    int j = 1;
    for (int i = 0; i < n; ++i) {
        int ni = (i + 1) % n;
        auto area = [&](int k) {
            return cross(h[i], h[ni], h[k]);
        };
        while (area((j + 1) % n) > area(j)) {
            j = (j + 1) % n;
        }
        upd(i, j);
        upd(ni, j);
        if (area((j + 1) % n) == area(j)) {
            upd(i, (j + 1) % n);
            upd(ni, (j + 1) % n);
        }
    }
    return ans;
}
