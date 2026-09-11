struct NTT {
    static const int MOD = 998244353;
    static const int G = 3;
    /*
    ntt友好模数 原根
    998244353 3
    469762049 3
    167772161 3
    1004535809 3
    754974721 11
    */
    static ll qpow(ll a, ll b) {
        ll res = 1;
        while (b) {
            if (b & 1) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }
    static void ntt(vector<ll>& a, bool invert) {
        int n = a.size();
        // 位逆序
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            while (j & bit) {
                j ^= bit;
                bit >>= 1;
            }
            j ^= bit;
            if (i < j) {
                swap(a[i], a[j]);
            }
        }
        // 蝴蝶操作
        for (int len = 2; len <= n; len <<= 1) {
            ll wlen = qpow(G, (MOD - 1) / len);
            if (invert) {
                wlen = qpow(wlen, MOD - 2);
            }
            for (int i = 0; i < n; i += len) {
                ll w = 1;
                for (int j = 0; j < len / 2; j++) {
                    ll u = a[i + j];
                    ll v = a[i + j + len / 2] * w % MOD;
                    ll x = u + v;
                    if (x >= MOD) x -= MOD;
                    ll y = u - v;
                    if (y < 0) y += MOD;
                    a[i + j] = x;
                    a[i + j + len / 2] = y;
                    w = w * wlen % MOD;
                }
            }
        }
        if (invert) {
            ll inv_n = qpow(n, MOD - 2);
            for (ll& x : a) {
                x = x * inv_n % MOD;
            }
        }
    }
    static vector<ll> multiply(vector<ll> a, vector<ll> b) {
        if (a.empty() || b.empty()) {
            return {};
        }
        // 小规模直接暴力卷积，常数更小
        if (min(a.size(), b.size()) <= 32) {
            vector<ll> c(a.size() + b.size() - 1);
            for (int i = 0; i < (int)a.size(); i++) {
                for (int j = 0; j < (int)b.size(); j++) {
                    c[i + j] = (c[i + j] + a[i] * b[j]) % MOD;
                }
            }
            return c;
        }
        int need = (int)a.size() + (int)b.size() - 1;
        int n = 1;
        while (n < need) {
            n <<= 1;
        }
        a.resize(n);
        b.resize(n);
        ntt(a, false);
        ntt(b, false);
        for (int i = 0; i < n; i++) {
            a[i] = a[i] * b[i] % MOD;
        }
        ntt(a, true);
        a.resize(need);
        return a;
    }
};