ll q_pow(ll x,ll y,ll mod){
    ll s=1;
    while(y>0){
        if(y&1){
            s=s*x%mod;
        }
        x=x*x%mod;
        y>>=1;
    }
    return s;
}
ll exgcd(ll a,ll b,ll &x,ll &y){
    if(!b){
        x=1,y=0;
        return a;
    }
    ll d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
ll inv(ll a,ll mod){
    ll x,y;
    exgcd(a,mod,x,y);
    return (x%mod+mod)%mod;
}
ll exBSGS(ll a,ll b,ll p){
    if(b==1||p==1) return 0;
    a%=p,b%=p;
    ll cnt=0;
    ll d=gcd(a,p);
    while(d>1){
        if(b%d!=0) return -1;
        p/=d;
        b=b/d*inv(a/d,p)%p;
        ++cnt;
        if(b==1) return cnt;
        d=gcd(a,p);
    }
    if(p==1) return cnt;
    unordered_map<ll,ll>mp;
    ll m=ceil(sqrt(p));
    ll e=1;
    for(ll j=0;j<m;++j){
        if(!mp.count(e)) mp[e]=j;
        e=e*a%p;
    }
    ll inv_am=inv(q_pow(a,m,p),p);
    ll cur=b;
    for(ll i=0;i<=m;i++){
        if(mp.count(cur)){
            return i*m+mp[cur]+cnt;
        }
        cur=cur*inv_am%p;
    }
    return -1;
}