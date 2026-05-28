//P3384 [模板]重链剖分 / 树链剖分
const int N=1e5+5;
ll mod;
int n,m,r;
vector<int>G[N];
int d[N],f[N],siz[N],dfn[N],rev[N],cnt,top[N],son[N];
ll val[N],new_val[N];
struct Seg{
    struct S{
        int l,r;
        ll sum,laz;
    };
    int n;
    vector<S>tre;
    Seg(){};
    Seg(int n):n(n){
        tre.resize(n<<2);
        build(0,n,1);
    };
    #define lc (p<<1)
    #define rc (p<<1|1)
    void pushup(int p){
        tre[p].sum=(tre[lc].sum+tre[rc].sum)%mod;
    }
    void pushdown(int p){
        if(tre[p].laz==0) return;
        tre[lc].laz=(tre[lc].laz+tre[p].laz)%mod;
        tre[rc].laz=(tre[rc].laz+tre[p].laz)%mod;
        tre[lc].sum=(tre[lc].sum+tre[p].laz*(tre[lc].r-tre[lc].l+1)%mod)%mod;
        tre[rc].sum=(tre[rc].sum+tre[p].laz*(tre[rc].r-tre[rc].l+1)%mod)%mod;
        tre[p].laz=0;
    }
    void build(int l,int r,int p){
        tre[p]={l,r,0LL,0LL};
        if(l==r) {
            tre[p].sum=new_val[l]%mod;
            return;
        }
        int mid=l+r>>1;
        build(l,mid,lc);
        build(mid+1,r,rc);
        pushup(p);
    }
    void Add(int l,int r,ll k,int p){
        if(l<=tre[p].l&&r>=tre[p].r){
            tre[p].sum=(tre[p].sum+k*(tre[p].r-tre[p].l+1)%mod)%mod;
            tre[p].laz=(tre[p].laz+k)%mod;
            return;
        }
        int mid=tre[p].l+tre[p].r>>1;
        pushdown(p);
        if(l<=mid) Add(l,r,k,lc);
        if(r>mid) Add(l,r,k,rc); 
        pushup(p);
    }
    ll qry(int l,int r,int p){
        if(l<=tre[p].l&&r>=tre[p].r) return tre[p].sum;
        ll ans=0;
        int mid=tre[p].l+tre[p].r>>1;
        pushdown(p);
        if(l<=mid) ans=(ans+qry(l,r,lc))%mod;
        if(r>mid) ans=(ans+qry(l,r,rc))%mod;
        return ans;
    }
}S;
void dfs1(int u,int fa){
    f[u]=fa;
    d[u]=d[fa]+1;
    siz[u]=1;
    for(int v:G[u]){
        if(v==fa) continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
}//第一遍初始化节点信息
void dfs2(int u,int node){
    top[u]=node;
    dfn[u]=(++cnt);
    rev[cnt]=u;
    new_val[cnt]=val[u];
    if(son[u]) dfs2(son[u],node);
    for(int v:G[u]){
        if(v!=son[u]&&v!=f[u]) dfs2(v,v);
    }
}
void Upd_path(int l,int r,ll k){
    k%=mod;
    while(top[l]!=top[r]){
        if(d[top[l]]<d[top[r]]) swap(l,r);
        S.Add(dfn[top[l]],dfn[l],k,1);
        l=f[top[l]];
    }
    if(d[l]>d[r]) swap(l,r);
    S.Add(dfn[l],dfn[r],k,1);
}
ll qry_path(int l,int r){
    int res=0;
    while(top[l]!=top[r]){
        if(d[top[l]]<d[top[r]]) swap(l,r);
        res=(res+S.qry(dfn[top[l]],dfn[l],1))%mod;
        l=f[top[l]];
    }//不在同一个重链中LCA跳
    if(d[l]>d[r]) swap(l,r);
    res=(res+S.qry(dfn[l],dfn[r],1))%mod;
    return res;
}
void Upd(int u,ll k){
    k%=mod;
    S.Add(dfn[u],dfn[u]+siz[u]-1,k,1);
}
ll qry(int u){
    return S.qry(dfn[u],dfn[u]+siz[u]-1,1);
}
void solve(){
    cin>>n>>m>>r>>mod;
    for(int i=1;i<=n;i++) cin>>val[i];
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs1(r,0);
    dfs2(r,r);
    S=Seg(n+1);
    for(int i=1;i<=m;i++){
        int op,l,r;ll k;cin>>op;
        if(op==1){
            cin>>l>>r>>k;
            Upd_path(l,r,k);
        }
        else if(op==2){
            cin>>l>>r;
            cout<<qry_path(l,r)<<endl;
        }
        else if(op==3){
            cin>>l>>k;
            Upd(l,k);
        }
        else if(op==4){
            cin>>l;
            cout<<qry(l)<<endl;
        }
    }
}
