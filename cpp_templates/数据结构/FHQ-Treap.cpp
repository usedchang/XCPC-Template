template <typename T>
struct FHQ_Treap {
    struct Node {
        T data;
        int l = 0, r = 0, sz = 1;
        unsigned rnd;
        bool rev = false;   // 翻转懒标记
    };
    std::vector<Node> t;   // 下标从1开始，0为空节点
    int root = 0;
    FHQ_Treap() {
        t.push_back(Node{});   // 占位0号
        t[0].sz = 0;
    }
    // 完全清空
    void clear() {
        t.clear();
        t.push_back(Node{});
        t[0].sz = 0;
        root = 0;
    }
    bool empty() const { return t[root].sz == 0; }
    int size() const { return t[root].sz; }
    void push(int u) {
        if (!u || !t[u].rev) return;
        swap(t[u].l, t[u].r);
        if (t[u].l) t[t[u].l].rev ^= 1;
        if (t[u].r) t[t[u].r].rev ^= 1;
        t[u].rev = false;
    }
    // 新建节点（随机优先级）
    int new_node(const T& val) {
        static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        t.push_back({val, 0, 0, 1, static_cast<unsigned>(rng())});
        return static_cast<int>(t.size()) - 1;
    }
    void pull(int u) {
        if (!u) return;
        t[u].sz = 1 + t[t[u].l].sz + t[t[u].r].sz;
        // 若T支持区间信息合并，可在此调用 t[u].data.pull(t[t[u].l].data, t[t[u].r].data);
    }
    // 按大小分裂：左树得到前k个元素，右树为剩余部分
    void split(int u, int k, int& L, int& R) {
        if (!u) { L = R = 0; return; }
        push(u);   // 关键！
        int left_sz = t[t[u].l].sz;
        if (k <= left_sz) {
            R = u;
            split(t[u].l, k, L, t[u].l);
        } else {
            L = u;
            split(t[u].r, k - left_sz - 1, t[u].r, R);
        }
        pull(u);
    }
    // 合并两棵树（L所有元素在R之前）
    int merge(int L, int R) {
        if (!L || !R) return L ? L : R;
        push(L);
        push(R);   // 关键！
        if (t[L].rnd < t[R].rnd) {
            t[L].r = merge(t[L].r, R);
            pull(L);
            return L;
        } else {
            t[R].l = merge(L, t[R].l);
            pull(R);
            return R;
        }
    }
    // ---------- 位置操作（1-indexed）----------
    // 在第pos个元素之后插入（pos = 0 表示头部，pos = size() 表示尾部）
    void insert(int pos, const T& val) {
        int L, R;
        split(root, pos, L, R);
        int u = new_node(val);
        root = merge(merge(L, u), R);
    }
    void reverse(int l, int r) {  // 翻转 [l, r] (1-indexed)
        //assert(1 <= l && l <= r && r <= size());
        int L, M, R;
        split(root, l - 1, L, M);
        split(M, r - l + 1, M, R);
        t[M].rev ^= 1;            // 打上翻转标记
        root = merge(merge(L, M), R);
    }
    // 删除第k个元素（1-indexed），返回被删除的值
    T erase(int k) {
        int L, M, R;
        split(root, k - 1, L, M);
        split(M, 1, M, R);
        T removed = t[M].data;
        root = merge(L, R);
        // 可选：回收节点 M （本例中忽略，vector不回收）
        return removed;
    }
    // 删除区间 [l, r]（1-indexed 闭区间）
    void erase_range(int l, int r) {
        int L, M, R;
        split(root, l - 1, L, M);
        split(M, r - l + 1, M, R);
        root = merge(L, R);
        // M 整棵子树被丢弃
    }
    // 查询第k个元素（1-indexed）
    T get_kth(int k)  {
        int u = root;
        while (u) {
            push(u);   // 关键！
            int left_sz = t[t[u].l].sz;
            if (k <= left_sz) {
                u = t[u].l;
            } else if (k == left_sz + 1) {
                return t[u].data;
            } else {
                k -= left_sz + 1;
                u = t[u].r;
            }
        }
        return T{}; // 不会到达
    }
    // 便捷访问（同 get_kth）
    T operator[](int k) { return get_kth(k); }
    // ---------- 构建操作 ----------
    // 线性时间构建（笛卡尔树）—— 输入序列的顺序即为最终中序顺序
    void build(const std::vector<T>& arr) {
        clear();                     // 清空原有树
        if (arr.empty()) return;
        std::vector<int> nodes;      // 存储每个节点在 t 中的下标
        nodes.reserve(arr.size());
        for (const auto& val : arr) {
            nodes.push_back(new_node(val));
        }
        // 单调栈维护右链，确保按随机优先级满足堆性质
        std::vector<int> St;
        for (int cur : nodes) {
            int last = 0;
            while (!St.empty() && t[St.back()].rnd > t[cur].rnd) {
                last = St.back();
                St.pop_back();
            }
            t[cur].l = last;               // 当前节点的左子 = 最后一个被弹出的节点
            if (!St.empty()) {
                t[St.back()].r = cur;   // 栈顶的右子指向当前节点
            }
            St.push_back(cur);
        }
        // 栈底即为根
        root = St.empty() ? 0 : St[0];
        // 后序遍历更新所有节点的 sz（因为只设置了左右关系，sz 仍为1）
        update_subtree_size(root);
    }
private:
    // 后序遍历更新子树大小
    void update_subtree_size(int u) {
        if (!u) return;
        update_subtree_size(t[u].l);
        update_subtree_size(t[u].r);
        pull(u);
    }
};
