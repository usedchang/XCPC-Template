#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct PAM {
    struct Node {
        int len = 0;
        int fail = 0;
        int num = 0;       // 以该节点结尾的回文后缀个数
        i64 cnt = 0;       // 出现次数
        array<int, 26> ch;

        Node() {
            ch.fill(-1);
        }
    };

    vector<Node> tr;
    string s;
    int last;

    PAM() {
        tr.resize(2);
        tr[0].len = -1;    // 奇根
        tr[0].fail = 0;
        tr[1].len = 0;     // 偶根
        tr[1].fail = 0;
        last = 1;
    }

    int getfail(int u, int pos, char c) const {
        while (pos - 1 - tr[u].len < 0 || s[pos - 1 - tr[u].len] != c) {
            u = tr[u].fail;
        }
        return u;
    }

    // 加入一个小写字符，返回当前前缀的回文后缀个数
    int add(char c) {
        int x = c - 'a';
        assert(0 <= x && x < 26);
        s.push_back(c);
        int pos = (int)s.size() - 1;
        int p = getfail(last, pos, c);

        if (tr[p].ch[x] == -1) {
            int cur = tr.size();
            tr.emplace_back();
            tr[cur].len = tr[p].len + 2;
            if (tr[cur].len == 1) {
                tr[cur].fail = 1;
            } else {
                int q = getfail(tr[p].fail, pos, c);
                tr[cur].fail = tr[q].ch[x];
            }
            tr[cur].num = 1 + tr[tr[cur].fail].num;
            tr[p].ch[x] = cur;
        }

        last = tr[p].ch[x];
        ++tr[last].cnt;
        return tr[last].num;
    }

    int size() const {
        return (int)tr.size() - 2;
    }

    // 沿 fail 边汇总每个节点的出现次数；两个根的下标为 0/1
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
            if (u >= 2) {
                cnt[tr[u].fail] += cnt[u];
            }
        }
        return cnt;
    }
};
