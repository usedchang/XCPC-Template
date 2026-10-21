#include <bits/stdc++.h>
using namespace std;

// 0-indexed 单点加、半开区间 [l,r) 求和
template <class T>
struct BIT {
    int n;
    vector<T> tr;

    explicit BIT(int n = 0) : n(n), tr(n + 1, T{}) {}

    void add(int i, T v) {
        for (++i; i <= n; i += i & -i) {
            tr[i] += v;
        }
    }

    T sum(int r) const {
        T res{};
        for (; r > 0; r -= r & -r) {
            res += tr[r];
        }
        return res;
    }

    T query(int l, int r) const {
        return sum(r) - sum(l);
    }
};

// 0-indexed 区间加、区间和
template <class T>
struct BITR {
    int n;
    BIT<T> d, c;

    explicit BITR(int n = 0) : n(n), d(n + 1), c(n + 1) {}

    void add(int l, int r, T v) {
        d.add(l, v);
        d.add(r, -v);
        c.add(l, v * l);
        c.add(r, -v * r);
    }

    T sum(int r) const {
        return d.sum(r) * r - c.sum(r);
    }

    T query(int l, int r) const {
        return sum(r) - sum(l);
    }
};

// 0-indexed 二维单点加、半开矩形 [x1,x2) x [y1,y2) 求和
template <class T>
struct BIT2D {
    int n, m;
    vector<vector<T>> tr;

    BIT2D(int n, int m) : n(n), m(m), tr(n + 1, vector<T>(m + 1, T{})) {}

    void add(int x, int y, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            for (int j = y + 1; j <= m; j += j & -j) {
                tr[i][j] += v;
            }
        }
    }

    T sum(int x, int y) const {
        T res{};
        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                res += tr[i][j];
            }
        }
        return res;
    }

    T query(int x1, int y1, int x2, int y2) const {
        return sum(x2, y2) - sum(x1, y2)
             - sum(x2, y1) + sum(x1, y1);
    }
};
