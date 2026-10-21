#include <bits/stdc++.h>
using namespace std;

struct Manacher {
    string s;
    vector<int> odd, even;

    explicit Manacher(string s) : s(move(s)), odd(this->s.size()), even(this->s.size()) {
        int n = this->s.size();
        for (int i = 0, l = 0, r = -1; i < n; ++i) {
            int k = (i > r ? 1 : min(odd[l + r - i], r - i + 1));
            while (i - k >= 0 && i + k < n && this->s[i - k] == this->s[i + k]) {
                ++k;
            }
            odd[i] = k;
            if (i + k - 1 > r) {
                l = i - k + 1;
                r = i + k - 1;
            }
        }
        for (int i = 0, l = 0, r = -1; i < n; ++i) {
            int k = (i > r ? 0 : min(even[l + r - i + 1], r - i + 1));
            while (i - k - 1 >= 0 && i + k < n && this->s[i - k - 1] == this->s[i + k]) {
                ++k;
            }
            even[i] = k;
            if (i + k - 1 > r) {
                l = i - k;
                r = i + k - 1;
            }
        }
    }

    int longest_length() const {
        int ans = 0;
        for (int x : odd) {
            ans = max(ans, 2 * x - 1);
        }
        for (int x : even) {
            ans = max(ans, 2 * x);
        }
        return ans;
    }

    // Tests whether s[l..r) is a palindrome.
    bool is_palindrome(int l, int r) const {
        int len = r - l;
        if (len <= 1) {
            return true;
        }
        if (len & 1) {
            return odd[(l + r - 1) / 2] >= len / 2 + 1;
        }
        return even[(l + r) / 2] >= len / 2;
    }
};
