//P3379 最近公共祖先
void solve(){
    int n,q,s;
    cin>>n>>q>>s;
    vector<vector<int>>G(n+1);
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    vector<int>d(n+1);
    vector<int>f(n+1);
    vector<int>dfn(n+1);
    int cnt=0;
    auto dfs=[&](auto &&dfs,int u,int fa) ->void {
        f[u]=fa;
        dfn[u]=(++cnt);
        d[u]=d[fa]+1;
        for(int v:G[u]){
            if(v==fa) continue;
            dfs(dfs,v,u);
        }
    };
    dfs(dfs,s,0);
    vector<vector<int>>st(n+1,vector<int>(21));
    for(int i=1;i<=n;i++) st[dfn[i]][0]=f[i];
    for(int j=1;j<=20;j++){
        for(int i=1;i+(1<<j)-1<=n;i++){
            int l=st[i][j-1];
            int r=st[i+(1<<j-1)][j-1];
            if(d[l]<d[r]) st[i][j]=l;
            else st[i][j]=r;
        }
    }
    auto lca=[&](int l,int r) ->int {
        if(l==r) return l;
        l=dfn[l],r=dfn[r];
        if(l>r) swap(l,r);
        l++;
        int len=__lg(r-l+1);
        int L=st[l][len];
        int R=st[r-(1<<len)+1][len];
        return (d[L]<d[R])?L:R;
    };
    while(q--){
        int x,y;
        cin>>x>>y;
        cout<<lca(x,y)<<endl;
    }
}
