//P2398 GCD-SUM
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int N=1e5+5;
ll p[N],vis[N],cnt;
ll mu[N],pre[N],phi[N];
void init(int n){
    mu[1]=phi[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            p[cnt++]=i;
            mu[i]=-1;
            phi[i]=i-1;
        }
        for(int j=0;i*p[j]<=n;j++){
            int m=i*p[j];
            vis[m]=1;
            if(i%p[j]==0){
                mu[m]=0;
                phi[m]=phi[i]*p[j];
                break;
            }
            phi[m]=phi[i]*(p[j]-1);
            mu[m]=-mu[i];
        }
    }
    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+phi[i];
}
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    ll ans=0;
    ll n;cin>>n;
    init(n+5);
    for(int l=1,r;l<=n;l=r+1){
        ll v=n/l;
        r=n/v;
        ans+=v*v*(pre[r]-pre[l-1]);
    }
    cout<<ans<<endl;
    return 0;
}
