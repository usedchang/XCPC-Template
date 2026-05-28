#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;
// ========== 快速乘（取模） ==========
ll mul_mod(ll a, ll b, ll mod) {
    return (ll)((i128)a * b % mod);
}
// ========== 快速幂取模 ==========
ll q_pow(ll a, ll d, ll mod) {
    ll res = 1;
    a %= mod;
    while (d) {
        if (d & 1) res = mul_mod(res, a, mod);
        a = mul_mod(a, a, mod);
        d >>= 1;
    }
    return res;
}
// ========== Miller–Rabin 确定性判素数 ==========
bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    ll d = n - 1;
    int r = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++r;
    }
    // 底数集合（对 2^64 以内确定性）
    static const ll bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for (ll a : bases) {
        if (a % n == 0) continue;
        ll x = q_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool comp = true;
        for (int i = 0; i < r - 1; ++i) {
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                comp = false;
                break;
            }
        }
        if (comp) return false;
    }
    return true;
}
// ========== 最大公约数 ==========
// ========== Pollard–Rho 分解因子（参考你的高效写法） ==========
// 小质数表，用于提前试除
const vector<ll> small_primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
ll pollard_rho(ll n) {
    // 先试除小质数
    for (ll p : small_primes) {
        if (n % p == 0) return p;
    }

    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<ll> dist(1, n - 1);
    auto f = [&](ll x) -> ll {
        x = mul_mod(x, x, n) + 1;
        return x >= n ? x - n : x;
    };
    ll x = 0, y = 0, tot = 0, p = 1, q, g;
    for (ll i = 0; (i & 255) || (g = gcd(p, n)) == 1; ++i) {
        x = f(x);
        y = f(f(y));
        if (x == y) {
            x = ++tot;
            y = f(x);
        }
        q = mul_mod(p, (x > y ? x - y : y - x), n);
        if (q) p = q;
    }
    return g;
}
// ========== 递归分解，更新最大质因子 ==========
ll max_factor = 0 , n;
ll min_factor ;   // 初始化为 n
void factorize_mx(ll n) {
    if (n <= max_factor || n < 2) return;
    if (is_prime(n)) {
        max_factor = max(max_factor, n);
        return;
    }
    ll d = pollard_rho(n);
    factorize_mx(d);
    factorize_mx(n / d);
}
void factorize_mn(ll n) {
    if (n <= 1) return;
    if (is_prime(n)) {
        min_factor = min(min_factor, n);
        return;
    }
    ll d = pollard_rho(n);
    factorize_mn(d);
    factorize_mn(n / d);
}
int main() {
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    int T;cin >> T;
    while (T--) {
        cin >> n;  
        max_factor = 0,min_factor = n;
        factorize_mx(n);
        if (max_factor == n) cout << "Prime\n";
        else cout << max_factor << '\n';
    }
    return 0;
}
