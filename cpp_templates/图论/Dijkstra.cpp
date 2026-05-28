#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int N=2e5+5;
struct node{
    int u;ll w;
    friend bool operator<(node a,node b){
        return a.w>b.w;
    }
};
vector<node>G[N];
bool vis[N];
ll dis[N];
int n,m,s;
void Dijkstra(int s){
    fill(dis+1,dis+1+n,INT_MAX);
    priority_queue<node>Q;
    dis[s]=0;
    Q.push({s,0});
    while(!Q.empty()){
        int u=Q.top().u;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(auto &[v,w]:G[u]){
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                Q.push({v,dis[v]});
            }
        }
    }
}
void solve(){
    cin>>n>>m>>s;
    for(int i=1;i<=m;i++){
        int x,y;ll w;
        cin>>x>>y>>w;
        G[x].push_back({y,w});
    }
    Dijkstra(s);
    for(int i=1;i<=n;i++) cout<<dis[i]<<' ';
    cout<<endl;
}
int main(){
    solve();
    return 0;
}
