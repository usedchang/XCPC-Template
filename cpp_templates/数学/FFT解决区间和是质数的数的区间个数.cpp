#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define endl '\n'
struct FFT {
    using cd = complex<double>;
    const double PI = acos(-1);
    void fft(vector<cd>& a, bool invert) {
        int n = a.size();
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1)
                j ^= bit;
            j ^= bit;
            if (i < j)
                swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * PI / len * (invert ? -1 : 1);
            cd wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                cd w(1);
                for (int j = 0; j < len / 2; j++) {
                    cd u = a[i + j], v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }
        if (invert) {
            for (cd& x : a)
                x /= n;
        }
    }
    template<typename T>
    vector<ll> multiply(const vector<T>& a, const vector<T>& b) {
        vector<cd> fa(a.size()), fb(b.size());
        for (int i = 0; i < a.size(); i++) fa[i] = (double)a[i];
        for (int i = 0; i < b.size(); i++) fb[i] = (double)b[i];
        int n = 1;
        while (n < (int)(a.size() + b.size() - 1)) n <<= 1;
        fa.resize(n);
        fb.resize(n);
        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < n; ++i) fa[i] *= fb[i];
        fft(fa, true);
        vector<ll> res(a.size() + b.size() - 1);
        for (int i = 0; i < res.size(); i++) res[i] = llround(fa[i].real());
        return res;
    }
};
const int N=1e6+5;
bitset<N>isp;
vector<int>p;
void init(int n){
    p.reserve(n/10);
    isp.set();
    isp[0]=isp[1]=false;
    for(int i=2;i<=n;i++){
        if(isp[i]) p.push_back(i);
        else continue;
        for(int j=i*2;j<=n;j+=i) isp[j]=false;
    }
}
void solve(){
    int n;cin>>n;
    vector<ll>a(n+1),pre(n+1);
    for(int i=1;i<=n;i++) cin>>a[i],pre[i]=pre[i-1]+a[i];
    vector<int>vis(pre[n]+1);
    vis[0]=1;
    for(int i=1;i<=n;i++) vis[pre[i]]=1;
    vector<int>B(vis.rbegin(),vis.rend());
    FFT fft;
    vector<ll>C=fft.multiply(vis,B);
    ll ans=0;
    for(int x:p){
        if(x>pre[n]) break;
        ans+=C[pre[n]+x];
    }
    cout<<ans<<endl;
}
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    init(1e6);int T=1;cin>>T;
    while(T--) solve();
    return 0;
}
