#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct MinCostMaxFlow {
    struct Edge {
        int to, rev;
        i64 cap, cost;
    };

    int n;
    vector<vector<Edge>> graph;

    explicit MinCostMaxFlow(int n) : n(n), graph(n) {}

    void add_edge(int u, int v, i64 cap, i64 cost) {
        int forward = graph[u].size();
        int reverse = graph[v].size() + (u == v);
        graph[u].push_back({v, reverse, cap, cost});
        graph[v].push_back({u, forward, 0, -cost});
    }

    // Finds a maximum flow and, among them, one with minimum total cost.
    // Requires that no reachable negative-cost cycle exists in the residual graph.
    pair<i64, i64> min_cost_max_flow(int source, int sink,
                                     i64 flow_limit = numeric_limits<i64>::max()) {
        if (source == sink || flow_limit <= 0) {
            return {0, 0};
        }
        constexpr i64 inf = numeric_limits<i64>::max() / 4;
        i64 flow = 0, cost = 0;
        vector<i64> dist(n);
        vector<int> parent_vertex(n), parent_edge(n);
        vector<bool> in_queue(n);

        while (flow < flow_limit) {
            fill(dist.begin(), dist.end(), inf);
            fill(in_queue.begin(), in_queue.end(), false);
            queue<int> q;
            dist[source] = 0;
            q.push(source);
            in_queue[source] = true;

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                in_queue[u] = false;
                for (int i = 0; i < (int)graph[u].size(); ++i) {
                    const Edge &e = graph[u][i];
                    if (e.cap == 0 || dist[e.to] <= dist[u] + e.cost) {
                        continue;
                    }
                    dist[e.to] = dist[u] + e.cost;
                    parent_vertex[e.to] = u;
                    parent_edge[e.to] = i;
                    if (!in_queue[e.to]) {
                        in_queue[e.to] = true;
                        q.push(e.to);
                    }
                }
            }

            if (dist[sink] == inf) {
                break;
            }
            i64 pushed = flow_limit - flow;
            for (int v = sink; v != source; v = parent_vertex[v]) {
                pushed = min(pushed, graph[parent_vertex[v]][parent_edge[v]].cap);
            }
            for (int v = sink; v != source; v = parent_vertex[v]) {
                Edge &e = graph[parent_vertex[v]][parent_edge[v]];
                e.cap -= pushed;
                graph[v][e.rev].cap += pushed;
            }
            flow += pushed;
            cost += pushed * dist[sink];
        }
        return {flow, cost};
    }
};
