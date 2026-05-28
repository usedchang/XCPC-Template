struct DSU{
    vector<int>f;
    vector<int>siz;
    DSU(){};
    DSU(int n){
        f.resize(n+1);
        iota(f.begin(),f.end(),0);
        siz.assign(n+1,1);
    }
    int find(int x){
        return x==f[x]?x:f[x]=find(f[x]);
    }
    bool merge(int x,int y){
        int fx=find(x),fy=find(y);
        if(fx==fy) return false;
        f[fx]=fy;
        siz[fy]+=siz[fx];
        return true;
    }
    int nxt(int l,int r){
        ll res=0;
        l=find(l);
        int fl=l;
        while(l<=r){
            ++res;
            fl=find(l+1);
            f[l]=fl;
            l=fl;
        }
        return res;
    }//l需要多少步跳到r？模拟链表的模式删除l-r所有中转点
    bool same(int x,int y){
        return find(x)==find(y);
    }
};
