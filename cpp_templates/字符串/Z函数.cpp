#include <bits/stdc++.h>
using namespace std;

// z[i] is the LCP length of s and s.substr(i); z[0] is set to |s|.
vector<int> z_function(string_view s) {
    int n = s.size();
    vector<int> z(n);
    if (n == 0) {
        return z;
    }
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}
