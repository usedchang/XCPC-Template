//P1196银河英雄传说
struct DSU{
    DSU(){}
    vector<int>f,siz;
    vector<ll>dis;
    DSU(int n){
        dis.resize(n+1);
        f.resize(n+1);
        iota(f.begin(),f.end(),0);
        siz.assign(n+1,1);
    }
    int find(int x){
        int fx=f[x];
        if(fx==x) return x;
        int rt=find(f[x]);
        dis[x]+=dis[f[x]];
        return f[x]=rt;
    }
    bool merge(int x,int y){
        int fx=find(x),fy=find(y);
        if(fx==fy) return false; 
        f[fx]=fy;
        dis[fx]+=siz[fy];
        siz[fy]+=siz[fx];
        return true;
    }
    bool same(int x,int y){
        return find(x)==find(y);
    }
    ll Dis(int x,int y){
        return dis[x]-dis[y];
    }
};
void solve(){
    int n;cin>>n;
    DSU dsu(n+1);
    for(int i=1;i<=n;i++){
        char c;int x,y;cin>>c>>x>>y;
        if(c=='M') dsu.merge(x,y);
        else{
            if(dsu.same(x,y)) cout<<abs(dsu.Dis(x,y))-1<<endl;
            else cout<<-1<<endl;
        }
    }
}
