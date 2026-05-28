void solve(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>>G(n+1);
    for(int i=1;i<=m;i++){
        int x,y;cin>>x>>y;
        G[x].emplace_back(y);
        G[y].emplace_back(x);
    }
    int A=0,B=0;
    vector<int>col(n+1);
    auto dfs=[&](auto &dfs,int u) ->bool {
        bool f=true;
        for(int v:G[u]){
            if(!col[v]) {
                col[v]=3-col[u];
                if(col[v]==1) ++A;
                else ++B;
                f&=dfs(dfs,v);
            }
            else if(col[v]!=3-col[u]) f=false;//当前联通分量无法染色
        }
        return f;
    };
    ll ans=0;
    for(int i=1;i<=n;i++){
        if(!col[i]){
            A=B=0;
            col[i]=1;
            ++A;
            if(dfs(dfs,i)) ans+=max(A,B);
        }
    }
    cout<<ans<<endl;
}
