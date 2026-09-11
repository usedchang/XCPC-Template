#include <bits/stdc++.h>
using namespace std;
struct TwoSAT {
    int n;
    vector<vector<int>> G;
    vector<int> dfn, low, scc_id;
    vector<bool> in_stk;
    stack<int> st;
    int tim, scc_cnt;
    TwoSAT(int n) : n(n), G(2 * n), dfn(2 * n), low(2 * n), scc_id(2 * n), in_stk(2 * n) {
        tim = scc_cnt = 0;
    }
    void add_edge(int u, int v) {
        G[u].push_back(v);
    }
    // i, j 从 1 开始，a, b ∈ {0, 1}
    void add_clause(int i, bool a, int j, bool b) {
        --i; --j;
        // 2*i: false , 2*i+1: true
        add_edge((i << 1) | (!a), (j << 1) | b);   // !a -> b
        add_edge((j << 1) | (!b), (i << 1) | a);   // !b -> a
    }
    void tarjan(int u) {
        dfn[u] = low[u] = ++tim;
        st.push(u);
        in_stk[u] = true;
        for (int v : G[u]) {
            if (!dfn[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (in_stk[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (low[u] == dfn[u]) {
            ++scc_cnt;
            int v;
            do {
                v = st.top(); st.pop();
                in_stk[v] = false;
                scc_id[v] = scc_cnt;
            } while (v != u);
        }
    }

    bool solve(vector<int> &ans) {
        ans.assign(n + 1, 0);
        for (int i = 0; i < 2 * n; ++i)
            if (!dfn[i]) tarjan(i);

        for (int i = 0; i < n; ++i) {
            if (scc_id[2 * i] == scc_id[2 * i + 1])
                return false;   // 无解
            ans[i + 1] = (scc_id[2 * i] < scc_id[2 * i + 1]) ? 0 : 1;
        }
        return true;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    TwoSAT solver(n);
    for (int k = 0; k < m; ++k) {
        int i, a, j, b;
        cin >> i >> a >> j >> b;
        solver.add_clause(i, a, j, b);
    }
    vector<int> ans;
    if (solver.solve(ans)) {
        cout << "POSSIBLE\n";
        for (int i = 1; i <= n; ++i)
            cout << ans[i] << " \n"[i == n];
    } else {
        cout << "IMPOSSIBLE\n";
    }
    return 0;
}