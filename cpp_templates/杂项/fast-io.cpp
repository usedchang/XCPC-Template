#include <bits/stdc++.h>
using namespace std;

// ====================== 通用快读（支持任意整数类型）======================
template<typename T>
inline T read() {
    T x = 0; int f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + (ch - '0'); ch = getchar(); }
    return x * f;
}

// ====================== 通用快写（支持任意整数类型）======================
template<typename T>
inline void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

// ====================== 使用示例 ======================
int main() {
    int a = read<int>();
    long long b = read<long long>();
    short c = read<short>();
    __int128 d = read<__int128>();   // 支持 __int128！

    write(a); putchar('\n');
    write(b); putchar(' ');
    write(c); putchar('\n');
    write(d); putchar('\n');         // __int128 直接输出完美
    return 0;
}
