#include <bits/stdc++.h>
using namespace std;
int main(){
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> edges(m);
    vector<int>deg(n + 1, 0);
    for(int i = 0; i < m; i++){
        cin >> edges[i].first >> edges[i].second;
        deg[edges[i].first]++;
        deg[edges[i].second]++;
    }
    // 定向：度数小 -> 度数大，度数相同则编号小 -> 编号大
    vector<vector<int>> adj(n + 1);
    for(int i = 0; i < m; i++){
        int u = edges[i].first, v = edges[i].second;
        if(deg[u] < deg[v] || (deg[u] == deg[v] && u < v)){
            adj[u].push_back(v);
        } else {
            adj[v].push_back(u);
        }
    }
    // 枚举三元环
    vector<int> mark(n + 1, 0); // mark[w] = u 表示 u->w 这条边存在
    long long ans = 0;
    for(int u = 1; u <= n; u++){
        // 标记 u 的所有出边邻居
        for(int v : adj[u]){
            mark[v] = u;
        }
        // 枚举 u -> v -> w，检查 u -> w
        for(int v : adj[u]){
            for(int w : adj[v]){
                if(mark[w] == u){
                    ans++;
                }
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
