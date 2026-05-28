void solve(){
    int m,n=500;cin>>m;
    vector<vector<pair<int,int>>>G(n+1);
    vector<int>in(n+1);
    for(int i=1;i<=m;i++){
        int x,y;cin>>x>>y;
        G[x].emplace_back(y,i);
        G[y].emplace_back(x,i);
        ++in[x],++in[y];
    }
    auto find=[&]() ->int {
        int cnt=0;
        for(int i=1;i<=n;i++){
            if(in[i]&1) ++cnt;
        }
        if(cnt!=2&&cnt!=0) return -1;
        else if(cnt==0) {
            for(int i=1;i<=n;i++){
                if(in[i]) return i;
            }
        }
        else if(cnt==2){
            for(int i=1;i<=n;i++){
                if(in[i]&1) return i;
            }
        }
        return -1;
    };
    int s=find();
    vector<int>nxt(n+1),vis(m+1),res;
    for(int i=1;i<=n;i++) sort(G[i].begin(),G[i].end());
    auto dfs=[&](auto &&dfs,int u) ->void {
        while(nxt[u]<G[u].size()){
            int v=G[u][nxt[u]].first;
            int id=G[u][nxt[u]].second;
            ++nxt[u];
            if(vis[id]) continue;
            vis[id]=1;
            dfs(dfs,v);
        }
        res.push_back(u);
    };
    dfs(dfs,s);
    reverse(res.begin(),res.end());
    for(int x:res) cout<<x<<endl;
}
