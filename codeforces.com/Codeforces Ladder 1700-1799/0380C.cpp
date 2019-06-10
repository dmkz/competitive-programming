/*
    Problem: 380C. Sereja and Brackets
    
    Solution: segment tree, divide and conquer, bracket sequence, O(n + q * log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
struct Node {
    int freeOpened, freeClosed, answ;
    Node(int fo_ = 0, int fc_ = 0, int answ_ = 0)
        : freeOpened(fo_), freeClosed(fc_), answ(answ_){}
};
Node combine(Node a, Node b) {
    int delta = std::min(a.freeOpened, b.freeClosed);
    return Node(
        a.freeOpened - delta + b.freeOpened,
        a.freeClosed + b.freeClosed - delta,
        a.answ + b.answ + 2 * delta
    );
}
struct SegTree {
    std::vector<Node> data;
    Node build(int v, int l, int r, const std::string& s) {
        if (l + 1 == r) {
            data[v].freeOpened += (s[l] == '(');
            data[v].freeClosed += (s[l] == ')');
            return data[v];
        }
        const int m = (l + r) / 2;
        return data[v] = combine(build(2*v+1,l,m,s),build(2*v+2,m,r,s));
    }
    Node get(int v, int tl, int tr, int ql, int qr) {
        if (qr <= tl || tr <= ql) return Node();
        if (ql <= tl && tr <= qr) return data[v];
        const int tm = (tl + tr) / 2;
        return combine(get(2*v+1,tl,tm,ql,qr),get(2*v+2,tm,tr,ql,qr));
    }
    SegTree(const std::string& s) {
        int pow = 1;
        while (pow < isz(s)) pow *= 2;
        data.resize(2*pow);
        build(0,0,isz(s),s);
    }
};
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (std::string s; std::cin >> s; ) {
        SegTree segtree(s);
        int q; std::cin >> q;
        while (q--) {
            int l, r; std::cin >> l >> r; l--;
            std::cout << segtree.get(0,0,isz(s),l,r).answ << "\n";
        }
    }
    return 0;
}