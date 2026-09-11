#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld EPS = 1e-12L;
const ld INF = 1e100L;
const ld PI = acosl(-1.0L);
bool eq(ld a, ld b) {
    return fabsl(a - b) <= EPS;
}
int sgn(ld x) {
    if (x > EPS) return 1;
    if (x < -EPS) return -1;
    return 0;
}
