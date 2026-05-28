//U41492 树上数颜色
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int N=1e5+5;
vector<int>G[N];
int cnt[N],siz[N],son[N],f[N],res,a[N],ans[N];
void dfs1(int u,int fa){
    f[u]=fa;
    siz[u]=1;
    for(int v:G[u]){
        if(v==fa) continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
}
void Upd(int u,bool F,int skiped){
    if(F){
        cnt[a[u]]++;
        if(cnt[a[u]]==1) res++;
    }
    else{
        cnt[a[u]]--;
        if(cnt[a[u]]==0) res--;
    }
    for(int v:G[u]){
        if(v==f[u]||v==skiped) continue;
        Upd(v,F,0);
    }
}//更新轻儿子贡献
void dfs2(int u,bool F){
    for(int v:G[u]){
        if(v==son[u]||v==f[u]) continue;
        dfs2(v,0);
    }
    if(son[u]) {
        dfs2(son[u],1);
    }
    Upd(u,1,son[u]);
    ans[u]=res;
    if(!F) Upd(u,0,0);
}
void solve(){
    int n;cin>>n;
    for(int i=1;i<n;i++){
        int x,y;cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i=1;i<=n;i++) cin>>a[i];
    dfs1(1,0);
    dfs2(1,1);
    int q;cin>>q;
    while(q--){
        int x;cin>>x;
        cout<<ans[x]<<endl;
    }
}
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    solve();
    return 0;
}
