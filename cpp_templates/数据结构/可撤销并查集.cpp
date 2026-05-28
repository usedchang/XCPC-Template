struct DSU {
    vector<int> f, siz;
    struct Record {
        int smallRoot;
        int bigRoot;
        int oldSizeBig;
    };
    vector<Record> st;
    DSU() {}
    DSU(int n) {
        f.resize(n);
        siz.assign(n, 1);
        iota(f.begin(), f.end(), 0);
        st.clear();
    }
    int find(int x) const {
        while (f[x] != x) x = f[x];
        return x;
    }
    bool merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return false;
        if (siz[fx] > siz[fy]) swap(fx, fy);
        st.push_back({fx, fy, siz[fy]});
        f[fx] = fy;
        siz[fy] += siz[fx];
        return true;
    }
    void undo() {
        auto [small, big, oldSz] = st.back();
        st.pop_back();
        f[small] = small;
        siz[big] = oldSz;
    }
    size_t save() {
        return st.size();
    }
    void rollback(size_t checkpoint) {
        while (st.size() > checkpoint) undo();
    }
    int size(int x) {
        return siz[find(x)];
    }
};
