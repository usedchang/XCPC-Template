#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const ll INF=1e18;
const int N=1e7;
void solve(){
    int n;cin>>n;
    vector<ll>a(n+1);
    vector<vector<int>>G(n+1);
    vector<ll>f(n+1);
    ll sum=0;
    for(int i=1;i<=n;i++) cin>>a[i],sum+=a[i];
    for(int i=1;i<n;i++){
        int x,y;cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);    
    }
    vector<ll>dp(n+1);
    vector<ll>siz(n+1);
    auto dfs=[&](auto &&dfs,int u,int fa) ->void {
        dp[u]=INF;
        f[u]=a[u];
        siz[u]=1;
        for(int v:G[u]){
            if(v==fa) continue;
            dfs(dfs,v,u);
            f[u]+=f[v];
            siz[u]+=siz[v];
            dp[u]=min(dp[u],dp[v]);
        }
        dp[u]=min(dp[u],f[u]/siz[u]);
    };
    dfs(dfs,1,0);
    for(int i=1;i<=n;i++) cout<<dp[i]<<' ';
    cout<<endl;
}
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    int size(256<<20);
    __asm__ ( "movq %0, %%rsp\n"::"r"((char*)malloc(size)+size)); 
    int T=1;cin>>T;
    while(T--) solve();
    exit(0);
    return 0;
}
