#include <bits/stdc++.h>
using namespace std;

// 0-indexed point updates and half-open range sums [l, r).
template <class T>
struct Fenwick {
    int n;
    vector<T> bit;

    explicit Fenwick(int n = 0) : n(n), bit(n + 1, T{}) {}

    void add(int i, T delta) {
        for (++i; i <= n; i += i & -i) {
            bit[i] += delta;
        }
    }

    // Sum of a[0..r).
    T prefix_sum(int r) const {
        T result{};
        for (; r > 0; r -= r & -r) {
            result += bit[r];
        }
        return result;
    }

    T range_sum(int l, int r) const {
        return prefix_sum(r) - prefix_sum(l);
    }
};

// Range add and range sum on a 0-indexed array, using two Fenwick trees.
template <class T>
struct FenwickRangeSum {
    int n;
    Fenwick<T> slope, intercept;

    explicit FenwickRangeSum(int n = 0) : n(n), slope(n + 1), intercept(n + 1) {}

    void range_add(int l, int r, T delta) {
        slope.add(l, delta);
        slope.add(r, -delta);
        intercept.add(l, delta * l);
        intercept.add(r, -delta * r);
    }

    T prefix_sum(int r) const {
        return slope.prefix_sum(r) * r - intercept.prefix_sum(r);
    }

    T range_sum(int l, int r) const {
        return prefix_sum(r) - prefix_sum(l);
    }
};

// 0-indexed point updates and half-open rectangle sums [x1, x2) x [y1, y2).
template <class T>
struct Fenwick2D {
    int n, m;
    vector<vector<T>> bit;

    Fenwick2D(int n, int m) : n(n), m(m), bit(n + 1, vector<T>(m + 1, T{})) {}

    void add(int x, int y, T delta) {
        for (int i = x + 1; i <= n; i += i & -i) {
            for (int j = y + 1; j <= m; j += j & -j) {
                bit[i][j] += delta;
            }
        }
    }

    T prefix_sum(int x, int y) const {
        T result{};
        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                result += bit[i][j];
            }
        }
        return result;
    }

    T rectangle_sum(int x1, int y1, int x2, int y2) const {
        return prefix_sum(x2, y2) - prefix_sum(x1, y2)
             - prefix_sum(x2, y1) + prefix_sum(x1, y1);
    }
};
