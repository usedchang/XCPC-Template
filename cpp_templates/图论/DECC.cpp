const int N=2e5+5;
vector<pair<int,int>>G[N];
struct DECC{
    vector< vector<pair<int,int> >>G;
    vector< vector<int> >B;// 存储所有边双连通分量
    vector<int>dfn,low;//时间戳
    stack<int>st;
    vector<char>vis;
    vector<int>mp;// 每个点属于哪个分量
    int cnt,n,id;
    DECC(int n):n(n),cnt(0),id(0){
        G.resize(n+1);
        low.resize(n+1);
        dfn.resize(n+1);
        mp.resize(n+1);
    }
    void add(int x,int y){
        ++id;
        G[x].push_back({y,id});
        G[y].push_back({x,id});
    }
    void tarjan(int u,int fa){
        dfn[u]=low[u]=(++cnt);
        st.push(u);
        for(auto &[v,id]:G[u]){
            if(!dfn[v]){
                tarjan(v,id);
                low[u]=min(low[u],low[v]);
            }
            else if(id!=fa&&dfn[v]<dfn[u]){
                low[u]=min(low[u],dfn[v]);
            }
        }
        if(dfn[u]==low[u]){
            vector<int>tmp;
            int y;
            do{
                y=st.top();
                mp[y]=B.size();
                st.pop();
                tmp.push_back(y);
            }while(y!=u);
            if(!tmp.empty()) B.push_back(tmp);
        }
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    DECC bcc(n+1);
    for(int i=1;i<=m;i++){
        int x,y;cin>>x>>y;
        bcc.add(x,y);
    }
    for(int i=1;i<=n;i++){
        if(!bcc.dfn[i]) bcc.tarjan(i,0);
    }
    cout<<bcc.B.size()<<endl;
    for(auto &p:bcc.B){
        cout<<p.size()<<' ';
        for(int &x:p) cout<<x<<' ';
        cout<<endl;
    }
}
