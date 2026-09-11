struct P3 {
    ld x = 0, y = 0, z = 0;
    P3() = default;
    P3(ld x, ld y, ld z): x(x), y(y), z(z) {}
    P3 operator + (const P3& p) const { return { x + p.x, y + p.y,z + p.z};}
    P3 operator - (const P3& p) const { return { x - p.x, y - p.y,z - p.z};}
    P3 operator * (ld k) const { return { x * k, y * k,z * k};}
    P3 operator / (ld k) const { return { x / k, y / k, z / k};}
    P3& operator += (const P3& p) {
        x += p.x;
        y += p.y;
        z += p.z;
        return *this;
    }
};
P3 operator * (ld k, const P3& p) { return p * k; }
// -------------------- 3D 基础运算 --------------------
ld dot(P3 a, P3 b) { return a.x * b.x + a.y * b.y + a.z * b.z;}
// 3D 叉积返回向量
P3 cross(P3 a, P3 b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}
ld len2(P3 a) { return dot(a, a);}
ld len(P3 a) { return sqrtl(len2(a));}
P3 unit(P3 a) {
    ld l = len(a);
    if (l <= EPS) return {0, 0, 0};
    return a / l;
}
ld dist(P3 a, P3 b) { return len(a - b);}
P3 rotAxis(P3 v, P3 axis, ld rad) {
    ld l = len(axis);
    if (l <= EPS) return v;
    axis = axis / l;
    ld c = cosl(rad);
    ld s = sinl(rad);
    return v * c + cross(axis, v) * s + axis * dot(axis, v) * (1 - c);
}
