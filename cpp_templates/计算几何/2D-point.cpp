struct P {
    ld x = 0, y = 0;
    P() = default;
    P(ld x, ld y) : x(x), y(y) {}
    P operator + (const P& p) const { return {x + p.x, y + p.y};}
    P operator - (const P& p) const { return {x - p.x, y - p.y};}
    P operator * (ld k) const { return {x * k, y * k};}
    P operator / (ld k) const {return {x / k, y / k};}
    P& operator += (const P& p) { x += p.x; y += p.y; return *this;}
    P& operator -= (const P& p) { x -= p.x; y -= p.y; return *this;}
};
P operator * (ld k, const P& p) { return p * k;}
ld dot(P a, P b) { return a.x * b.x + a.y * b.y;}// 点积
ld cross(P a, P b) { return a.x * b.y - a.y * b.x;}// 叉积
ld cross(P a, P b, P c) { return cross(b - a, c - a);}
ld len2(P a) { return dot(a,a);}
ld len(P a) { return sqrtl(len2(a));}
P unit(P a) {
    ld l = len(a);
    if (l <= EPS) return {0, 0};
    return a / l;
}
ld dist(P a, P b) { return len(a - b);}
P rot90(P a) { return {-a.y, a.x};}// 逆时针旋转 90°
ld deg2rad(ld deg) { return deg * PI / 180.0L;}
ld rad2deg(ld rad) { return rad * 180.0L / PI;}
P rot(P p, ld rad) {
    ld c = cosl(rad),s = sinl(rad);
    return { p.x * c - p.y * s,p.x * s + p.y * c};
}
ld angle(P a,P b){ return atan2l(fabsl(cross(a,b)),dot(a,b));}//向量夹角
P rotAt(P p, P center, ld rad) { return center + rot(p - center, rad);}//点绕点旋转
int ori(P a,P b,P c){ return sgn(cross(b-a,c-a));}
