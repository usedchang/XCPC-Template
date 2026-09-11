#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 505;
const ll INF = (ll)4e18;
// 不存在的边用 NEG 表示：足够小（不会被选中），又不会让 lx+ly-w 溢出 ll
const ll NEG = -(ll)4e15;

// 二分图最大权完美匹配（KM 算法，O(n^2 m)）：左部 n 点、右部 m 点（要求 n <= m），
// 不存在的边填 NEG。输入输出格式、变体改法与用法见正文。
int n, m, e;
ll w[MAXN][MAXN];
ll lx[MAXN], ly[MAXN], slack[MAXN];  // 左右部顶点标号、slack
int match[MAXN], matchL[MAXN];       // match[j]=右部 j 匹配的左部点
int pre[MAXN];
bool visy[MAXN];

void km() {
    fill(lx + 1, lx + n + 1, 0);
    fill(ly + 1, ly + m + 1, 0);
    fill(match, match + m + 1, 0);
    // 初始标号：左部取关联边的最大权，右部取 0
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) lx[i] = max(lx[i], w[i][j]);
    for (int u = 1; u <= n; ++u) {
        fill(slack, slack + m + 1, INF);
        fill(visy, visy + m + 1, false);
        match[0] = u;                       // 0 号虚点：本轮要增广的左部点
        int y = 0;
        do {
            visy[y] = true;                 // y 进入交错树
            int x = match[y], ny = 0;
            ll d = INF;
            for (int j = 1; j <= m; ++j) {
                if (visy[j]) continue;
                ll t = lx[x] + ly[j] - w[x][j];   // 松驰量
                if (t < slack[j]) { slack[j] = t; pre[j] = y; }
                if (slack[j] < d) { d = slack[j]; ny = j; }
            }
            // 更新标号：交错树上的点 lx 减 d、ly 加 d，其余 slack 减 d
            for (int j = 0; j <= m; ++j) {
                if (visy[j]) { lx[match[j]] -= d; ly[j] += d; }
                else slack[j] -= d;
            }
            y = ny;
        } while (match[y]);                 // 直到找到一个未匹配的右部点
        while (y) { int py = pre[y]; match[y] = match[py]; y = py; }  // 沿 pre 回溯增广
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> e;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) w[i][j] = NEG;
    for (int k = 0; k < e; ++k) {
        int u, v; ll x;
        cin >> u >> v >> x;
        w[u][v] = x;
    }
    km();
    ll ans = 0;
    for (int i = 1; i <= n; ++i) matchL[i] = 0;
    for (int j = 1; j <= m; ++j)
        if (match[j]) { ans += w[match[j]][j]; matchL[match[j]] = j; }
    cout << ans << '\n';
    for (int i = 1; i <= n; ++i) cout << matchL[i] << " \n"[i == n];
    return 0;
}
