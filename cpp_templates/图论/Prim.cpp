#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int inf=0x3f3f3f3f;
const int N=5e5+10;
int dis[N];
int n,m,cntn;
bool vis[N];
ll ans;
struct edge{
    int u,w;
};
vector<edge>G[N];
void add(int x,int y,int w){
    G[x].push_back({y,w});
    G[y].push_back({x,w});
}
struct node{
    int u,w;
    friend bool operator <(node a,node b){
        return a.w>b.w;
    }
}a[N];
priority_queue<node>Q;
void Prim(){
    cntn=n;
    dis[1]=0;
    Q.push({1,0});
    while(!Q.empty()){
        auto [u,w]=Q.top();
        Q.pop();
        if(vis[u]) continue;
        cntn--;
        ans+=w;
        vis[u]=1;
        for(int i=0;i<G[u].size();i++){
            auto [v,w]=G[u][i];
            if(vis[v]) continue;
            if(w<dis[v]){
                dis[v]=w;
                Q.push({v,dis[v]});
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=m;i++){
        int x,y,w;cin>>x>>y>>w;
        add(x,y,w);
        add(y,x,w);
    }
    Prim();
    if(cntn==0) cout<<ans<<endl;
    else cout<<"orz"<<endl;
    return 0;
}