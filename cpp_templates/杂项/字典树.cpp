// 字典树：pbds PATRICIA trie（前缀搜索）与 std::map 动态开点两种写法；说明见正文。
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/trie_policy.hpp>
#include <map>
using namespace std;
using namespace __gnu_pbds;

// <键, 映射, 键访问特性, 容器标签, 更新策略>
typedef trie<string, null_type, trie_string_access_traits<>, pat_trie_tag,
             trie_prefix_search_node_update> Ptrie;

int main() {
    Ptrie t;
    t.insert("apple");
    t.insert("apply");
    t.insert("app");
    t.insert("banana");

    // 前缀搜索：遍历所有以 "app" 开头的键（按字典序）
    auto range = t.prefix_range("app");
    for (auto it = range.first; it != range.second; ++it) cout << *it << '\n';
    // app / apple / apply
    cout << t.size() << '\n';                          // 4
    cout << (t.find("banana") != t.end()) << '\n';     // 1
    t.erase("app");
    cout << t.size() << '\n';                          // 3

    // —— 字符集大 / 节点稀疏时：std::map 动态开点 trie（每个节点只存实际用到的边）
    //    比 26/62 叉定长数组省内存，代价是一次转移 O(log 字符集)
    vector<map<int, int>> nxt(1);                      // nxt[p][c] = 子节点编号
    vector<int> cnt(1, 0);                             // 经过该节点的串数
    auto insert = [&](const string& s) {
        int p = 0;
        for (char c : s) {
            if (!nxt[p].count(c)) {
                nxt.emplace_back();
                cnt.push_back(0);
                nxt[p][c] = (int)nxt.size() - 1;
            }
            p = nxt[p][c];
            ++cnt[p];
        }
    };
    insert("abc");
    insert("abd");
    insert("abc");
    // 查询：以 "ab" 为前缀的串有多少个
    int p = 0;
    for (char c : string("ab")) p = nxt[p].count(c) ? nxt[p][c] : -1;
    if (p < 0) p = 0;
    cout << cnt[p] << '\n';                            // 3
    return 0;
}
