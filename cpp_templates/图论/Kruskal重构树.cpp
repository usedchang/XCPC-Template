struct DSU{
    vector<ll>f;
    DSU(){}
    DSU(int n){
        f.resize(n+1);
        iota(f.begin(),f.end(),0);
    };
    int find(int x){
        return x==f[x]?x:f[x]=find(f[x]);
    }
    bool merge(int x,int y){
        int fx=find(x),fy=find(y);
        if(fx==fy) return false;
        f[fx]=fy;
        return true;
    }
};
struct Edge{
    int x,y;ll w;
    Edge(){};
    Edge(int x,int y,ll w):x(x),y(y),w(w){};
    friend bool operator<(Edge A,Edge B){
        return A.w<B.w;
    }
};
inline void solve(){
    int n,m;
    cin>>n>>m;
    DSU dsu(n<<1);
    vector<vector<int>>G(n<<1|1);
    vector<Edge>a;
    vector<ll>val(n<<1|1);//存新节点(边)权值
    for(int i=1;i<=m;i++){
        int x,y;ll w;
        cin>>x>>y>>w;
        a.emplace_back(x,y,w);
    }
    sort(a.begin(),a.end());
    int tot=n;
    for(auto &[x,y,w]:a){
        int fx=dsu.find(x),fy=dsu.find(y);
        if(fx!=fy){
            ++tot;
            dsu.merge(fx,tot);
            dsu.merge(fy,tot);
            G[tot].push_back(fx);
            G[tot].push_back(fy);
            val[tot]=w;
        }
    }
    vector<int>dfn(n<<1|1);
    vector<ll>d(n<<1|1);
    vector<vector<int>>st(n<<1|1,vector<int>(20));
    int top=0;
    auto dfs=[&](auto &&dfs,int u,int fa) ->void {
        d[u]=d[fa]+1;
        dfn[u]=++top;
        st[dfn[u]][0]=fa;
        for(int v:G[u]) dfs(dfs,v,u);
    };
    for(int i=1;i<=(n<<1);i++){
        if(dsu.find(i)==i){
            dfs(dfs,i,0);
        }
    }
    for(int i=1;i<20;i++){
        for(int j=1;j+(1<<i)-1<=(n<<1);j++){
            int L=st[j][i-1];
            int R=st[j+(1<<i-1)][i-1];
            st[j][i]=(d[L]<d[R])?L:R;
        }
    }
    auto lca=[&](int l,int r) ->int {
        if(l==r) return l;
        l=dfn[l],r=dfn[r];
        if(l>r) swap(l,r);
        ++l;
        int len=__lg(r-l+1);
        int L=st[l][len];
        int R=st[r-(1<<len)+1][len];
        return (d[L]<d[R])?L:R;
    };
    int q;cin>>q;
    for(int i=1;i<=q;i++){
        int x,y;cin>>x>>y;
        if(dsu.find(x)!=dsu.find(y)) cout<<"impossible"<<endl;
        else cout<<val[lca(x,y)]<<endl;
    }
}
