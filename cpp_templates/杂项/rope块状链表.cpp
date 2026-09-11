// GNU 扩展 rope（块状链表 / 可持久化序列）：用法见正文。
#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;

int main() {
    rope<int> a, b;
    for (int i = 1; i <= 5; ++i) a.push_back(i);      // 1 2 3 4 5
    a.insert(1, 99);                                  // 在下标 1 前插入 -> 1 99 2 3 4 5
    a.erase(1, 1);                                    // 从下标 1 起删 1 个 -> 1 2 3 4 5
    rope<int> mid = a.substr(1, 3);                   // 取出 [1, 1+3) -> 2 3 4
    b = a;                                            // O(1) 复制，底层共享
    b.append(mid);                                    // 1 2 3 4 5 2 3 4
    cout << a.size() << ' ' << b.size() << '\n';      // 5 8
    for (int i = 0; i < (int)b.size(); ++i) cout << b[i] << " \n"[i + 1 == (int)b.size()];
    a += b;                                           // 拼接，a 变成 13 个元素
    cout << a.size() << '\n';                         // 13
    cout << a[0] << ' ' << a[12] << '\n';             // 1 4（随机下标访问是 O(log n)）

    // 字符序列同理：rope<char> s; 或直接写 crope
    crope s;
    s.push_back('a');
    s += "bc";
    s.insert(1, "XY");                                // a X Y b c
    cout << s.size() << ' ' << s[1] << s[2] << '\n';  // 5 XY
    return 0;
}
