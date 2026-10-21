#include <bits/stdc++.h>
using namespace std;

// Kahn 拓扑排序：返回 {是否 DAG, 一个拓扑序}
pair<bool, vector<int>> topo(const vector<vector<int>> &g) {
    int n = g.size();
    vector<int> deg(n);
    for (int u = 0; u < n; ++u) {
        for (int v : g[u]) {
            ++deg[v];
        }
    }

    queue<int> q;
    for (int u = 0; u < n; ++u) {
        if (deg[u] == 0) {
            q.push(u);
        }
    }

    vector<int> ord;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ord.push_back(u);
        for (int v : g[u]) {
            if (--deg[v] == 0) {
                q.push(v);
            }
        }
    }
    return {(int)ord.size() == n, move(ord)};
}

// 边权只有 0/1 的单源最短路
vector<int> bfs01(const vector<vector<pair<int, int>>> &g, int s) {
    constexpr int INF = numeric_limits<int>::max() / 2;
    int n = g.size();
    vector<int> dis(n, INF);
    deque<int> q;
    dis[s] = 0;
    q.push_front(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        for (auto [v, w] : g[u]) {
            assert(w == 0 || w == 1);
            if (dis[v] <= dis[u] + w) {
                continue;
            }
            dis[v] = dis[u] + w;
            if (w == 0) {
                q.push_front(v);
            } else {
                q.push_back(v);
            }
        }
    }
    return dis;
}
