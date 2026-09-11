using VP=vector<P>;
struct Circle {
    P o;
    ld r = -1;    // r < 0 表示无效圆
};
bool inside(const Circle& c, P p) {
    if (c.r < 0) return false;
    return dist(c.o, p) <= c.r + EPS;
}// 点是否在圆内 / 圆周
Circle diameter(P a, P b) {
    P o = (a + b) / 2;
    return { o,dist(a, b) / 2};
}// 两点作为直径
Circle circle3(P a, P b, P c) {
    P u = b - a,v = c - a;
    ld cr = cross(u, v);
    ld mx = max({ dist(a, b),dist(a, c),dist(b, c)});// 最大边长
    if (mx <= EPS) return {{0, 0}, -1};
    // 2S / max_edge 本质上是对应高度
    if (fabsl(cr) <= EPS * mx) return {{0, 0}, -1};// 高度 <= EPS，视为退化
    P o = circumcenter(a, b, c);
    return {o, dist(o, a)};
}
ld dPC(P p,const Circle& c){
    return fabsl(dist(p,c.o)-c.r);
}
VP tangents(P p,const Circle& c){
    P v=p-c.o;
    ld d2=len2(v),r2=c.r*c.r;
    if(d2<r2-EPS) return {};
    if(fabsl(d2-r2)<=EPS) return {p};
    P q=c.o+v*(r2/d2);
    P h=rot90(v)*(c.r*sqrtl(d2-r2)/d2);
    return {q+h,q-h};
}//点到圆的两个切点

Circle mec_two_points(const VP& pts,int lim,P p,P q) {
    Circle base = diameter(p, q);
    Circle left{{0, 0}, -1};
    Circle right{{0, 0}, -1};
    P pq = q - p;
    for (int i = 0; i < lim; ++i) {
        P r = pts[i];
        if (inside(base, r)) continue;
        ld side = cross(pq, r - p);
        Circle c = circle3(p, q, r);
        if (c.r < 0) continue;
        ld center_side = cross(pq, c.o - p);
        if (side > 0) {
            if (left.r < 0 ||center_side >cross(pq, left.o - p))  left = c;
        } else if (side < 0) {
            if (right.r < 0 ||center_side <cross(pq, right.o - p)) right = c;
        }
    }
    if (left.r < 0 && right.r < 0) return base;
    if (left.r < 0) return right;
    if (right.r < 0) return left;
    return left.r <= right.r? left: right;
}
// 最小覆盖圆
// 返回圆心 + 半径
// 随机增量
// 期望 O(n)
Circle mec(VP pts) {
    if (pts.empty()) return {{0, 0}, 0};
    static mt19937_64 rng( chrono::steady_clock::now().time_since_epoch().count());
    shuffle(pts.begin(), pts.end(), rng);
    Circle c{{0, 0}, -1};
    for (int i = 0; i < (int)pts.size(); ++i) {
        if (inside(c, pts[i])) continue;
        c = {pts[i], 0};
        for (int j = 0; j < i; ++j) {
            if (inside(c, pts[j])) continue;
            c = mec_two_points(pts, j, pts[i], pts[j]);
        }
    }
    return c;
}
// 返回 0 / 1 / 2 个交点
VP interLC( const L& l,const Circle& c) {
    VP res;
    if (!valid(l) || c.r < 0) return res;
    P h = proj(c.o, l);
    ld d = dist(h, c.o);
    if (d > c.r + EPS) return res;
    if (fabsl(d - c.r) <= EPS) {
        res.push_back(h);
        return res;
    }
    ld len = sqrtl(max((ld)0, c.r * c.r - d * d));
    P e = unit(l.v);
    res.push_back(h + e * len);
    res.push_back(h - e * len);
    return res;
}
int interCC(const Circle& a,const Circle& b,VP& res) {
    res.clear();
    if (a.r < 0 || b.r < 0) return 0;
    ld d = dist(a.o, b.o);// 同心
    if (d <= EPS) {
        if (fabsl(a.r - b.r) <= EPS) return -1; // 重合
        return 0;
    }
    ld sum = a.r + b.r;
    ld dif = fabsl(a.r - b.r);
    if (d > sum + EPS) return 0; // 相离
    if (d < dif - EPS) return 0; // 内含
    P e = (b.o - a.o) / d;
    ld x = (a.r * a.r - b.r * b.r + d * d)/ (2 * d);
    P base = a.o + e * x;
    ld h2 = a.r * a.r - x * x;
    ld h = sqrtl(max((ld)0, h2));
    if (h <= EPS) {
        res.push_back(base);
        return 1;
    }
    P off = rot90(e) * h;
    res.push_back(base + off);
    res.push_back(base - off);
    return 2;
}
