#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    int n;cin>>n;
    vector<vector<int>>G(n+1);
    vector<int>down(n+1),up(n+1);
    for(int i=1;i<n;i++){
        int x,y;cin>>x>>y;
        G[x].emplace_back(y);
        G[y].emplace_back(x);
    }
    auto dfs1=[&](auto &&dfs1,int u,int fa) ->void {
        for(int v:G[u]){
            if(v==fa) continue;
            dfs1(dfs1,v,u);
            down[u]=max(down[u],down[v]+1);
        }
    };
    dfs1(dfs1,1,0);
    auto dfs2=[&](auto &&dfs2,int u,int fa) ->void {
        int m1=0,m2=0;//最长路径，次长路径
        for(int v:G[u]){
            if(v==fa) continue;
            if(down[m1]<down[v]) m2=m1,m1=v;
            else if(down[m2]<down[v]) m2=v;
        }
        for(int v:G[u]){
            if(v==fa) continue;
            up[v]=up[u]+1;
            if(m1!=0&&down[m1]!=down[v]) up[v]=max(up[v],down[m1]+2);
            else if(down[m2]!=0) up[v]=max(up[v],down[m2]+2);
            dfs2(dfs2,v,u);
        }
    };
    dfs2(dfs2,1,0);
    int ans=0;
    for(int i=1;i<=n;i++) ans=max(ans,down[i]+up[i]);
    cout<<ans<<endl;
    return 0;
}
