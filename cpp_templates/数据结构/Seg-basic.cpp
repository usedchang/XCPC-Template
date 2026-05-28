struct Seg{
    #define lc (p<<1)
    #define rc (p<<1|1)
    struct S{
        int l,r;
        ll val,laz;
    };
    Seg(){};
    Seg(int n){
        tre.resize(n<<2);
        build(0,n,1);
    };
    void pushup(int p){
        tre[p].val=tre[lc].val+tre[rc].val;
    }
    void pushdown(int p){
        if(tre[p].laz==0) return;
        tre[lc].laz+=tre[p].laz;
        tre[rc].laz+=tre[p].laz;
        tre[lc].val+=tre[p].laz;
        tre[rc].val+=tre[p].laz;
        tre[p].laz=0;
    }
    void build(int l,int r,int p){
        tre[p]={l,r,0,0};
        if(l==r){
            tre[p]=a[l];
            return;
        }
        int mid=l+r>>1;
        build(l,mid,lc);
        build(mid+1,r,rc);
        pushup(p);
    }
    void add(int l,int r,ll k,int p){
        if(l<=tre[p].l&&r>=tre[p].r){
            tre[p].val+=k*(tre[p].r-tre[p].l+1);
            tre[p].laz+=k;
            return;
        }
        int mid=tre[p].l+tre[p].r>>1;
        pushdown(p);
        if(l<=mid) add(l,r,k,lc);
        if(r>mid) add(l,r,k,rc);
        pushup(p);
    }
    ll qry(int l,int r,int p){
        if(l<=tre[p].l&&r>=tre[p].r){
            return tre[p].val;
        }
        int mid=tre[p].l+tre[p].r>>1;
        pushdown(p);
        ll ans=0;
        if(l<=mid) ans+=qry(l,r,lc);
        if(r>mid) ans+=qry(l,r,rc);
        return ans;
    }
};
