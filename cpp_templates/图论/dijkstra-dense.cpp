#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int N=1010;     // 注意:n<=1000 推荐使用稠密版，否则改用稀疏图堆优化！
const ll INF = 1e18;

ll g[N][N];
ll dis[N];
bool vis[N];
int n,m,s;

void Dijkstra(int s){
    for(int i=1;i<=n;i++){
        dis[i]=INF;
        vis[i]=false;
    }
    dis[s]=0;
    for(int i=1;i<=n;i++){
        int u=-1; ll minv=INF;
        for(int j=1;j<=n;j++){
            if(!vis[j] && dis[j]<minv){
                minv=dis[j];
                u=j;
            }
        }
        if(u==-1) break;
        vis[u]=true;
        for(int j=1;j<=n;j++){
            if(g[u][j]<INF && dis[j]>dis[u]+g[u][j]){
                dis[j]=dis[u]+g[u][j];
            }
        }
    }
}

void solve(){
    cin>>n>>m>>s;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            g[i][j]=(i==j?0:INF);
    for(int i=1;i<=m;i++){
        int x,y;ll w;
        cin>>x>>y>>w;
        g[x][y]=min(g[x][y],w);   // 支持重边取最优
    }
    Dijkstra(s);
    for(int i=1;i<=n;i++) cout<<dis[i]<<' ';
    cout<<endl;
}
int main(){
    solve();
    return 0;
}
