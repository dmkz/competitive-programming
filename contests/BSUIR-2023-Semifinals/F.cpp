#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma")
#include "template.hpp"
#include "numeric.hpp"
#include "segmenttreelazy.hpp"
using namespace algos::numeric;
const int mod = (int)1e9+7;
using Int = IntMod<mod>;
struct Vec2 {
    Int a{}, b{};
    Vec2 operator+(const Vec2& v) const {
        return {a + v.a, b + v.b};
    }
    bool operator==(const Vec2& v) const {
        return a == v.a && b == v.b;
    }
    bool operator!=(const Vec2& v) const {
        return !(*this == v);
    }
};
struct Mat22 {
    
    Int a{}, b{}, c{}, d{};
    
    Mat22 operator*(const Mat22 &m) const {
        return Mat22{a*m.a+b*m.c,a*m.b+b*m.d, 
                     c*m.a+d*m.c,c*m.b+d*m.d};
    }
    Mat22 operator+(const Mat22 &m) const {
        return Mat22{a + m.a, b + m.b,
                     c + m.c, d + m.d};
    }
    Vec2 operator*(const Vec2 & m) const {
        return Vec2{a*m.a+b*m.b,c*m.a+d*m.b};
    }
};
const int NMAX = 200200;
const std::vector<Mat22> powers = []() {
    std::vector<Mat22> res(NMAX+1);
    res[0] = Mat22{1,0,0,1};
    for (int i = 1; i <= NMAX; i++) {
        res[i] = Mat22{1,1,1,0} * res[i-1];
    }
    return res;
}();
const std::vector<Mat22> geom = [](){
    std::vector<Mat22> res(NMAX+1);
    for (int i = 1; i <= NMAX; i++) {
        res[i] = res[i-1] + powers[i-1];
    }
    return res;
}();
using namespace algos::SegmentTreeLazy;
struct TraitsSumAdd2 {
    // Definition of neutral element for `Value`:
    static Vec2 valueNeutral() { return Vec2{0,0}; }
    // Definition of neutral element for `Extra`:
    static Vec2 extraNeutral() { return Vec2{0,0}; }
    // Definition of how should combine `Extra` with `Value`:
    template<typename Node>
    static Vec2 getValue(const Node& src) {
        return src.value() + geom[src.len()] * src.extra();
    }
    // Definition of how should combine `Value` with `Value` (children to root):
    template<typename NodeRoot, typename NodeLt, typename NodeRt>
    static void pull(NodeRoot root, const NodeLt& lt, const NodeRt& rt) {
        root.value() = getValue(lt) + powers[lt.len()] * getValue(rt);
    }
    // Definition of how should combine `Extra` with `Extra`:
    template<typename NodeDst, typename NodeSrc>
    static void push(NodeDst dst, const NodeSrc& src) {
        dst.extra() = dst.extra() + src.extra();
    }
};
int main() {
    int n, q; std::cin >> n >> q;
    std::vector<Vec2> a(n);
    for (int i = 0; i < n; i++) {
        int x; std::cin >> x;
        a[i] = {x, 0};
    }
    SegmentTree<Vec2, Vec2, TraitsSumAdd2> segtree;
    segtree.build(a);
    while (q --> 0) {
        char c; std::cin >> c;
        if (c == '?') {
            int l, r; std::cin >> l >> r;
            l--,r--;
            std::cout << segtree.get(l,r).a << '\n';
        } else {
            assert(c == '+');
            int l, r, x; std::cin >> l >> r >> x;
            l--,r--;
            segtree.update(l,r,Vec2{x,0});
        }
    }
}
