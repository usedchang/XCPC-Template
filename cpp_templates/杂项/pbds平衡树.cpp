// pbds 名次树（tree + tree_order_statistics_node_update）：用法与可重集合技巧见正文。
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// tree<键, 映射, 比较器, 容器标签, 更新策略>
//   null_type            —— 当 set 用（不用映射）
//   rb_tree_tag          —— 红黑树（另有 splay_tree_tag / ov_tree_tag）
//   tree_order_statistics_node_update —— 提供 order_of_key / find_by_order
typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update> ordered_set;

int main() {
    ordered_set t;
    t.insert(3); t.insert(1); t.insert(4); t.insert(1);   // 等价于 set，重复插入无效
    // order_of_key(x)：严格小于 x 的元素个数（0-indexed 排名）
    cout << t.order_of_key(3) << '\n';                    // 1
    // find_by_order(k)：第 k 小（k 从 0 计数），越界返回 end()
    cout << *t.find_by_order(0) << '\n';                  // 1
    cout << *t.find_by_order(2) << '\n';                  // 4
    // 前驱后继：lower_bound(x) 是 >= x，upper_bound(x) 是 > x
    cout << *t.lower_bound(3) << ' ' << *t.upper_bound(3) << '\n';   // 3 4
    auto it = t.find_by_order(t.order_of_key(4));         // 4 的位置
    cout << *prev(it) << '\n';                            // 3（4 的前驱）
    t.erase(4);
    cout << (t.find(4) == t.end()) << '\n';               // 1
    cout << t.size() << '\n';                             // 2

    // 可重集合（multiset）：键改成 pair<值, 唯一编号> 保证键唯一；
    // 查询"值 <= x 的个数"用 order_of_key({x, 无穷大})，"值 >= x 的个数"用 size - order_of_key({x, 0})
    tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag,
         tree_order_statistics_node_update> ms;
    int id = 0;
    ms.insert({5, id++});
    ms.insert({5, id++});
    ms.insert({7, id++});
    cout << ms.order_of_key({5, INT_MAX}) << '\n';        // 2（值 <= 5 的个数）
    cout << ms.size() - ms.order_of_key({5, 0}) << '\n';  // 3（值 >= 5 的个数）
    return 0;
}
