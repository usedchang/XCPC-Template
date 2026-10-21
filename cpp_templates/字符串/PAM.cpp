#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct PalindromicTree {
    struct Node {
        int len = 0;
        int link = 0;
        int suffix_count = 0;
        i64 occurrences = 0;
        array<int, 26> next;

        Node() {
            next.fill(-1);
        }
    };

    vector<Node> nodes;
    string text;
    int last;

    PalindromicTree() {
        nodes.resize(2);
        nodes[0].len = -1;  // Odd root.
        nodes[0].link = 0;
        nodes[1].len = 0;   // Even root.
        nodes[1].link = 0;
        last = 1;
    }

    int get_link(int v, int pos, char c) const {
        while (pos - 1 - nodes[v].len < 0 || text[pos - 1 - nodes[v].len] != c) {
            v = nodes[v].link;
        }
        return v;
    }

    // Adds one lowercase character and returns the number of palindromic suffixes.
    int add(char c) {
        int x = c - 'a';
        assert(0 <= x && x < 26);
        text.push_back(c);
        int pos = (int)text.size() - 1;
        int p = get_link(last, pos, c);

        if (nodes[p].next[x] == -1) {
            int cur = nodes.size();
            nodes.emplace_back();
            nodes[cur].len = nodes[p].len + 2;
            if (nodes[cur].len == 1) {
                nodes[cur].link = 1;
            } else {
                int q = get_link(nodes[p].link, pos, c);
                nodes[cur].link = nodes[q].next[x];
            }
            nodes[cur].suffix_count = 1 + nodes[nodes[cur].link].suffix_count;
            nodes[p].next[x] = cur;
        }

        last = nodes[p].next[x];
        ++nodes[last].occurrences;
        return nodes[last].suffix_count;
    }

    int distinct_count() const {
        return (int)nodes.size() - 2;
    }

    // Returns occurrence counts for nodes 0..nodes.size()-1; roots have count 0.
    vector<i64> occurrence_counts() const {
        vector<int> order(nodes.size());
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return nodes[a].len > nodes[b].len;
        });
        vector<i64> count(nodes.size());
        for (int v = 0; v < (int)nodes.size(); ++v) {
            count[v] = nodes[v].occurrences;
        }
        for (int v : order) {
            if (v >= 2) {
                count[nodes[v].link] += count[v];
            }
        }
        return count;
    }
};
