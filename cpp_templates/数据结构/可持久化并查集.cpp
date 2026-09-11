#include <bits/stdc++.h>
using namespace std;

// 可持久化并查集：主席树上维护 fa 与秩，按秩合并、不路径压缩；
// 输入格式与用法见正文。
const int N = 2e5 + 5;
int n, m, tot;
int ls[N * 25], rs[N * 25], fa[N * 25], dep[N * 25];
int root[N];                 // root[i] = 版本 i 的根（版本 0 是初始状态）

void build(int &p, int l, int r) {
    p = ++tot;
    if (l == r) { fa[p] = l; dep[p] = 1; return; }
    int mid = (l + r) >> 1;
    build(ls[p], l, mid);
    build(rs[p], mid + 1, r);
}
/* 把位置 pos 的 (fa, dep) 改成 (nf, nd)，返回新根 */
void modify(int &p, int pre, int l, int r, int pos, int nf, int nd) {
    p = ++tot;
    ls[p] = ls[pre];
    rs[p] = rs[pre];
    if (l == r) { fa[p] = nf; dep[p] = nd; return; }
    int mid = (l + r) >> 1;
    if (pos <= mid) modify(ls[p], ls[pre], l, mid, pos, nf, nd);
    else            modify(rs[p], rs[pre], mid + 1, r, pos, nf, nd);
}
int queryFa(int p, int l, int r, int pos) {
    while (l < r) {
        int mid = (l + r) >> 1;
        if (pos <= mid) { p = ls[p]; r = mid; }
        else { p = rs[p]; l = mid + 1; }
    }
    return fa[p];
}
int queryDep(int p, int l, int r, int pos) {
    while (l < r) {
        int mid = (l + r) >> 1;
        if (pos <= mid) { p = ls[p]; r = mid; }
        else { p = rs[p]; l = mid + 1; }
    }
    return dep[p];
}
int find(int rt, int x) {                 // 不压缩路径，按秩合并保证 O(log n) 层
    int f = queryFa(rt, 1, n, x);
    while (f != x) { x = f; f = queryFa(rt, 1, n, x); }
    return x;
}

int main() {
    scanf("%d %d", &n, &m);
    build(root[0], 1, n);
    for (int i = 1; i <= m; ++i) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int a, b;
            scanf("%d %d", &a, &b);
            int ra = find(root[i - 1], a), rb = find(root[i - 1], b);
            if (ra == rb) { root[i] = root[i - 1]; continue; }
            int da = queryDep(root[i - 1], 1, n, ra), db = queryDep(root[i - 1], 1, n, rb);
            if (da > db) { swap(ra, rb); swap(da, db); }   // 让 ra 的秩不小于 rb
            int t;
            modify(t, root[i - 1], 1, n, rb, ra, db);      // rb 的父亲改成 ra
            if (da == db) {                                // 秩相同：ra 的秩 +1
                int t2;
                modify(t2, t, 1, n, ra, ra, da + 1);
                root[i] = t2;
            } else {
                root[i] = t;
            }
        } else if (op == 2) {
            int k;
            scanf("%d", &k);
            root[i] = root[k];                             // 回到版本 k
        } else {
            int a, b;
            scanf("%d %d", &a, &b);
            root[i] = root[i - 1];                         // 询问不产生新版本
            printf("%d\n", find(root[i], a) == find(root[i], b) ? 1 : 0);
        }
    }
    return 0;
}
