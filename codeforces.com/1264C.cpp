/*
    Problem: 1264C. Beautiful Mirrors
    Solution: probability theory, expected value, Segment Tree, math, O(n + q*log(n))
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
const auto io_sync_off = [](){std::ios_base::sync_with_stdio(0);std::cin.tie(0);return 0;}();
using ll = long long;
template<int mod>
struct IntMod {
    static int add(int a, int b) { return (a += b) >= mod ? a -= mod : a; }
    static int sub(int a, int b) { return (a -= b) < 0 ? a += mod : a; }
    int value;
    IntMod(ll value_ = 0)
    {
        if (value_ < 0) { value = int(mod - (-value_) % mod); }
        else if (value_ >= mod) { value = int(value_ % mod); }
        else { value = (int)value_; }
    }
    IntMod pow(ll n) const {
        if (n == 0) { return IntMod(1); }
        else if (n < 0) { return (IntMod(1) / *this).pow(-n); }
        if (value <= 1) { return *this; }
        IntMod r = 1, a = *this;
        while (n > 0) {
            if (n & 1) {
                r *= a;
            }
            a *= a;
            n >>= 1;
        }
        return r;
    }
    IntMod operator-() const { return IntMod(mod-value); }
    IntMod operator*(IntMod other) const { return IntMod(value * 1LL * other.value); }
    IntMod operator/(IntMod other) const { return *this * other.pow(mod-2); }
    IntMod operator+(IntMod other) const { return IntMod(add(value, other.value)); }
    IntMod operator-(IntMod other) const { return IntMod(sub(value, other.value)); }
    IntMod& operator*=(IntMod other) { return *this = *this * other; }
    IntMod& operator/=(IntMod other) { return *this = *this / other; }
    IntMod& operator+=(IntMod other) { return *this = *this + other; }
    IntMod& operator-=(IntMod other) { return *this = *this - other; }
    bool operator<(IntMod other) const { return value < other.value; }
};
template<int Mod> IntMod<Mod> pow(IntMod<Mod> v, ll n) { return v.pow(n); }
const int mod = 998244353;
using Int = IntMod<mod>;
template<typename T>
struct PrefixProduct {
    std::vector<T> data;
    template<typename T2>
    PrefixProduct(const std::vector<T2>& arr) {
        data.assign(isz(arr)+1, T(1));
        for (int i = 0; i < isz(arr); i++) {
            data[i+1] = data[i] * arr[i];
        }
    }
    T operator()(const int begin, const int after) const { return data[after] / data[begin]; }
};
template<typename T> bool operator>(const T& a, const T& b) { return b < a; }
template<typename T> bool operator>=(const T& a, const T& b) { return !(a < b); }
template<typename T> bool operator<=(const T& a, const T& b) { return !(a > b); }
template<typename T> bool operator!=(const T& a, const T& b) { return a < b || b < a; }
template<typename T> bool operator==(const T& a, const T& b) { return !(a != b); }

namespace SegmentTreeLazy {
    
    /*******************************************************************************
     *  SegmentTree<Value, Extra, Traits> - segment tree class with lazy propagation, 0-indexed
     *  Default operations: minimal value on segment and addition on segment for int64_t type
     *  Use Traits<Value,Extra> for definition of:
     *      1)  neutral element for `Value`;
     *      2)  neutral element for `Extra`;
     *      3)  how should combine `Extra` with `Value`;
     *      4)  how should combine `Value` with `Value` (children to root);
     *      5)  how should combine `Extra` with `Extra`;
     *  See examples below: TraitsMinAdd<Value, Extra>
     ******************************************************************************/
    
    /*******************************************************************************
     *  Traits for minimal value on segment. 
     *  Get-query:    get minimal value in segment [l, r]
     *  Update-query: add const to each value in segment [l, r]
     ******************************************************************************/
    template<typename Value, typename Extra>
    struct TraitsMinAdd {
        // Definition of neutral element for `Value`:
        static Value valueNeutral() { return std::numeric_limits<Value>::max(); }
        // Definition of neutral element for `Extra`:
        static Extra extraNeutral() { return Extra(0); }
        // Definition of how should combine `Extra` with `Value`:
        template<typename Node>
        static Value getValue(const Node& src) {
            return src.value() + src.extra();
        }
        // Definition of how should combine `Value` with `Value` (children to root):
        template<typename NodeRoot, typename NodeLt, typename NodeRt>
        static void pull(NodeRoot root, const NodeLt& lt, const NodeRt& rt) {
            root.value() = std::min(getValue(lt), getValue(rt));
        }
        // Definition of how should combine `Extra` with `Extra`:
        template<typename NodeDst, typename NodeSrc>
        static void push(NodeDst dst, const NodeSrc& src) {
            dst.extra() += src.extra();
        }
    };
    
    /*******************************************************************************
     *  Additional traits, implemented below 
     ******************************************************************************/
    template<typename Value, typename Extra>  struct TraitsMaxAdd;
    
    /*******************************************************************************
     *  SegmentTree, see description above
     ******************************************************************************/
    template<typename Value = int64_t, typename Extra = int64_t, typename Traits = TraitsMinAdd<Value, Extra> >
    struct SegmentTree {
        
        /*******************************************************************************
         *  Node class
         ******************************************************************************/
        struct Node {
            Value value;
            
            Extra extra;
            
            Node(Value value_ = Traits::valueNeutral(), Extra extra_ = Traits::extraNeutral())
                : value(value_), extra(extra_) { }
            
            Value getValue(int l, int r) const { return Traits::getValue(NodeWrapper<Node>(l, r, *this)); }
        };
        
        /*******************************************************************************
         *  NodeWrapper class
         ******************************************************************************/
        template<typename NodeType>
        struct NodeWrapper {
            int l, r;
            NodeType node;
            NodeWrapper(int l_, int r_, NodeType node_)
                : l(l_), r(r_), node(node_) { }
            int  left() const { return l; }
            int right() const { return r; }
            int   mid() const { return (l+r)/2; }
            int   len() const { return r - l + 1; }
            Value& value() { return node.value; }
            Extra& extra() { return node.extra; }
            const Value& value() const { return node.value; }
            const Extra& extra() const { return node.extra; }
        };
        
        /*******************************************************************************
         *  SegmentTree public data: n - number of items, data - vector for nodes
         ******************************************************************************/
        int n; std::vector<Node> data;
        
        
        /*******************************************************************************
         *  Resize segment tree data to needed size
         ******************************************************************************/
        void resize(int n_) {
            n = n_;
            data.assign(2 * n - 1, Node());
        }
        
        /*******************************************************************************
         *  Lazy propagation from node to its children
         ******************************************************************************/
        void push(int v, int l, int r, int m) {
            if (data[v].extra != Traits::extraNeutral()) {
                Traits::push(
                    NodeWrapper<Node&>(l, m, data[v+1]), 
                    NodeWrapper<const Node&>(l, r, data[v])
                );
                Traits::push(
                    NodeWrapper<Node&>(m+1, r, data[v+2*(m-l+1)]), 
                    NodeWrapper<const Node&>(  l, r, data[v])
                );
                data[v].extra = Traits::extraNeutral();
            }
        }
        
        /*******************************************************************************
         *  Update node using children values
         ******************************************************************************/
        void pull(int v, int l, int r, int m) {
            assert(data[v].extra == Traits::extraNeutral());
            Traits::pull(
                NodeWrapper<Node&>(  l, r, data[v]), 
                NodeWrapper<const Node&>(  l, m, data[v+1]), 
                NodeWrapper<const Node&>(m+1, r, data[v+2*(m-l+1)])
            );
        }
        
        /*******************************************************************************
         *  Build segtree from array with given values
         ******************************************************************************/
        template<typename T>
        void build(const std::vector<T>& arr, const int v, const int tl, const int tr) {
            if (tl == tr) {
                data[v] = Node(arr[tl]);
            } else {
                const int tm = (tl + tr) / 2;
                build(arr, v+1,   tl, tm);
                build(arr, v+2*(tm-tl+1), tm+1, tr);
                pull(v, tl, tr, tm);
            }
        }
        
        template<typename T>
        void build(const std::vector<T>& arr) { 
            resize((int)arr.size());
            build(arr, 0, 0, n-1);
        }

        /*******************************************************************************
         *  Get-query on range [ql, qr]
         ******************************************************************************/
        Node get(int ql, int qr, const int v, const int tl, const int tr) {
            if (ql == tl && qr == tr) {
                return data[v];
            } else {
                int tm = (tl + tr) / 2;
                push(v, tl, tr, tm);
                Node ret;
                if (qr <= tm) {
                    ret = get(ql, qr, v+1,   tl, tm);
                } else if (ql > tm) {
                    ret = get(ql, qr, v+2*(tm-tl+1), tm+1, tr);
                } else {
                    const auto lt = get(  ql, tm, v+1,   tl, tm);
                    const auto rt = get(tm+1, qr, v+2*(tm-tl+1), tm+1, tr);
                    Traits::pull(
                        NodeWrapper<Node&>(  ql, qr, ret), 
                        NodeWrapper<const Node&>(  ql, tm, lt), 
                        NodeWrapper<const Node&>(tm+1, qr, rt)
                    );
                }
                pull(v, tl, tr, tm);
                return ret;
            }
        }
        
        Value get(const int ql, const int qr) { return get(ql, qr, 0, 0, n-1).getValue(ql, qr); }
        
        /*******************************************************************************
         *  Update query on range [ql, qr] by extra
         ******************************************************************************/
        void update(const int ql, const int qr, const Extra& extra, const int v, const int tl, const int tr) {
            if (ql == tl && tr == qr) {
                Traits::push(
                    NodeWrapper<Node&>(tl, tr, data[v]),
                    NodeWrapper<Node>(ql, qr, Node(Traits::valueNeutral(), extra))
                );
            } else {
                int tm = (tl + tr) / 2;
                push(v, tl, tr, tm);
                if (qr <= tm) {
                    update(ql, qr, extra, v+1, tl, tm);
                } else if (ql > tm) {
                    update(ql, qr, extra, v+2*(tm-tl+1),tm+1,tr);
                } else {
                    update(ql, tm, extra, v+1,   tl, tm);
                    update(tm+1, qr, extra, v+2*(tm-tl+1), tm+1, tr);
                }
                pull(v, tl, tr, tm);
            }
        }

        void update(const int ql, const int qr, const Extra& extra) {
            update(ql, qr, extra, 0, 0, n-1); 
        }

    };
    
    /*******************************************************************************
     *  Traits for maximal value on segment. 
     *  Get-query:    get maximal value in segment [l, r]
     *  Update-query: add const to each value in segment [l, r]
     ******************************************************************************/
    template<typename Value, typename Extra>
    struct TraitsMaxAdd {
        // Definition of neutral element for `Value`:
        static Value valueNeutral() { return std::numeric_limits<Value>::min(); }
        // Definition of neutral element for `Extra`:
        static Extra extraNeutral() { return Extra(0); }
        // Definition of how should combine `Extra` with `Value`:
        template<typename Node>
        static Value getValue(const Node& src) {
            return src.value() + src.extra();
        }
        // Definition of how should combine `Value` with `Value` (children to root):
        template<typename NodeRoot, typename NodeLt, typename NodeRt>
        static void pull(NodeRoot root, const NodeLt& lt, const NodeRt& rt) {
            root.value() = std::max(getValue(lt), getValue(rt));
        }
        // Definition of how should combine `Extra` with `Extra`:
        template<typename NodeDst, typename NodeSrc>
        static void push(NodeDst dst, const NodeSrc& src) {
            dst.extra() += src.extra();
        }
    };   
}
template<typename Value, typename Extra>
struct TraitsSumMul {
    // Definition of neutral element for `Value`:
    static Value valueNeutral() { return Value(0); }
    // Definition of neutral element for `Extra`:
    static Extra extraNeutral() { return Extra(1); }
    // Definition of how should combine `Extra` with `Value`:
    template<typename Node>
    static Value getValue(const Node& src) {
        return src.value() * src.extra();
    }
    // Definition of how should combine `Value` with `Value` (children to root):
    template<typename NodeRoot, typename NodeLt, typename NodeRt>
    static void pull(NodeRoot root, const NodeLt& lt, const NodeRt& rt) {
        root.value() = getValue(lt) + getValue(rt);
    }
    // Definition of how should combine `Extra` with `Extra`:
    template<typename NodeDst, typename NodeSrc>
    static void push(NodeDst dst, const NodeSrc& src) {
        dst.extra() *= src.extra();
    }
};
using SegTree = SegmentTreeLazy::SegmentTree<Int, Int, TraitsSumMul<Int,Int>>;
int main() {
    for (int n, q; std::cin >> n >> q; ) {
        std::vector<Int> p(n);
        for (int i = 0, tmp; i < n; i++) {
            std::cin >> tmp;
            p[i] = Int(tmp) / 100;
        }
        PrefixProduct<Int> prod(p);
        std::vector<Int> temp(n);
        for (int i = 0; i < n; i++) {
            temp[i] = prod(0, i);
        }
        SegTree segtree;
        segtree.build(temp);
        std::set<int> mirrors;
        mirrors.insert(n);
        mirrors.insert(0);
        segtree.update(0,n-1,Int(1)/prod(0, n));
        while (q--) {
            int v; std::cin >> v; v--;
            auto it = mirrors.find(v);
            if (it == mirrors.end()) {
                auto curr = mirrors.insert(v).first;
                auto prev = std::prev(curr);
                auto next = std::next(curr);
                const auto rightProd = prod(*curr, *next);
                segtree.update(*prev,*curr-1,rightProd);
            } else {
                auto curr = it;
                auto prev = std::prev(curr);
                auto next = std::next(curr);
                const auto rightProd = prod(*curr, *next);
                segtree.update(*prev, *curr-1, Int(1)/rightProd);
                mirrors.erase(it);
            }
            std::cout << (segtree.get(0, n-1)).value << '\n';
        }
    }
    return 0;
}