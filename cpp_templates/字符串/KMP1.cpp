#include <bits/stdc++.h>
using namespace std;

// pi[i] is the length of the longest proper prefix of s[0..i] that is also a suffix.
vector<int> prefix_function(string_view s) {
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
