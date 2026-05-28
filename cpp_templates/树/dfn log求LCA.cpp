//P3379 最近公共祖先
const int N=5e5+5;
vector<int>G[N];
int f[N],d[N],dfn[N],top[N],cnt,siz[N],son[N];
void dfs1(int u,int fa){
    d[u]=d[fa]+1;
    f[u]=fa;
    siz[u]=1;
    for(int v:G[u]){
        if(fa==v) continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
}
void dfs2(int u,int node){
    dfn[u]=(++cnt);//维护dfn序
    top[u]=node;
    if(son[u]) dfs2(son[u],node);
    for(int v:G[u]){
        if(v==f[u]||v==son[u]) continue;
        dfs2(v,v);
    }
}
int LCA(int l,int r){
    while(top[l]!=top[r]){
        if(d[top[l]]<d[top[r]]) swap(l,r);
        l=f[top[l]];
    }
    if(d[l]<d[r]) return l;
    return r;
}//树上LCA跳
void solve(){
    int n,m,s;
    cin>>n>>m>>s;
    for(int i=1;i<n;i++){
        int x,y;cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs1(s,0);
    dfs2(s,s);
    for(int i=1;i<=m;i++){
        int x,y;cin>>x>>y;
        cout<<LCA(x,y)<<endl;
    }
}
