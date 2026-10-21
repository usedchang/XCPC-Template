#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct SuffixAutomaton {
    struct State {
        array<int, 26> next;
        int link = -1;
        int len = 0;
        i64 occurrences = 0;

        State() {
            next.fill(-1);
        }
    };

    vector<State> states;
    int last;

    SuffixAutomaton() {
        states.emplace_back();
        last = 0;
    }

    void extend(char c) {
        int x = c - 'a';
        assert(0 <= x && x < 26);
        int cur = states.size();
        states.emplace_back();
        states[cur].len = states[last].len + 1;
        states[cur].occurrences = 1;

        int p = last;
        while (p != -1 && states[p].next[x] == -1) {
            states[p].next[x] = cur;
            p = states[p].link;
        }
        if (p == -1) {
            states[cur].link = 0;
        } else {
            int q = states[p].next[x];
            if (states[p].len + 1 == states[q].len) {
                states[cur].link = q;
            } else {
                int clone = states.size();
                State clone_state = states[q];
                states.push_back(clone_state);
                states[clone].len = states[p].len + 1;
                states[clone].occurrences = 0;
                while (p != -1 && states[p].next[x] == q) {
                    states[p].next[x] = clone;
                    p = states[p].link;
                }
                states[q].link = states[cur].link = clone;
            }
        }
        last = cur;
    }

    void build(string_view s) {
        states.clear();
        states.emplace_back();
        last = 0;
        for (char c : s) {
            extend(c);
        }
    }

    bool contains(string_view s) const {
        int v = 0;
        for (char c : s) {
            int x = c - 'a';
            if (x < 0 || x >= 26 || states[v].next[x] == -1) {
                return false;
            }
            v = states[v].next[x];
        }
        return true;
    }

    i64 distinct_substrings() const {
        i64 answer = 0;
        for (int v = 1; v < (int)states.size(); ++v) {
            answer += states[v].len - states[states[v].link].len;
        }
        return answer;
    }

    // Returns end-position counts for every state after suffix-link aggregation.
    vector<i64> occurrence_counts() const {
        vector<int> order(states.size());
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return states[a].len > states[b].len;
        });
        vector<i64> count(states.size());
        for (int v = 0; v < (int)states.size(); ++v) {
            count[v] = states[v].occurrences;
        }
        for (int v : order) {
            if (v != 0) {
                count[states[v].link] += count[v];
            }
        }
        return count;
    }
};
