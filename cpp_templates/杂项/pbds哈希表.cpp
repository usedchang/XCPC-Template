// pbds 哈希表 gp_hash_table / cc_hash_table：用法见正文。
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// 防卡的自定义哈希：把 key 混入随机数再走 splitmix64
struct chash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int main() {
    // gp_hash_table<键, 值, 哈希>；第三个参数不写就是 default_hash<键>
    gp_hash_table<long long, int, chash> mp;
    mp[123] = 1;
    mp[456] = 2;
    cout << mp[123] + mp[456] << '\n';                 // 3
    cout << (mp.find(999) == mp.end()) << '\n';        // 1
    mp.erase(123);
    cout << mp.size() << '\n';                         // 1
    // 当作集合用：映射写成 null_type
    gp_hash_table<int, null_type, chash> st;
    st.insert(7);
    cout << (st.find(7) != st.end()) << '\n';          // 1
    // 多组数据复用：clear() 比重新构造快（内部容量会保留）
    mp.clear();
    cout << mp.size() << '\n';                         // 0
    // 说明：cc_hash_table<键, 值, 哈希> 是拉链法版本，用法完全一样；
    //       键是 string 这类非整数时，自定义哈希要按实际键类型写
    return 0;
}
