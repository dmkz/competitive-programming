/*
    Problem: 339D. Xenia and Bit Operations
    Solution: Segment Tree
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

struct Node {
    
    int value, level;
    
    Node(int v_ = 0, int l_ = 0) : value(v_), level(l_) { }
};

Node combine(const Node& a, const Node& b) {
    assert(a.level == b.level);
    return Node{a.level % 2 ? (a.value ^ b.value) : (a.value | b.value), a.level+1};
}

struct SegmentTree {

    int size;

    std::vector<Node> data;
    
    SegmentTree(const std::vector<int>& arr) {
        size = (int)arr.size();
        int pow = 1;
        while (pow < size) pow *= 2;
        data.resize(2 * pow);
        build(0, 0, size-1, arr);
    }
    
    void build(int v, int l, int r, const std::vector<int>& arr) {
        if (l == r) {
            data[v] = arr[l];
        } else {
            int m = (l + r) / 2;
            build(2*v+1,   l, m, arr);
            build(2*v+2, m+1, r, arr);
            data[v] = combine(data[2*v+1],data[2*v+2]);
        }
    }

    void set(int v, int l, int r, int p, int x) {
        if (l == r) {
            data[v] = x;
        } else {
            int m = (l + r) / 2;
            if (p <= m) {
                set(2*v+1,   l, m, p, x);
            } else {
                set(2*v+2, m+1, r, p, x);
            }
            data[v] = combine(data[2*v+1],data[2*v+2]);
        }
    }
    
    void set(int p, int x) {
        set(0, 0, size-1, p, x);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, m; std::cin >> n >> m;
    
    std::vector<int> arr(1 << n);
    for (auto& it : arr) std::cin >> it;
    
    SegmentTree st(arr);
    
    while (m--) {
        int p, x; std::cin >> p >> x; --p;
        st.set(p,x);
        std::cout << st.data[0].value << '\n';
    }
    return 0;
}