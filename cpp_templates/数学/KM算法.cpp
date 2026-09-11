#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;

ll qpow(ll a, ll b){ ll r=1; a%=MOD; for(;b;b>>=1,a=a*a%MOD) if(b&1) r=r*a%MOD; return r; }

vector<ll> BerlekampMassey(const vector<ll>& s){
    vector<ll> ls, cur; ll lf=0, ld=0;
    for(int i=0;i<(int)s.size();i++){
        ll t=0;
        for(int j=0;j<(int)cur.size();j++) t=(t+s[i-1-j]*cur[j])%MOD;
        if((s[i]-t)%MOD==0) continue;
        if(cur.empty()){ cur.resize(i+1); lf=i; ld=(s[i]-t)%MOD; continue; }
        ll k=(s[i]-t)%MOD*qpow(((ld%MOD)+MOD)%MOD, MOD-2)%MOD;
        vector<ll> c(i-lf-1); c.push_back(k);
        for(int j=0;j<(int)ls.size();j++) c.push_back((MOD-k)*ls[j]%MOD);
        if(c.size()<cur.size()) c.resize(cur.size());
        for(int j=0;j<(int)cur.size();j++) c[j]=(c[j]+cur[j])%MOD;
        if(i-lf+(int)ls.size() >= (int)cur.size()){ ls=cur; lf=i; ld=(s[i]-t)%MOD; }
        cur=c;
    }
    for(auto&x:cur) x=(x+MOD)%MOD;
    return cur;
}

/* s[n] = rec[0]*s[n-1]+...+rec[k-1]*s[n-k] */
ll linearRecurrence(const vector<ll>& s, unsigned long long n){
    if(n < s.size()) return s[(int)n];
    vector<ll> rec = BerlekampMassey(s);
    int k = rec.size();
    if(k==0) return 0;
    vector<ll> c(k);            // x^k = c[0]x^{k-1}+...+c[k-1]
    for(int j=0;j<k;j++) c[j]=rec[k-1-j];
    auto mul = [&](const vector<ll>& p, const vector<ll>& q){
        vector<ll> t(2*k,0);
        for(int i=0;i<k;i++) if(p[i]) for(int j=0;j<k;j++) if(q[j])
            t[i+j]=(t[i+j]+p[i]*q[j])%MOD;
        for(int i=2*k-2;i>=k;i--) if(t[i])
            for(int j=0;j<k;j++) t[i-1-j]=(t[i-1-j]+t[i]*c[j])%MOD;
        vector<ll> r(k); for(int i=0;i<k;i++) r[i]=t[i]%MOD;
        return r;
    };
    vector<ll> r(k), a(k); r[0]=1; if(k>1) a[1]=1; else a[0]=rec[0];
    unsigned long long e=n;
    while(e){ if(e&1ULL) r=mul(r,a); a=mul(a,a); e>>=1ULL; }
    ll ans=0; for(int i=0;i<k;i++) ans=(ans+r[i]*s[i])%MOD;
    return ans;
}

int main(){
    unsigned long long n; cin>>n;
    vector<ll> s = {1,1,2,3,5,8,13,21,34,55};   // F_1..F_10
    cout<<linearRecurrence(s, n-1)<<"\n";      // 0-based: F_n = s[n-1]
    return 0;
}
