#include <bits/stdc++.h>
using namespace std;

// 博弈论 SG 打表找规律：本文件含打表程序（#if 0 包住，改成 #if 1 可单独运行）与正解；
// 例题题面、P 态规律与用法见正文。

/* ========== 1) 暴力 SG 打表（只打印必败态，规律最直观） ========== */
#if 0
map<vector<int>, int> memo;
int sg(vector<int> a) {
    sort(a.begin(), a.end());                 // 状态规范化：只和多重集有关
    if (a.back() == 0) return memo[a] = 0;    // 全 0：当前玩家无法行动，负
    if (memo.count(a)) return memo[a];
    set<int> nxt;
    int n = a.size();
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) continue;
        if (i && a[i] == a[i - 1]) continue;  // 同值只试一次
        vector<int> b = a;
        for (int j = 0; j < n; j++) b[j] = min(b[j], a[i]);  // 先对所有 j != i 取 min
        b[i]--;                                              // 再把自己减 1
        nxt.insert(sg(b));
    }
    int g = 0;
    while (nxt.count(g)) g++;                 // mex
    return memo[a] = g;
}
void dfs(int pos, int minv, int n, int V, vector<int>& a) {
    if (pos == n) {
        if (sg(a) == 0) {                     // 只打印 P 态
            for (int x : a) printf("%d ", x);
            printf("\n");
        }
        return;
    }
    for (int v = minv; v <= V; v++) { a[pos] = v; dfs(pos + 1, v, n, V, a); }
}
int main() {
    for (int n = 1; n <= 4; n++) {
        printf("n=%d:\n", n);
        vector<int> a(n, 1);
        dfs(0, 1, n, 4, a);                   // 值域 [1,4]
    }
    return 0;
}
#endif

/* ========== 2) 正解：排序 + 配对判奇偶 ========== */
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        vector<int> a(n);
        for (auto& x : a) scanf("%d", &x);
        sort(a.begin(), a.end());
        bool lose = true;                         // 先手是否必败
        if (n & 1) {
            if (a[0] % 2 != 0) lose = false;      // 落单的最小值必须为偶数
            for (int i = 1; i + 1 < n; i += 2)
                if ((a[i] ^ a[i + 1]) & 1) lose = false;   // 每对同奇偶
        } else {
            for (int i = 0; i + 1 < n; i += 2)
                if ((a[i] ^ a[i + 1]) & 1) lose = false;
        }
        puts(lose ? "Maya" : "Insight");
    }
    return 0;
}
