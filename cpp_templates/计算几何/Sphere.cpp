struct Sphere {
    P3 o;
    ld r = -1;
};
bool inside(const Sphere& s, P3 p) {
    if (s.r < 0) return false;
    return dist(s.o, p) <= s.r + EPS;
}
Sphere sphere1(P3 a) { return {a, 0};}// 一个点确定半径 0 球
Sphere sphere2(P3 a, P3 b) {
    P3 o = (a + b) / 2;
    return {o,dist(a, b) / 2};
}// 两点确定直径球
// 三个非共线点
// 返回它们所在平面中的外接圆
// 把这个圆视为 3D 球的截面
// 这是经过三点的最小半径球心
Sphere sphere3(P3 a, P3 b, P3 c) {
    P3 u = b - a,v = c - a,w = cross(u, v);
    ld mx = max({ dist(a, b), dist(a, c), dist(b, c)});
    if (mx <= EPS) return {{0, 0, 0}, -1};
    // |u×v| / max_edge 是长度量
    if (len(w) <= EPS * mx) return {{0, 0, 0}, -1};
    ld w2 = len2(w),u2 = len2(u),v2 = len2(v);
    P3 q = (cross(v, w) * u2 + cross(w, u) * v2)/ (2 * w2);
    P3 o = a + q;
    return {o, dist(o, a)};
}
Sphere sphere4(P3 a, P3 b, P3 c, P3 d) {
    P3 u = b - a,v = c - a,w = d - a;
    P3 vxw = cross(v, w);
    ld area = len(vxw);
    ld base_scale = max({len(v),len(w),len(v - w)});
    // v,w 基本共线
    if (base_scale <= EPS ||area <= EPS * base_scale) return {{0, 0, 0}, -1};
    ld det = dot(u, vxw);
    // |det| / |v×w| = u 到 vw 所在平面的距离
    if (fabsl(det) <= EPS * area) return {{0, 0, 0}, -1};
    P3 q = (cross(v, w) * len2(u) + cross(w, u) * len2(v) + cross(u, v) * len2(w)) / (2 * det);
    P3 o = a + q;
    return {o, dist(o, a)};
}// 四个非共面点唯一确定外接球
// R <= 4
// 暴力枚举哪个子集真正决定最小球
// 这样可以处理：
// - 重复点
// - 三点共线
// - 四点共面
// - 钝角三角形实际上由两个点决定
Sphere trivial_ball(const vector<P3>& R) {
    int m = (int)R.size();
    if (m == 0) return {{0, 0, 0}, -1};
    Sphere best{{0, 0, 0},INF};
    for (int mask = 1;mask < (1 << m);++mask) {
        vector<P3> q;
        for (int i = 0; i < m; ++i) {
            if (mask >> i & 1) q.push_back(R[i]);
        }
        Sphere s{ {0, 0, 0},-1};
        if (q.size() == 1) s = sphere1(q[0]);
        else if (q.size() == 2) s = sphere2(q[0],q[1]);
        else if (q.size() == 3) s = sphere3(q[0],q[1],q[2]);
        else if (q.size() == 4) s = sphere4(q[0],q[1],q[2],q[3]);
        if (s.r < 0) continue;
        bool ok = true;
        for (P3 p : R) {
            if (!inside(s, p)) {
                ok = false;
                break;
            }
        }
        if (ok && s.r < best.r) best = s;
    }
    return best;
}
// WARNING:
// Welzl recursion depth = O(n).
// n 很大（例如 1e6 级）有栈溢出风险。
Sphere welzl( vector<P3>& pts,int n,vector<P3>& R) {
    // 3D 最多 4 个边界点决定球
    if ( n == 0 ||(int)R.size() == 4 ) { return trivial_ball(R);}
    P3 p = pts[n - 1];
    // 先假设 p 不需要成为边界点
    Sphere s = welzl(pts,n - 1,R);
    if (inside(s, p)) return s;
    // p 在旧球外 => p 必须成为新最小球边界点
    R.push_back(p);
    Sphere ans = welzl(pts,n - 1,R);
    R.pop_back();
    return ans;
}
// 三维最小覆盖球
// 固定维度下期望 O(n)
// 注意 Welzl 是递归实现，递归深度 O(n)
Sphere mes( vector<P3> pts) {
    if (pts.empty()) return {{0, 0, 0}, 0};
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    shuffle(pts.begin(),pts.end(),rng);
    vector<P3> R; R.reserve(4);
    return welzl(pts,(int)pts.size(),R);
}
