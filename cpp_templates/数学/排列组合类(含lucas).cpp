const ll mod=998244353;
vector<ll>fac,invfac;
ll q_pow(ll x,ll y){
    ll s=1;
    x%=mod;
    while(y>0){
        if(y&1){
            s=s*x%mod;
        }
        x=x*x%mod;
        y>>=1;
    }
    return s;
}
void init(int n){
    fac.resize(n+1);
    invfac.resize(n+1);
    fac[0]=invfac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    invfac[n]=q_pow(fac[n],mod-2);
    for(int i=n-1;i>=1;i--) invfac[i]=invfac[i+1]*(i+1)%mod;
}
ll C(ll n,ll m){
    if(n<m) return 0;
    if(n<mod&&m<mod) return fac[n]*invfac[m]%mod*invfac[n-m]%mod;
    return C(n/mod,m/mod)*C(n%mod,m%mod)%mod;
}
