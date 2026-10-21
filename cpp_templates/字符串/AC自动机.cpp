#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

// 多模式串匹配：统计每个模式串在文本中的出现次数。
struct AC {
    static constexpr int S = 26;

    struct Node {
        array<int, S> ch;
        int fail = 0;

        Node() {
            ch.fill(-1);
        }
    };

    vector<Node> tr;
    vector<int> ed, ord;
    bool ok = false;

    AC() : tr(1) {}

    int add(string_view s) {
        if (ok) {
            throw logic_error("add all patterns before build()");
        }
        if (s.empty()) {
            throw invalid_argument("patterns must be non-empty");
        }
        int u = 0;
        for (char c : s) {
            int x = c - 'a';
            assert(0 <= x && x < S);
            int v = tr[u].ch[x];
            if (v == -1) {
                v = tr.size();
                tr[u].ch[x] = v;
                tr.emplace_back();
            }
            u = v;
        }
        ed.push_back(u);
        return (int)ed.size() - 1;
    }

    void build() {
        if (ok) {
            return;
        }
        queue<int> q;
        ord.clear();
        ord.push_back(0);
        for (int c = 0; c < S; ++c) {
            int u = tr[0].ch[c];
            if (u == -1) {
                tr[0].ch[c] = 0;
            } else {
                tr[u].fail = 0;
                q.push(u);
                ord.push_back(u);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int c = 0; c < S; ++c) {
                int v = tr[u].ch[c];
                if (v == -1) {
                    tr[u].ch[c] = tr[tr[u].fail].ch[c];
                } else {
                    tr[v].fail = tr[tr[u].fail].ch[c];
                    q.push(v);
                    ord.push_back(v);
                }
            }
        }
        ok = true;
    }

    // 按 add 的顺序返回每个模式串的出现次数
    vector<i64> query(string_view s) const {
        if (!ok) {
            throw logic_error("call build() before query()");
        }
        vector<i64> cnt(tr.size());
        int u = 0;
        for (char c : s) {
            int x = c - 'a';
            assert(0 <= x && x < S);
            u = tr[u].ch[x];
            ++cnt[u];
        }
        for (int i = (int)ord.size() - 1; i > 0; --i) {
            int u = ord[i];
            cnt[tr[u].fail] += cnt[u];
        }
        vector<i64> ans(ed.size());
        for (int i = 0; i < (int)ed.size(); ++i) {
            ans[i] = cnt[ed[i]];
        }
        return ans;
    }
};
