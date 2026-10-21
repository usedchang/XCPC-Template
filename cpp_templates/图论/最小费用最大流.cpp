#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct MCMF {
    struct E {
        int to, rev;
        i64 cap, cost;
    };

    int n;
    vector<vector<E>> g;

    explicit MCMF(int n) : n(n), g(n) {}

    void add(int u, int v, i64 cap, i64 cost) {
        int fu = g[u].size();
        int fv = g[v].size() + (u == v);
        g[u].push_back({v, fv, cap, cost});
        g[v].push_back({u, fu, 0, -cost});
    }

    // 最大流中的最小费用；要求残量网络无源点可达负环
    pair<i64, i64> flow(int s, int t, i64 lim = numeric_limits<i64>::max()) {
        if (s == t || lim <= 0) {
            return {0, 0};
        }
        constexpr i64 INF = numeric_limits<i64>::max() / 4;
        i64 f = 0, c = 0;
        vector<i64> dis(n);
        vector<int> pv(n), pe(n);
        vector<bool> inq(n);

        while (f < lim) {
            fill(dis.begin(), dis.end(), INF);
            fill(inq.begin(), inq.end(), false);
            queue<int> q;
            dis[s] = 0;
            q.push(s);
            inq[s] = true;

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                inq[u] = false;
                for (int i = 0; i < (int)g[u].size(); ++i) {
                    const E &e = g[u][i];
                    if (e.cap == 0 || dis[e.to] <= dis[u] + e.cost) {
                        continue;
                    }
                    dis[e.to] = dis[u] + e.cost;
                    pv[e.to] = u;
                    pe[e.to] = i;
                    if (!inq[e.to]) {
                        inq[e.to] = true;
                        q.push(e.to);
                    }
                }
            }

            if (dis[t] == INF) {
                break;
            }
            i64 d = lim - f;
            for (int v = t; v != s; v = pv[v]) {
                d = min(d, g[pv[v]][pe[v]].cap);
            }
            for (int v = t; v != s; v = pv[v]) {
                E &e = g[pv[v]][pe[v]];
                e.cap -= d;
                g[v][e.rev].cap += d;
            }
            f += d;
            c += d * dis[t];
        }
        return {f, c};
    }
};
