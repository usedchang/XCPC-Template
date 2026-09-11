bool onS(P p, P a, P b) {
    if (dist(a, b) <= EPS) return dist(p, a) <= EPS;
    if (ori(a, b, p) != 0) return false;
    return p.x >= min(a.x, b.x) - EPS &&
           p.x <= max(a.x, b.x) + EPS &&
           p.y >= min(a.y, b.y) - EPS &&
           p.y <= max(a.y, b.y) + EPS;
}// 点在线段上，包含端点
bool properSS(P a, P b, P c, P d) {
    int s1 = ori(a, b, c);
    int s2 = ori(a, b, d);
    int s3 = ori(c, d, a);
    int s4 = ori(c, d, b);
    return s1 * s2 < 0 && s3 * s4 < 0;
}// 两线段严格相交：交点都不在端点
bool interSS(P a, P b, P c, P d) {
    if (properSS(a, b, c, d)) return true;
    if (onS(a, c, d)) return true;
    if (onS(b, c, d)) return true;
    if (onS(c, a, b)) return true;
    if (onS(d, a, b)) return true;
    return false;
}// 两线段是否相交：包含端点接触和共线重叠
ld dSS(P a, P b, P c, P d) {
    if (interSS(a, b, c, d)) return 0;
    return min({
        dPS(a, c, d),
        dPS(b, c, d),
        dPS(c, a, b),
        dPS(d, a, b)
    });
}
