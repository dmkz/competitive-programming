/*
    Problem: 1439. Battle with You-Know-Who
    
    Solution: Segment Tree, binary search, O((n+q)*log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>

struct Node {
    int sum, vl, vr;
    
    Node(int sum_ = 0, int vl_ = -1, int vr_ = -1) 
        : sum(sum_), vl(vl_), vr(vr_) 
    { }
};


struct SegmentTree {

    int left, right;

    std::vector<Node> data;
    
    SegmentTree(int left_, int right_, int x) : left(left_), right(right_) {
        data.push_back(Node(x * (right-left+1)));
    }
    
    int add(int nl, int nr, int x) {
        data.push_back(Node(x * (nr-nl+1)));
        return (int)data.size()-1;
    }
    
    void set(int v, int l, int r, int p, int x) {
        if (l == r) {
            data[v].sum = x;
        } else {
            int m = (l + r) / 2, vl = data[v].vl, vr = data[v].vr;
            if (vl == -1) { vl = add(  l, m, 1); data[v].vl = vl; }
            if (vr == -1) { vr = add(m+1, r, 1); data[v].vr = vr; }
            if (p <= m) {
                set(vl, l, m, p, x);
            } else {
                set(vr, m+1, r, p, x);
            }
            data[v].sum = data[vl].sum + data[vr].sum;
        }
    }
    
    void set(int p, int x) {
        set(0, left, right, p, x);
    }
    
    int get(int sum) {
        int v = 0, l = left, r = right;
        while (l != r) {
            int m = (l+r)/2, vl = data[v].vl, vr = data[v].vr;
            if (vl == -1) { vl = add(  l, m, 1); data[v].vl = vl; }
            if (vr == -1) { vr = add(m+1, r, 1); data[v].vr = vr; }            
            if (data[vl].sum < sum) {
                sum -= data[vl].sum;
                v = vr;
                l = m+1;
            } else {
                r = m;
                v = vl;
            }
        }
        return l;
    }
};

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    SegmentTree st(1, n+q, 1);
    while (q--) {
        char t; int p;
        scanf(" %c %d", &t, &p);
        if (t == 'L') {
            printf("%d\n", st.get(p));
        } else {
            st.set(st.get(p), 0);
        }
    }
    return 0;
}