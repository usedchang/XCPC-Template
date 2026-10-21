// P2257 YY的GCD：求 1<=x<=N, 1<=y<=M 且 gcd(x,y) 为质数的有序对数量。
// 多组询问，T<=1e4，N,M<=1e7；线性筛 + 预处理 f(T) 前缀和 + 整除分块。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 10000000;
signed char mu[MAXN + 1];   // 莫比乌斯函数，取值 -1/0/1
int f[MAXN + 1];            // f(T) = sum_{p|T, p prime} mu(T/p)
int pre[MAXN + 1];          // f 的前缀和
vector<int> primes;
bitset<MAXN + 1> composite;

void init(int n) {
    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!composite[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            if (1LL * i * p > n) break;
            composite[i * p] = 1;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }
    // 计算 f(T)
    for (int p : primes) {
        for (int t = p; t <= n; t += p) {
            f[t] += mu[t / p];
        }
    }
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + f[i];
    }
}

ll solve(int n, int m) {
    if (n > m) swap(n, m);
    ll ans = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        ans += 1LL * (n / l) * (m / l)
             * (pre[r] - pre[l - 1]);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    vector<pair<int, int>> qs(T);
    int max_n = 1;
    for (auto &[n, m] : qs) {
        cin >> n >> m;
        max_n = max({max_n, n, m});
    }
    init(max_n);
    for (auto [n, m] : qs) {
        cout << solve(n, m) << '\n';
    }
    return 0;
}
