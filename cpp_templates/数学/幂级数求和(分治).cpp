#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 分治求 S_i(n) = sum_{k=1..n} k^i x^k（i = 0..deg）：推导、复杂度与用法见正文。
struct PolyExpSum {
    ll mod;                     // 模数
    int deg;                    // 多项式次数：f(y) = y^deg
    ll base;                    // 底数 x（已取模）
    vector<vector<ll>> C;       // 杨辉三角（组合数）
    struct Node {
        vector<ll> s;           // s[i] = S_i(m) = sum_{k=1}^{m} k^i x^k
        ll pw;                  // x^m
    };

    ll powmod(ll a, ll b) const {      // 快速幂：先取模，避免底数 >= mod 时溢出
        a %= mod;
        ll r = 1 % mod;
        while (b) {
            if (b & 1) r = r * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return r;
    }
    /* 返回 S_0..S_deg(n) 与 x^n */
    Node dfs(ll n) {
        if (n == 0) return {vector<ll>(deg + 1, 0), 1 % mod};
        if (n == 1) return {vector<ll>(deg + 1, base), base};   // S_i(1) = 1^i · x = x
        Node half = dfs(n / 2);
        ll m = n / 2;
        vector<ll> res(deg + 1);
        for (int i = 0; i <= deg; ++i) {                        // 先算 S_i(2m)
            ll add = 0;
            for (int j = 0; j <= i; ++j) {                      // sum_{j} C(i,j) m^{i-j} S_j(m)
                ll t = C[i][j] * powmod(m, i - j) % mod * half.s[j] % mod;
                add = (add + t) % mod;
            }
            res[i] = (half.s[i] + add * half.pw) % mod;         // 再乘上 x^m
        }
        ll cur = half.pw * half.pw % mod;                       // x^{2m}
        if (n & 1) {                                            // 奇数长度补一项 S_i(2m+1)
            ll last = cur * base % mod;                         // x^{2m+1}
            for (int i = 0; i <= deg; ++i)
                res[i] = (res[i] + powmod(n, i) * last) % mod;  // +(2m+1)^i · x^{2m+1}
            cur = last;
        }
        return {res, cur};
    }

    PolyExpSum(int degree, ll a, ll m) : mod(m), deg(degree), base(a % m) {
        C.assign(deg + 1, vector<ll>(deg + 1, 0));
        for (int i = 0; i <= deg; ++i) {
            C[i][0] = C[i][i] = 1 % mod;
            for (int j = 1; j < i; ++j)
                C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }
    /* sum_{k=1}^{n} k^deg · x^k mod mod */
    ll query(ll n) { return dfs(n).s[deg]; }
};

// 例：sum_{k=1}^{10} k^3 · 3^k，以及一般多项式 f(y)=2y^2+y（线性组合各次幂和）
int main() {
    const ll MOD = 1000000007LL;
    PolyExpSum f(3, 3, MOD);
    cout << f.query(10) << '\n';
    PolyExpSum g(2, 5, MOD);                    // 取出 S_0..S_2 自己组合
    auto s = g.dfs(10);
    ll ans = (2 * s.s[2] + s.s[1]) % MOD;       // f(y) = 2y^2 + y
    cout << ans << '\n';
    return 0;
}
