#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>

struct Node {
    int min, max;
};

Node combine(const Node& a, const Node& b) {
    return Node{std::min(a.min, b.min), std::max(a.max, b.max)};
}

struct SegmentTree {
    int size;
    std::vector<Node> data;
    
    void build(int v, int l, int r, const std::vector<int>& arr) {
        if (l == r) {
            data[v] = Node{arr[l], arr[l]};
        } else {
            int m = (l + r) / 2;
            build(2*v+1,   l, m, arr);
            build(2*v+2, m+1, r, arr);
            data[v] = combine(data[2*v+1], data[2*v+2]);
        }
    }
    
    Node get(int v, int l, int r, int ql, int qr) const {
        if (l == ql && r == qr) {
            return data[v];
        } else {
            int m = (l + r) / 2;
            if (qr <= m) {
                return get(2*v+1,   l, m, ql, qr);
            } else if (ql > m) {
                return get(2*v+2, m+1, r, ql, qr);
            } else {
                return combine(
                    get(2*v+1,   l, m,  ql, m),
                    get(2*v+2, m+1, r, m+1, qr)
                );
            }
        }
    }
    
    Node get(int left, int right) const {
        return get(0, 0, size-1, left, right);
    }
    
    void inc(int v, int l, int r, int p) {
        if (l == r) {
            data[v].min++;
            data[v].max++;
        } else {
            int m = (l + r) / 2;
            if (p <= m) {
                inc(2*v+1,   l, m, p);
            } else {
                inc(2*v+2, m+1, r, p);
            }
            data[v] = combine(data[2*v+1], data[2*v+2]);
        }
    }
    
    void inc(int value) {
        inc(0, 0, size-1, value);
    }
    
    SegmentTree(const std::vector<int>& arr) {
        size = (int)arr.size();
        int pow = 1;
        while (pow < size) {
            pow *= 2;
        }
        data.resize(2 * pow);
        build(0, 0, size-1, arr);
    }
};

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    std::vector<int> count(1+n, 0);
    
    SegmentTree st(count);
    
    int answ = 0;
    
    for (int i = 0; i < n; ++i) {
        int value;
        scanf("%d", &value); 
        st.inc(value);
        count[value]++;
        if (value > 0) {
            auto res = st.get(0, value-1);
            if (res.min < count[value]-k) {
                break;
            }
        }
        if (value < n) {
            auto res = st.get(value+1, n);
            if (res.max-k > count[value]) {
                break;
            }
        }
        ++answ;
    }
    
    printf("%d", answ);
    
    return 0;
}