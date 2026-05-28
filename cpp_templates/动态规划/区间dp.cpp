//P1995 石子合并
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int N=105;
const ll INF=1e12;
ll a[N<<1],pre[N<<1];
ll Mx[N<<1][N<<1],Mn[N<<1][N<<1];
ll mx(int l,int r){
    if(Mx[l][r]!=-1) return Mx[l][r];
    if(l==r) return a[l];
    ll ans=0;
    for(int k=l;k+1<=r;k++){
        ans=max(ans,mx(l,k)+mx(k+1,r));
    }
    return Mx[l][r]=ans+(pre[r]-pre[l-1]);
}
ll mn(int l,int r){
    if(Mn[l][r]!=-1) return Mn[l][r];
    if(l==r) return a[l];
    ll ans=INF;
    for(int k=l;k+1<=r;k++){
        ans=min(ans,mn(l,k)+mn(k+1,r));
    }
    return Mn[l][r]=ans+(pre[r]-pre[l-1]);
}
void solve(){
    int n;cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],a[i+n]=a[i];
    for(int i=1;i<=n*2;i++) pre[i]=pre[i-1]+a[i];
    memset(Mx,-1,sizeof Mx);
    memset(Mn,-1,sizeof Mn);
    ll ans1=0,ans2=INF;
    for(int i=1;i<=n;i++){
        int l=i,r=n+i-1;
        ans1=max(ans1,mx(l,r)-(pre[r]-pre[l-1]));
        ans2=min(ans2,mn(l,r)-(pre[r]-pre[l-1]));
    }
    cout<<ans2<<endl<<ans1<<endl;
}
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    solve();
    return 0;
}
