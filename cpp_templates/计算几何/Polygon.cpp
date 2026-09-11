using Poly=vector<P>;
P centroid(const Poly& p) {
    int n = (int)p.size();
    ld s = 0,sx = 0,sy = 0;
    for (int i = 0; i < n; ++i) {
        const P& a = p[i];
        const P& b = p[(i + 1) % n];
        ld c = cross(a, b);
        s += c;
        sx += (a.x + b.x) * c;
        sy += (a.y + b.y) * c;
    }
    return {sx / (3 * s),sy / (3 * s)};
}//重心, requires area2(p) != 0
ld area2(const Poly& p) {
    ld s = 0;
    int n = (int)p.size();
    for (int i = 0; i < n; i++) s += cross(p[i], p[(i + 1) % n]);
    return s;
}// 有向面积 * 2,CCW > 0, CW < 0
ld area(const Poly& p) {
    return fabsl(area2(p)) / 2;
}
ld peri(const Poly& p) {
    ld ans = 0;
    int n = (int)p.size();
    for (int i = 0; i < n; ++i) ans += dist(p[i], p[(i + 1) % n]);
    return ans;
}
enum PointPolygonRelation {
    POLY_OUT = -1,
    POLY_ON  = 0,
    POLY_IN  = 1
};
int inPoly(const Poly& poly, P p) {
    int n = (int)poly.size();
    int winding = 0;
    for (int i = 0; i < n; ++i) {
        P a = poly[i];
        P b = poly[(i + 1) % n];
        if (onS(p, a, b)) return POLY_ON;
        int s = ori(a, b, p);
        if (a.y <= p.y) {
            if (b.y > p.y && s > 0) ++winding;
        } else {
            if (b.y <= p.y && s < 0) --winding;
        }
    }
    return winding == 0 ? POLY_OUT : POLY_IN;
}// 简单多边形，CW / CCW 均可
