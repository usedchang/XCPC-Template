#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct Dinic {
    struct E {
        int to, rev;
        i64 cap;
    };

    int n;
    vector<vector<E>> g;
    vector<int> lv, it;

    explicit Dinic(int n) : n(n), g(n), lv(n), it(n) {}

    void add(int u, int v, i64 c) {
        int fu = g[u].size();
        int fv = g[v].size() + (u == v);
        g[u].push_back({v, fv, c});
        g[v].push_back({u, fu, 0});
    }

    bool bfs(int s, int t) {
        fill(lv.begin(), lv.end(), -1);
        queue<int> q;
        lv[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto &e : g[u]) {
                if (e.cap > 0 && lv[e.to] == -1) {
                    lv[e.to] = lv[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return lv[t] != -1;
    }

    i64 dfs(int u, int t, i64 f) {
        if (u == t || f == 0) {
            return f;
        }
        for (int &i = it[u]; i < (int)g[u].size(); ++i) {
            E &e = g[u][i];
            if (e.cap == 0 || lv[e.to] != lv[u] + 1) {
                continue;
            }
            i64 d = dfs(e.to, t, min(f, e.cap));
            if (d == 0) {
                continue;
            }
            e.cap -= d;
            g[e.to][e.rev].cap += d;
            return d;
        }
        return 0;
    }

    i64 flow(int s, int t, i64 lim = numeric_limits<i64>::max()) {
        if (s == t || lim <= 0) {
            return 0;
        }
        i64 f = 0;
        while (f < lim && bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (f < lim) {
                i64 d = dfs(s, t, lim - f);
                if (d == 0) {
                    break;
                }
                f += d;
            }
        }
        return f;
    }

    // 残量网络中从 s 可达的一侧
    vector<bool> cut(int s) const {
        vector<bool> vis(n);
        queue<int> q;
        vis[s] = true;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto &e : g[u]) {
                if (e.cap > 0 && !vis[e.to]) {
                    vis[e.to] = true;
                    q.push(e.to);
                }
            }
        }
        return vis;
    }
};
