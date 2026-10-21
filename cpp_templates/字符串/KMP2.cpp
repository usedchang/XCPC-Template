#include <bits/stdc++.h>
using namespace std;

// Returns all 0-indexed starting positions of pattern in text.
vector<int> kmp_search(string_view text, string_view pattern) {
    if (pattern.empty()) {
        vector<int> positions(text.size() + 1);
        iota(positions.begin(), positions.end(), 0);
        return positions;
    }

    vector<int> pi(pattern.size());
    for (int i = 1; i < (int)pattern.size(); ++i) {
        int j = pi[i - 1];
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            ++j;
        }
        pi[i] = j;
    }

    vector<int> positions;
    for (int i = 0, j = 0; i < (int)text.size(); ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (text[i] == pattern[j]) {
            ++j;
        }
        if (j == (int)pattern.size()) {
            positions.push_back(i - j + 1);
            j = pi[j - 1];
        }
    }
    return positions;
}
