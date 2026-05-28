#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<pair<ll, int>> gen(vector<ll> a) {
    vector<pair<ll, int>> res;
    int k = a.size();
    for (int mask=0; mask<(1<<k); mask++) {
        ll s=0;
        for (int i=0; i<k; i++) if (mask&(1<<i)) s += a[i];
        res.emplace_back(s, mask);
    }
    sort(res.begin(), res.end());
    return res;
}

int main() {
    int n; ll c;
    scanf("%d%lld", &n, &c);
    vector<ll> w(n);
    for (int i=0; i<n; i++) scanf("%lld", &w[i]);
    int mid = n/2;
    vector<ll> L(w.begin(), w.begin()+mid), R(w.begin()+mid, w.end());
    auto ls = gen(L), rs = gen(R);
    ll maxw=0; int lm=0, rm=0;
    for (auto [sb, m]: rs) {
        if (sb > c) continue;
        ll rem = c - sb;
        int pos = upper_bound(ls.begin(), ls.end(), make_pair(rem, (1<<mid)-1)) - ls.begin() - 1;
        if (pos >=0 && ls[pos].first + sb > maxw) {
            maxw = ls[pos].first + sb;
            lm = ls[pos].second;
            rm = m;
        }
    }
    vector<int> ans(n);
    for (int i=0; i<mid; i++) ans[i] = (lm >> i) & 1;
    for (int i=0; i<n-mid; i++) ans[mid+i] = (rm >> i) & 1;
    printf("%lld\n", maxw);//最优代价
    for (int i=0; i<n; i++) printf("%d ", ans[i]);//最优方案输出
    return 0;
}
