// incenter: 要求三角形非退化
// circumcenter: 要求三点不共线
// orthocenter: 要求三点不共线
P centroid(P a, P b, P c) { return (a + b + c) / 3;}// 三角形重心
P incenter(P a, P b, P c) {
    ld A = dist(b, c); // a 的对边
    ld B = dist(c, a); // b 的对边
    ld C = dist(a, b); // c 的对边
    return (a * A + b * B + c * C)/ (A + B + C);
}// 三角形内心
P circumcenter(P a, P b, P c) {
    P u = b - a, v = c - a;
    ld d = 2 * cross(u, v);
    ld u2 = len2(u);
    ld v2 = len2(v);
    P q {(v.y * u2 - u.y * v2) / d,(u.x * v2 - v.x * u2) / d};
    return a + q;
}// 三角形外心
P orthocenter(P a, P b, P c) {
    P o = circumcenter(a, b, c);
    return a + b + c - o * 2;
}// 三角形垂心
ld area2(P a, P b, P c) {
    return fabsl(cross(a, b, c));
}
ld area(P a, P b, P c) {
    return area2(a, b, c) / 2;
}
// -1 外部，0 边界，1 内部
int inTri(P p, P a, P b, P c) {
    if (onS(p, a, b) ||onS(p, b, c) ||onS(p, c, a)) return 0;
    int s1 = ori(a, b, p);
    int s2 = ori(b, c, p);
    int s3 = ori(c, a, p);
    if ((s1 > 0 && s2 > 0 && s3 > 0) || (s1 < 0 && s2 < 0 && s3 < 0)) return 1;
    return -1;
}

