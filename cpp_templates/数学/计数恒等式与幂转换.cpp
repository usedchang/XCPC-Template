// 计数恒等式：曲棍球棒 / 范德蒙德 / 幂转下降幂
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1005;
const ll MOD = 998244353;
ll C[N][N];    // 组合数
ll S2[N][N];   // 第二类斯特林数

void init(int n) {
    for (int i = 0; i <= n; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            C[i][j] = (C[i - 1][j - 1]
                     + C[i - 1][j]) % MOD;
        }
    }
    S2[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            S2[i][j] = (S2[i - 1][j - 1]
                      + j * S2[i - 1][j]) % MOD;
        }
    }
}

// 曲棍球棒：sum C(i,r) = C(n+1,r+1)
ll hock(int n, int r) {
    ll s = 0;
    for (int i = r; i <= n; ++i)
        s = (s + C[i][r]) % MOD;
    return s;
}

// 范德蒙德：sum C(a,k)C(b,n-k) = C(a+b,n)
ll vander(int a, int b, int n) {
    ll s = 0;
    int lo = max(0, n - b);
    int hi = min(a, n);
    for (int k = lo; k <= hi; ++k) {
        s = (s + C[a][k] * C[b][n - k]) % MOD;
    }
    return s;
}

// x 的 k 次下降幂：x(x-1)...(x-k+1)
ll fall(ll x, int k) {
    x %= MOD;
    if (x < 0) x += MOD;
    ll r = 1;
    for (int i = 0; i < k; ++i) {
        r = r * ((x - i + MOD) % MOD) % MOD;
    }
    return r;
}

ll pw(ll a, ll e) {
    ll r = 1;
    a %= MOD;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    init(1000);
    assert(hock(10, 3) == C[11][4]);
    ll v = vander(5, 7, 4);
    assert(v == C[12][4]);
    for (int n = 0; n <= 50; ++n)
        for (int r = 0; r <= n; ++r)
            assert(hock(n, r)
                   == C[n + 1][r + 1]);
    for (int a = 0; a <= 30; ++a)
        for (int b = 0; b <= 30; ++b)
            for (int n = 0; n <= a + b; ++n) {
                assert(vander(a, b, n)
                       == C[a + b][n]);
            }

    // x^20 = sum S2[20][k] * x 的下降幂
    for (ll x = 0; x <= 20; ++x) {
        ll rhs = 0;
        for (int k = 0; k <= 20; ++k) {
            rhs = (rhs + S2[20][k]
                   * fall(x, k)) % MOD;
        }
        assert(rhs == pw(x, 20));
    }
    cout << "ok\n";
    return 0;
}
