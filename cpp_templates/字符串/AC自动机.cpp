#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

// Counts occurrences of every inserted lowercase pattern in a text.
struct AhoCorasick {
    static constexpr int alphabet = 26;

    struct Node {
        array<int, alphabet> next;
        int link = 0;

        Node() {
            next.fill(-1);
        }
    };

    vector<Node> nodes;
    vector<int> terminal;
    vector<int> order;
    bool built = false;

    AhoCorasick() : nodes(1) {}

    int add_pattern(string_view s) {
        if (built) {
            throw logic_error("add all patterns before build()");
        }
        if (s.empty()) {
            throw invalid_argument("patterns must be non-empty");
        }
        int v = 0;
        for (char c : s) {
            int x = c - 'a';
            assert(0 <= x && x < alphabet);
            int u = nodes[v].next[x];
            if (u == -1) {
                u = nodes.size();
                nodes[v].next[x] = u;
                nodes.emplace_back();
            }
            v = u;
        }
        terminal.push_back(v);
        return (int)terminal.size() - 1;
    }

    void build() {
        if (built) {
            return;
        }
        queue<int> q;
        order.clear();
        order.push_back(0);
        for (int c = 0; c < alphabet; ++c) {
            int u = nodes[0].next[c];
            if (u == -1) {
                nodes[0].next[c] = 0;
            } else {
                nodes[u].link = 0;
                q.push(u);
                order.push_back(u);
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int c = 0; c < alphabet; ++c) {
                int u = nodes[v].next[c];
                if (u == -1) {
                    nodes[v].next[c] = nodes[nodes[v].link].next[c];
                } else {
                    nodes[u].link = nodes[nodes[v].link].next[c];
                    q.push(u);
                    order.push_back(u);
                }
            }
        }
        built = true;
    }

    // Returns counts in the same order as calls to add_pattern().
    vector<i64> count_matches(string_view text) const {
        if (!built) {
            throw logic_error("call build() before count_matches()");
        }
        vector<i64> visits(nodes.size());
        int v = 0;
        for (char c : text) {
            int x = c - 'a';
            assert(0 <= x && x < alphabet);
            v = nodes[v].next[x];
            ++visits[v];
        }
        for (int i = (int)order.size() - 1; i > 0; --i) {
            int u = order[i];
            visits[nodes[u].link] += visits[u];
        }
        vector<i64> answer(terminal.size());
        for (int i = 0; i < (int)terminal.size(); ++i) {
            answer[i] = visits[terminal[i]];
        }
        return answer;
    }
};
