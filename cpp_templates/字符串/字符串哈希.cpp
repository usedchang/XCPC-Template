#include <bits/stdc++.h>
using namespace std;

struct HashValue {
    uint32_t first, second;

    bool operator==(const HashValue &other) const {
        return first == other.first && second == other.second;
    }
};

// Double polynomial hash for lowercase or arbitrary byte strings.
struct RollingHash {
    static constexpr uint32_t mod1 = 1'000'000'007;
    static constexpr uint32_t mod2 = 1'000'000'009;
    static constexpr uint32_t base1 = 911'382'323;
    static constexpr uint32_t base2 = 972'663'749;

    vector<uint32_t> power1, power2, prefix1, prefix2;

    explicit RollingHash(string_view s)
        : power1(s.size() + 1, 1), power2(s.size() + 1, 1),
          prefix1(s.size() + 1), prefix2(s.size() + 1) {
        for (int i = 0; i < (int)s.size(); ++i) {
            uint32_t c = (unsigned char)s[i] + 1;
            power1[i + 1] = (uint64_t)power1[i] * base1 % mod1;
            power2[i + 1] = (uint64_t)power2[i] * base2 % mod2;
            prefix1[i + 1] = ((uint64_t)prefix1[i] * base1 + c) % mod1;
            prefix2[i + 1] = ((uint64_t)prefix2[i] * base2 + c) % mod2;
        }
    }

    // Returns the hash of the half-open substring s[l..r).
    HashValue get(int l, int r) const {
        uint32_t x = (prefix1[r] + mod1 - (uint64_t)prefix1[l] * power1[r - l] % mod1) % mod1;
        uint32_t y = (prefix2[r] + mod2 - (uint64_t)prefix2[l] * power2[r - l] % mod2) % mod2;
        return {x, y};
    }
};
