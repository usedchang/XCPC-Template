#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
struct BIT {
    vector<ll>a;
    int n;
    BIT(int n):n(n+1){ a.resize(n<<1);}
    void add(int x,ll k) {
        while (x<=n) {
            a[x]+=k;
            x+=x&-x;
        }
    }
    int qry(int x) {
        ll ans=0;
        while (x) {
            ans+=a[x];
            x&=x-1;
        }
        return ans;
    }
};
struct Query{
    int L, R, idx;
    bool operator<(const Query& other) const {
        return R < other.R;
    }
};
int n,q;
void solve(){
    vector<int>a(n+1);
    for (int i=1;i<=n;i++) cin>>a[i];
    vector<Query>qs(q);
    for (int i=0;i<q;i++) {
        cin>>qs[i].L>>qs[i].R;
        qs[i].idx=i;
    }
    sort(qs.begin(),qs.end());
    BIT S(n+1);
    vector<pair<int, int>> prev;
    map<int,int>las;
    vector<int>ans(q);
    int q_ptr=0;
    for (int i=1;i<=n;i++) {
        vector<pair<int,int>>cur;
        cur.emplace_back(a[i],i);
        for (auto& p:prev) cur.emplace_back(gcd(p.first,a[i]),p.second);
        vector<pair<int,int>> merged;
        for (auto& p:cur) {
            if (merged.empty()||merged.back().first!=p.first) {
                merged.push_back(p);
            }
        }
        for(auto& [g,l] :merged) {
            if (las.count(g)) S.add(las[g],-1);
            S.add(l,1);
            las[g]=l;
        }
        while(q_ptr<q&&qs[q_ptr].R==i) {
            int L=qs[q_ptr].L;
            int R=qs[q_ptr].R;
            int idx=qs[q_ptr].idx;
            ans[idx]=S.qry(R)-S.qry(L - 1);
            q_ptr++;
        }
        prev=move(merged);
    }
    for (int x:ans) cout<<x<<endl;
}
int main() {
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    while(cin>>n>>q) solve();
    return 0;
}
