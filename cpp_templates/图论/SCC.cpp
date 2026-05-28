const int N=1e4+5;
vector<int>G[N];
int w[N],new_w[N];
vector<int>new_G[N];
struct SCC{
    vector<vector<int> >ans;
    vector<int>dfn,low,mp;
    vector<char>vis;
    stack<int>st;
    int cnt,n;
    SCC(int n):n(n),cnt(0){
        vis.resize(n+1);
        dfn.resize(n+1);
        low.resize(n+1);
        mp.resize(n+1);
    }
    void tarjan(int u){
        low[u]=dfn[u]=(++cnt);
        st.push(u);
        vis[u]=1;
        for(int v:G[u]){
            if(!dfn[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
            }
            else if(vis[v]){
                low[u]=min(low[u],dfn[v]);
            }
        }
        if(dfn[u]==low[u]){
            int y;
            vector<int>tmp;
            do{
                y=st.top();
                st.pop();
                vis[y]=0;
                tmp.push_back(y);
                mp[y]=ans.size();
            }while(u!=y);
            if(!tmp.empty()) ans.push_back(tmp);
        }
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>w[i];
    for(int i=1;i<=m;i++){
        int x,y;cin>>x>>y;
        G[x].push_back(y);
    }
    SCC scc(n+1);
    for(int i=1;i<=n;i++){
        if(!scc.dfn[i]) scc.tarjan(i);
    }
    for(int i=0;i<scc.ans.size();i++){
        for(int v:scc.ans[i]){
            new_w[i]+=w[v];
        }
    }
    vector<int>in(scc.ans.size()),dp(scc.ans.size());
    for(int i=1;i<=n;i++){
        for(int v:G[i]){
            if(scc.mp[v]!=scc.mp[i]) {
                new_G[scc.mp[i]].push_back(scc.mp[v]);
                ++in[scc.mp[v]];
            }
        }
    }
    queue<int>Q;
    for(int i=0;i<scc.ans.size();i++){
        if(!in[i]) {
            Q.push(i);
            dp[i]=new_w[i];
        }
    }
    while(!Q.empty()){
        int u=Q.front();
        Q.pop();
        for(int v:new_G[u]){
            if((--in[v])==0){
                dp[v]=max(dp[v],dp[u]+new_w[v]);
                Q.push(v);
            }
        }
    }
    cout<<*max_element(dp.begin(),dp.end())<<endl;
}
