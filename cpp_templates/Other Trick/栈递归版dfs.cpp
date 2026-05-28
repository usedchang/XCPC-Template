struct Statu{
    int u,fa,op;//当前节点,父节点,操作方式
};
int x,y;
void solve() {
    int n; cin>>n;
    vector<ll>a(n+1),f(n+1),dp(n+1);
    vector<Statu>st(n+1);
    vector<int>siz(n+1);
    vector<vector<int>>G(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<n;i++){
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    st.push_back({1,0,0});
    while(!st.empty()){
        Statu &cur=st.back();
        int u=cur.u,fa=cur.fa;
        if(!cur.op){
            dp[u]=INF;
            f[u]+=a[u];
            siz[u]++;
            cur.op=1;
            for(int v:G[u]){
                if(v==fa) continue;
                st.push_back({v,u,0});
            }
        }
        else{
            for(int v:G[u]){
                if(v==fa) continue;
                dp[u]=min(dp[u],dp[v]);
                siz[u]+=siz[v];
                f[u]+=f[v];
            }
            dp[u]=min(dp[u],f[u]/siz[u]);
            st.pop_back();
        }
    }
    for(int i=1;i<=n;i++) cout<<dp[i]<<' ';
    cout<<endl;
}
