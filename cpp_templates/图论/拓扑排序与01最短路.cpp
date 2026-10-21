#include <bits/stdc++.h>
using namespace std;

// Kahn's algorithm. Returns {is_dag, one_topological_order}.
pair<bool, vector<int>> topological_sort(const vector<vector<int>> &graph) {
    int n = graph.size();
    vector<int> indegree(n);
    for (int u = 0; u < n; ++u) {
        for (int v : graph[u]) {
            ++indegree[v];
        }
    }

    queue<int> q;
    for (int u = 0; u < n; ++u) {
        if (indegree[u] == 0) {
            q.push(u);
        }
    }

    vector<int> order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : graph[u]) {
            if (--indegree[v] == 0) {
                q.push(v);
            }
        }
    }
    return {(int)order.size() == n, move(order)};
}

// Edges must have weight 0 or 1. The graph is an adjacency list of (to, weight).
vector<int> zero_one_bfs(const vector<vector<pair<int, int>>> &graph, int source) {
    constexpr int inf = numeric_limits<int>::max() / 2;
    int n = graph.size();
    vector<int> dist(n, inf);
    deque<int> q;
    dist[source] = 0;
    q.push_front(source);

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        for (auto [v, weight] : graph[u]) {
            assert(weight == 0 || weight == 1);
            if (dist[v] <= dist[u] + weight) {
                continue;
            }
            dist[v] = dist[u] + weight;
            if (weight == 0) {
                q.push_front(v);
            } else {
                q.push_back(v);
            }
        }
    }
    return dist;
}
