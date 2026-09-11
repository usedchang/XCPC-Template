#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 可持久化线段树（主席树）：写时复制 + 标记永久化；接口用法与例题说明见正文。
template <typename Info>
struct PSeg {
    struct Node { int l = 0, r = 0; Info val = Info(), tag = Info(); };
    vector<Node> tr;
    PSeg() { tr.push_back(Node()); }          // 0 号哨兵：孩子为 0，val/tag 为空元
    int newnode(Node o) { tr.push_back(o); return (int)tr.size() - 1; }   // 按值传入，扩容也不会失效
    /* 区间加：返回新版本的根，不动 pre 那一版 */
    int updRange(int pre, int l, int r, int ql, int qr, Info d) {
        int u = newnode(tr[pre]);             // 写时复制
        if (ql <= l && r <= qr) {
            tr[u].val = tr[u].val + d * Info(r - l + 1);    // 整段覆盖：只改 val 与 tag
            tr[u].tag = tr[u].tag + d;
            return u;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid) tr[u].l = updRange(tr[pre].l, l, mid, ql, qr, d);
        if (qr > mid)  tr[u].r = updRange(tr[pre].r, mid + 1, r, ql, qr, d);
        // 标记永久化：本节点区间和 = 左右孩子和 + 本节点 tag × 区间长度
        tr[u].val = tr[tr[u].l].val + tr[tr[u].r].val + tr[u].tag * Info(r - l + 1);
        return u;
    }
    /* 由初始数组建版本 0 */
    int build(int l, int r, const vector<Info>& a) {
        int u = newnode(Node());
        if (l == r) { tr[u].val = a[l]; return u; }
        int mid = (l + r) >> 1;
        tr[u].l = build(l, mid, a);
        tr[u].r = build(mid + 1, r, a);
        tr[u].val = tr[tr[u].l].val + tr[tr[u].r].val;
        return u;
    }
    /* 区间和：add 为祖先链上累计的 tag */
    Info sum(int u, int l, int r, int ql, int qr, Info add = Info()) {
        if (ql <= l && r <= qr) return tr[u].val + add * Info(r - l + 1);
        int mid = (l + r) >> 1;
        Info res = Info();
        add = add + tr[u].tag;
        if (ql <= mid) res = res + sum(tr[u].l, l, mid, ql, qr, add);
        if (qr > mid)  res = res + sum(tr[u].r, mid + 1, r, ql, qr, add);
        return res;
    }
};

// 例题：HDU 4348 To the moon
//   C l r d：区间 [l,r] 每个数加 d，当前时间 +1
//   Q l r  ：询问当前时间的区间和
//   H l r t：询问时间 t 的区间和
//   B t    ：当前时间回到 t（之后再 C 会覆盖原来的时间 t+1）
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<ll> A(n + 1);
        for (int i = 1; i <= n; ++i) cin >> A[i];
        PSeg<ll> seg;
        int root = seg.build(1, n, A);
        vector<int> his;                 // his[t] = 时间 t 的根
        his.push_back(root);
        while (m--) {
            char c;
            cin >> c;
            int l, r, t;
            ll d;
            if (c == 'C') {
                cin >> l >> r >> d;
                root = seg.updRange(root, 1, n, l, r, d);
                his.push_back(root);
            } else if (c == 'Q') {
                cin >> l >> r;
                cout << seg.sum(root, 1, n, l, r) << '\n';
            } else if (c == 'H') {
                cin >> l >> r >> t;
                cout << seg.sum(his[t], 1, n, l, r) << '\n';
            } else {                      // B t：回到时间 t，之后的版本作废
                cin >> t;
                root = his[t];
                his.resize(t + 1);
            }
        }
    }
    return 0;
}
