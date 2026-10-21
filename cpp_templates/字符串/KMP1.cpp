#include <bits/stdc++.h>
using namespace std;

// pi[i] 是最长真前缀且同时是 s[0..i] 后缀的长度。
vector<int> Kmp(string_view s) {
    vector<int> pi(s.size());
    for (int i = 1; i < (int)s.size(); ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}
