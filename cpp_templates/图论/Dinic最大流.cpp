#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct Dinic {
    struct Edge {
        int to, rev;
        i64 cap;
    };

    int n;
    vector<vector<Edge>> graph;
    vector<int> level, current;

    explicit Dinic(int n) : n(n), graph(n), level(n), current(n) {}

    void add_edge(int u, int v, i64 cap) {
        int forward = graph[u].size();
        int reverse = graph[v].size() + (u == v);
        graph[u].push_back({v, reverse, cap});
        graph[v].push_back({u, forward, 0});
    }

    bool bfs(int source, int sink) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[source] = 0;
        q.push(source);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto &e : graph[u]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[sink] != -1;
    }

    i64 dfs(int u, int sink, i64 flow) {
        if (u == sink || flow == 0) {
            return flow;
        }
        for (int &i = current[u]; i < (int)graph[u].size(); ++i) {
            Edge &e = graph[u][i];
            if (e.cap == 0 || level[e.to] != level[u] + 1) {
                continue;
            }
            i64 pushed = dfs(e.to, sink, min(flow, e.cap));
            if (pushed == 0) {
                continue;
            }
            e.cap -= pushed;
            graph[e.to][e.rev].cap += pushed;
            return pushed;
        }
        return 0;
    }

    i64 max_flow(int source, int sink,
                 i64 limit = numeric_limits<i64>::max()) {
        if (source == sink || limit <= 0) {
            return 0;
        }
        i64 flow = 0;
        while (flow < limit && bfs(source, sink)) {
            fill(current.begin(), current.end(), 0);
            while (flow < limit) {
                i64 pushed = dfs(source, sink, limit - flow);
                if (pushed == 0) {
                    break;
                }
                flow += pushed;
            }
        }
        return flow;
    }

    vector<bool> min_cut_side(int source) const {
        vector<bool> seen(n);
        queue<int> q;
        seen[source] = true;
        q.push(source);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto &e : graph[u]) {
                if (e.cap > 0 && !seen[e.to]) {
                    seen[e.to] = true;
                    q.push(e.to);
                }
            }
        }
        return seen;
    }
};
