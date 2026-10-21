#include <bits/stdc++.h>
using namespace std;

// 返回 t 在 s 中所有 0 起始位置。
vector<int> kmp(string_view s, string_view t) {
    int n = s.size(), m = t.size();
    if (m == 0) {
        vector<int> ans(n + 1);
        iota(ans.begin(), ans.end(), 0);
        return ans;
    }

    vector<int> pi(m);
    for (int i = 1; i < m; ++i) {
        int j = pi[i - 1];
        while (j > 0 && t[i] != t[j]) {
            j = pi[j - 1];
        }
        if (t[i] == t[j]) {
            ++j;
        }
        pi[i] = j;
    }

    vector<int> ans;
    for (int i = 0, j = 0; i < n; ++i) {
        while (j > 0 && s[i] != t[j]) {
            j = pi[j - 1];
        }
        if (s[i] == t[j]) {
            ++j;
        }
        if (j == m) {
            ans.push_back(i - j + 1);
            j = pi[j - 1];
        }
    }
    return ans;
}
