struct DSU{
    vector<int>f;
    vector<int>siz;
    DSU(){};
    DSU(int n){
        f.resize(n+2);          // n+1 作为 nxt 的哨兵
        iota(f.begin(),f.end(),0);
        siz.assign(n+2,1);
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
        int res=0;
        l=find(l);
        while(l<=r){
            ++res;
            l=f[l]=find(l+1);
        }
        return res;
    }//l需要多少步跳到r？模拟链表的模式删除l-r所有中转点
    bool same(int x,int y){
        return find(x)==find(y);
    }
};
