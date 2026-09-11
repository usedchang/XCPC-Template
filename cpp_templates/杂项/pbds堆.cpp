// pbds 堆（可并堆、可按句柄改/删）：pairing_heap_tag；用法见正文。
#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
using namespace __gnu_pbds;

// 容器标签：pairing_heap_tag（配对堆，最常用，支持 modify/erase）
//           binary_heap_tag、binomial_heap_tag、rc_binomial_heap_tag、thin_heap_tag
int main() {
    // 注意：std 和 __gnu_pbds 里都有 priority_queue，同时 using 两个命名空间时
    //       必须写全 __gnu_pbds::priority_queue，否则报 ambiguous
    __gnu_pbds::priority_queue<int, less<int>, pairing_heap_tag> pq, pq2;   // less = 大根堆
    pq.push(3);
    pq.push(1);
    pq.push(5);
    auto it = pq.push(4);              // push 返回迭代器（句柄），后面用它删除/修改
    cout << pq.top() << '\n';          // 5
    pq.modify(it, 9);                  // 把 4 改成 9（O(1) 摊还）
    cout << pq.top() << ' ' << pq.size() << '\n';   // 9 4
    pq.erase(it);                      // 按句柄删除
    cout << pq.size() << '\n';         // 3

    pq2.push(7);
    pq2.push(2);
    pq.join(pq2);                      // 合并两个堆（pq2 会被清空），O(1) 摊还
    cout << pq.size() << ' ' << pq2.size() << '\n'; // 5 0
    while (!pq.empty()) {              // 非清空式遍历也可以：for (auto x : pq)
        cout << pq.top() << ' ';
        pq.pop();
    }
    cout << '\n';                      // 7 5 3 2 1
    return 0;
}
