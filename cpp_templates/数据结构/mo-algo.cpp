//P2709 小B的询问
const int N=5e4+10;
int a[N],pos[N],cnt[N];
ll res,ans[N];
struct Q{
    int l,r,k;
}q[N];
void Add(int n){
    cnt[a[n]]++;
    res+=cnt[a[n]]*cnt[a[n]]-(cnt[a[n]]-1)*(cnt[a[n]]-1);
}
void Sub(int n){
    cnt[a[n]]--;
    res-=(cnt[a[n]]+1)*(cnt[a[n]]+1)-(cnt[a[n]])*(cnt[a[n]]);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m,k;cin>>n>>m>>k;
    int siz=sqrt(n+0.5);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        pos[i]=i/siz;
    }
    for(int i=0;i<m;i++){
        cin>>q[i].l>>q[i].r;
        q[i].k=i;
    }
    sort(q,q+m,[](Q x,Q y){
        return pos[x.l]==pos[y.l]?x.r<y.r:pos[x.l]<pos[y.l];
    });
    int l=1,r=0;
    for(int i=0;i<m;i++){
        while(q[i].l<l) Add(--l);
        while(q[i].r>r) Add(++r);
        while(q[i].l>l) Sub(l++);
        while(q[i].r<r) Sub(r--);
        ans[q[i].k]=res;
    }
    for(int i=0;i<m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
