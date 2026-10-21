// exgcd 求逆元与线性同余：用法、推导与复杂度见正文。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 返回 gcd(a,b)，并求出一组 ax+by=gcd(a,b) 的解
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// a 在模 m 下的逆元，要求 gcd(a,m)=1；返回 [0,m)
ll inv(ll a, ll m) {
    a %= m;
    if (a < 0) a += m;
    ll x, y;
    ll d = exgcd(a, m, x, y);
    assert(d == 1);              // 不互质时没有逆元
    return (x % m + m) % m;
}

// 解 ax ≡ b (mod m)。无解返回 false；
// 有解返回最小非负特解 x，通解为 x + k*(m/gcd(a,m))
bool lineq(ll a, ll b, ll m, ll &x) {
    if (m < 0) m = -m;
    a %= m;
    if (a < 0) a += m;
    b %= m;
    if (b < 0) b += m;
    ll g = __gcd(a, m);
    if (b % g != 0) return false;
    a /= g, b /= g, m /= g;
    __int128 x0 = (__int128)b * inv(a, m) % m;
    x = (ll)x0;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {                 // 求逆元
            ll a, m;
            cin >> a >> m;
            cout << inv(a, m) << '\n';
        } else {                       // ax=b (mod m)
            ll a, b, m, x;
            cin >> a >> b >> m;
            if (lineq(a, b, m, x))
                cout << x << '\n';
            else
                cout << "No\n";
        }
    }
    return 0;
}
