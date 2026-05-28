#include <iostream>
#include <cctype>
using namespace std;

// 重载 >> 运算符
istream& operator>>(istream &is, __int128 &n) {
    n = 0;
    int f = 1;
    char ch = is.get();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = is.get();
    }
    while (isdigit(ch)) {
        n = n * 10 + (ch - '0');
        ch = is.get();
    }
    n *= f;
    return is;
}

// 重载 << 运算符
ostream& operator<<(ostream &os, __int128 n) {
    if (n < 0) {
        os << '-';
        n = -n;
    }
    if (n > 9) os << n / 10;
    os << (char)(n % 10 + '0');
    return os;
}

// 绝对值函数
__int128 abs128(__int128 x) {
    return x < 0 ? -x : x;
}

// 整数平方根（向下取整）
__int128 sqrt128(__int128 x) {
    if (x < 0) return -1;
    __int128 l = 0, r = 1;
    while (r <= x / r) r *= 2; // 避免溢出
    while (l < r) {
        __int128 mid = (l + r + 1) / 2;
        if (mid <= x / mid) l = mid;
        else r = mid - 1;
    }
    return l;
}

int main() {
    __int128 a, b;
    cin >> a >> b;
    cout << "a = " << a << ", b = " << b << endl;
    cout << "abs(a) = " << abs128(a) << endl;
    cout << "sqrt(b) = " << sqrt128(b) << endl;
    return 0;
}
