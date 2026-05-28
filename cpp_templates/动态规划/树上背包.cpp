const ll mod=998244353;
void solve(){
    int n;cin>>n;
    vector<int>a(n+1);
    vector< vector<int> >G(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<n;i++){
        int x,y;cin>>x>>y;
        G[x].emplace_back(y);
        G[y].emplace_back(x);
    }
    vector<vector<ll>>dp(n+1,vector<ll>(n+1));//使用子树和当前点产生j个诚实者的合法情况
    vector<vector<ll>>f(n+1,vector<ll>(n+1));//仅使用子树产生j个诚实者的合法情况
    vector<int>siz(n+1);
    auto dfs=[&](auto &&dfs,int u,int fa) ->void {
        f[u][0]=siz[u]=1;
        for(int v:G[u]){
            if(v==fa) continue;
            dfs(dfs,v,u);
            vector<ll>nxt(siz[u]+siz[v]+1);
            for(int j=siz[u];j>=0;j--){
                for(int k=siz[v];k>=0;k--){
                    (nxt[j+k]+=(f[u][j]*dp[v][k]%mod))%=mod;
                }
            }
            f[u]=move(nxt);
            siz[u]+=siz[v];
        }
        for(int j=siz[u];j>=0;j--) dp[u][j]=f[u][j];
        dp[u][a[u]]=0;
        if(a[u]>=1&&a[u]<=siz[u]) {
            dp[u][a[u]]=f[u][a[u]-1];
        }
    };
    dfs(dfs,1,0);
    ll ans=0;
    for(int i=0;i<=siz[1];i++) (ans+=dp[1][i])%=mod;
    cout<<ans<<endl;
}
