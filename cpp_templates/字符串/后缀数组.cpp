#include <bits/stdc++.h>
using namespace std;

// 返回后缀起点按字典序排列的数组，O(n log n)
vector<int> SA(string_view s) {
    int n = s.size();
    int m = n + 1;                 // 末尾补一个小于所有字符的哨兵
    vector<int> v(m), sa(m), c(m);
    for (int i = 0; i < n; ++i) {
        v[i] = (unsigned char)s[i] + 1;
    }

    vector<int> cnt(max(m, 257));
    for (int x : v) {
        ++cnt[x];
    }
    for (int i = 1; i < (int)cnt.size(); ++i) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = m - 1; i >= 0; --i) {
        sa[--cnt[v[i]]] = i;
    }

    int cc = 1;
    for (int i = 1; i < m; ++i) {
        if (v[sa[i]] != v[sa[i - 1]]) {
            ++cc;
        }
        c[sa[i]] = cc - 1;
    }

    vector<int> sh(m), nc(m);
    for (int len = 1; len < m; len <<= 1) {
        for (int i = 0; i < m; ++i) {
            sh[i] = sa[i] - len;
            if (sh[i] < 0) {
                sh[i] += m;
            }
        }
        cnt.assign(cc, 0);
        for (int x : sh) {
            ++cnt[c[x]];
        }
        for (int i = 1; i < cc; ++i) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = m - 1; i >= 0; --i) {
            sa[--cnt[c[sh[i]]]] = sh[i];
        }

        nc[sa[0]] = 0;
        int ncc = 1;
        for (int i = 1; i < m; ++i) {
            pair<int, int> a = {c[sa[i]], c[(sa[i] + len) % m]};
            pair<int, int> b = {c[sa[i - 1]], c[(sa[i - 1] + len) % m]};
            if (a != b) {
                ++ncc;
            }
            nc[sa[i]] = ncc - 1;
        }
        c.swap(nc);
        cc = ncc;
    }

    sa.erase(sa.begin());          // 去掉哨兵后缀
    return sa;
}

// lcp[i] = LCP(sa[i-1], sa[i])，lcp[0] = 0
vector<int> LCP(string_view s, const vector<int> &sa) {
    int n = s.size();
    vector<int> rk(n), lcp(n);
    for (int i = 0; i < n; ++i) {
        rk[sa[i]] = i;
    }
    for (int i = 0, k = 0; i < n; ++i) {
        int r = rk[i];
        if (r == 0) {
            k = 0;
            continue;
        }
        int j = sa[r - 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
            ++k;
        }
        lcp[r] = k;
        if (k > 0) {
            --k;
        }
    }
    return lcp;
}
