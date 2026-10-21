#include <bits/stdc++.h>
using namespace std;

struct Manacher {
    string s;
    vector<int> od, ev;

    explicit Manacher(string s) : s(move(s)), od(this->s.size()), ev(this->s.size()) {
        int n = this->s.size();
        for (int i = 0, l = 0, r = -1; i < n; ++i) {
            int k = (i > r ? 1 : min(od[l + r - i], r - i + 1));
            while (i - k >= 0 && i + k < n && this->s[i - k] == this->s[i + k]) {
                ++k;
            }
            od[i] = k;
            if (i + k - 1 > r) {
                l = i - k + 1;
                r = i + k - 1;
            }
        }
        for (int i = 0, l = 0, r = -1; i < n; ++i) {
            int k = (i > r ? 0 : min(ev[l + r - i + 1], r - i + 1));
            while (i - k - 1 >= 0 && i + k < n && this->s[i - k - 1] == this->s[i + k]) {
                ++k;
            }
            ev[i] = k;
            if (i + k - 1 > r) {
                l = i - k;
                r = i + k - 1;
            }
        }
    }

    int maxlen() const {
        int ans = 0;
        for (int x : od) {
            ans = max(ans, 2 * x - 1);
        }
        for (int x : ev) {
            ans = max(ans, 2 * x);
        }
        return ans;
    }

    // s[l..r) 是否回文
    bool check(int l, int r) const {
        int len = r - l;
        if (len <= 1) {
            return true;
        }
        if (len & 1) {
            return od[(l + r - 1) / 2] >= len / 2 + 1;
        }
        return ev[(l + r) / 2] >= len / 2;
    }
};
