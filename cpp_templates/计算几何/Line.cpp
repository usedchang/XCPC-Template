struct L {
    P p,v;  // 直线上一点,方向向量
    L() = default;
};//直线,注意此为点+方向向量表示
L line(P a,P b){
    return {a,b-a};
}
L perpL(P p,const L& l) { return {p,rot90(l.v)}; }//过一点做已知直线垂线
bool valid(const L& l) {
    return len(l.v) > EPS;
}
bool parallel(const L& a, const L& b) {
    if (!valid(a) || !valid(b)) return false;
    ld scale = len(a.v) * len(b.v);
    return fabsl(cross(a.v, b.v)) <= EPS * scale;
}
bool perpendicular(const L& a, const L& b) {
    if (!valid(a) || !valid(b)) return false;
    ld scale = len(a.v) * len(b.v);
    return fabsl(dot(a.v, b.v)) <= EPS * scale;
}
bool interLL(const L& a, const L& b, P& res) {
    if (!valid(a) || !valid(b)) return false;
    ld d = cross(a.v, b.v);
    ld scale = len(a.v) * len(b.v);
    if (fabsl(d) <= EPS * scale) return false;
    ld t = cross(b.p - a.p, b.v) / d;
    res = a.p + a.v * t;
    return true;
}// false：非法直线 / 平行 / 重合
bool onL(P p, const L& l) {
    if (!valid(l))
        return dist(p, l.p) <= EPS;

    // |cross| / |v| = 点到直线距离
    return fabsl(cross(l.v, p - l.p)) <= EPS * len(l.v);
}
P proj(P p, const L& l) {
    ld vv = len2(l.v);
    if (vv <= EPS * EPS) return l.p;
    ld t = dot(p - l.p, l.v) / vv;
    return l.p + l.v * t;
}//点到直线垂足
P foot(P p, const L& l) {
    return proj(p, l);
}
P reflect(P p, const L& l) {
    P h = proj(p, l);
    return h * 2 - p;
}//点关于直线对称点
ld dPL(P p,const L& l) {
    ld d = len(l.v);
    if (d <= EPS) return dist(p, l.p);
    return fabsl( cross(l.v, p - l.p)) / d;
}//点到直线距离
P closeS(P p,P a,P b) {
    P v = b - a;
    ld vv = len2(v);
    if (vv <= EPS * EPS) return a;
    ld t = dot(p - a, v) / vv;
    t = max((ld)0, min((ld)1, t));
    return a + v * t;
}//点到线段的最近点
ld dPS(P p,P a,P b) {
    return dist(p,closeS(p, a, b));
}//点到线段距离
