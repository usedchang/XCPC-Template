#include <bits/stdc++.h>
using namespace std;

struct HV {
    uint32_t x, y;

    bool operator==(const HV &o) const {
        return x == o.x && y == o.y;
    }
};

struct Hash {
    static constexpr uint32_t mod1 = 1'000'000'007;
    static constexpr uint32_t mod2 = 1'000'000'009;
    static constexpr uint32_t base1 = 911'382'323;
    static constexpr uint32_t base2 = 972'663'749;

    vector<uint32_t> p1, p2, h1, h2;

    explicit Hash(string_view s)
        : p1(s.size() + 1, 1), p2(s.size() + 1, 1),
          h1(s.size() + 1), h2(s.size() + 1) {
        for (int i = 0; i < (int)s.size(); ++i) {
            uint32_t c = (unsigned char)s[i] + 1;
            p1[i + 1] = (uint64_t)p1[i] * base1 % mod1;
            p2[i + 1] = (uint64_t)p2[i] * base2 % mod2;
            h1[i + 1] = ((uint64_t)h1[i] * base1 + c) % mod1;
            h2[i + 1] = ((uint64_t)h2[i] * base2 + c) % mod2;
        }
    }

    // 子串 s[l..r) 的哈希
    HV get(int l, int r) const {
        uint32_t x = (h1[r] + mod1 - (uint64_t)h1[l] * p1[r - l] % mod1) % mod1;
        uint32_t y = (h2[r] + mod2 - (uint64_t)h2[l] * p2[r - l] % mod2) % mod2;
        return {x, y};
    }
};
