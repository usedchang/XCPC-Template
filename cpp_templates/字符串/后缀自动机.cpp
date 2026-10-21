#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct SAM {
    struct Node {
        array<int, 26> ch;
        int fail = -1;
        int len = 0;
        i64 cnt = 0;

        Node() {
            ch.fill(-1);
        }
    };

    vector<Node> tr;
    int last;

    SAM() {
        tr.emplace_back();
        last = 0;
    }

    void add(char c) {
        int x = c - 'a';
        assert(0 <= x && x < 26);
        int cur = tr.size();
        tr.emplace_back();
        tr[cur].len = tr[last].len + 1;
        tr[cur].cnt = 1;

        int p = last;
        while (p != -1 && tr[p].ch[x] == -1) {
            tr[p].ch[x] = cur;
            p = tr[p].fail;
        }
        if (p == -1) {
            tr[cur].fail = 0;
        } else {
            int q = tr[p].ch[x];
            if (tr[p].len + 1 == tr[q].len) {
                tr[cur].fail = q;
            } else {
                int clone = tr.size();
                tr.push_back(tr[q]);
                tr[clone].len = tr[p].len + 1;
                tr[clone].cnt = 0;
                while (p != -1 && tr[p].ch[x] == q) {
                    tr[p].ch[x] = clone;
                    p = tr[p].fail;
                }
                tr[q].fail = tr[cur].fail = clone;
            }
        }
        last = cur;
    }

    void build(string_view s) {
        tr.clear();
        tr.emplace_back();
        last = 0;
        for (char c : s) {
            add(c);
        }
    }

    bool find(string_view s) const {
        int u = 0;
        for (char c : s) {
            int x = c - 'a';
            if (x < 0 || x >= 26 || tr[u].ch[x] == -1) {
                return false;
            }
            u = tr[u].ch[x];
        }
        return true;
    }

    i64 distinct() const {
        i64 ans = 0;
        for (int i = 1; i < (int)tr.size(); ++i) {
            ans += tr[i].len - tr[tr[i].fail].len;
        }
        return ans;
    }

    // 沿 fail 边汇总每个状态的出现次数
    vector<i64> counts() const {
        vector<int> ord(tr.size());
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int a, int b) {
            return tr[a].len > tr[b].len;
        });
        vector<i64> cnt(tr.size());
        for (int i = 0; i < (int)tr.size(); ++i) {
            cnt[i] = tr[i].cnt;
        }
        for (int u : ord) {
            if (u != 0) {
                cnt[tr[u].fail] += cnt[u];
            }
        }
        return cnt;
    }
};
