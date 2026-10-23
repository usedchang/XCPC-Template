struct DSU{
    vector<int>f,siz;
    vector<ll>dis;
    DSU(int n){
        f.resize(n+1);
        dis.resize(n+1);
        siz.assign(n+1,1);
        iota(f.begin(),f.end(),0);
    }
    int find(int x){
        if(f[x]==x) return x;
        int p=f[x];
        f[x]=find(p);
        dis[x]+=dis[p];
        return f[x];
    }
    bool merge(int x,int y,ll w){
        int fx=find(x),fy=find(y);
        if(fx==fy){
            return dis[x]-dis[y]==w;
        }
        f[fx]=fy;
        dis[fx]=(w+dis[y]-dis[x]);
        siz[fy]+=siz[fx];
        return true;
    }
    bool same(int x,int y){
        int fx=find(x),fy=find(y);
        return find(x)==find(y);
    }
    ll Dis(int x,int y){
        find(x);
        find(y);
        return dis[x]-dis[y];
    }
};