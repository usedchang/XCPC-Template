#include <bits/stdc++.h>
using namespace std;

// Returns suffix starts in lexicographical order, in O(n log n).
vector<int> suffix_array(string_view s) {
    int n = s.size();
    int m = n + 1;  // Include a unique sentinel smaller than every byte.
    vector<int> value(m), sa(m), cls(m);
    for (int i = 0; i < n; ++i) {
        value[i] = (unsigned char)s[i] + 1;
    }

    vector<int> count(max(m, 257));
    for (int x : value) {
        ++count[x];
    }
    for (int i = 1; i < (int)count.size(); ++i) {
        count[i] += count[i - 1];
    }
    for (int i = m - 1; i >= 0; --i) {
        sa[--count[value[i]]] = i;
    }

    int classes = 1;
    for (int i = 1; i < m; ++i) {
        if (value[sa[i]] != value[sa[i - 1]]) {
            ++classes;
        }
        cls[sa[i]] = classes - 1;
    }

    vector<int> shifted(m), next_cls(m);
    for (int len = 1; len < m; len <<= 1) {
        for (int i = 0; i < m; ++i) {
            shifted[i] = sa[i] - len;
            if (shifted[i] < 0) {
                shifted[i] += m;
            }
        }
        count.assign(classes, 0);
        for (int x : shifted) {
            ++count[cls[x]];
        }
        for (int i = 1; i < classes; ++i) {
            count[i] += count[i - 1];
        }
        for (int i = m - 1; i >= 0; --i) {
            sa[--count[cls[shifted[i]]]] = shifted[i];
        }

        next_cls[sa[0]] = 0;
        int next_classes = 1;
        for (int i = 1; i < m; ++i) {
            pair<int, int> cur = {cls[sa[i]], cls[(sa[i] + len) % m]};
            pair<int, int> prev = {cls[sa[i - 1]], cls[(sa[i - 1] + len) % m]};
            if (cur != prev) {
                ++next_classes;
            }
            next_cls[sa[i]] = next_classes - 1;
        }
        cls.swap(next_cls);
        classes = next_classes;
    }

    sa.erase(sa.begin());  // Remove the sentinel suffix.
    return sa;
}

// lcp[i] is LCP(suffix_array[i - 1], suffix_array[i]); lcp[0] is 0.
vector<int> lcp_array(string_view s, const vector<int> &sa) {
    int n = s.size();
    vector<int> rank(n), lcp(n);
    for (int i = 0; i < n; ++i) {
        rank[sa[i]] = i;
    }
    for (int i = 0, k = 0; i < n; ++i) {
        int r = rank[i];
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
