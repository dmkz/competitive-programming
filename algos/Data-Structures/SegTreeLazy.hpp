#ifndef __SEGTREELAZY_HPP__
#define __SEGTREELAZY_HPP__
/*******************************************************************************************
 * The file "SegTreeLazy.hpp" is a part of competitive programming C++ library "algos".    *
 * You can find it here: https://github.com/dmkz/competitive-programming/tree/master/algos *
 *******************************************************************************************/
#include "SegTreeLazyTraits.hpp"
namespace algos {
namespace SegTreeLazy {
using namespace algos::SegTreeLazyTraits;
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
     *  Available traits, implemented below 
     ******************************************************************************/
    template<typename Value, typename Extra> using TraitsMinAdd = LazyMinAdd<Value,Extra>;
    template<typename Value, typename Extra> using TraitsMaxAdd = LazyMaxAdd<Value,Extra>;
    template<typename Value, typename Extra> using TraitsSumSet = LazySumSet<Value,Extra>;
    template<typename Value, typename Extra> using TraitsSumAdd = LazySumAdd<Value,Extra>;
    template<typename Value, typename Extra> using TraitsSumMul = LazySumMul<Value,Extra>;
    template<typename Value, typename Extra, auto Base>
    using TraitsGeomSumMul = LazyGeomSumMul<Value, Extra, Base>;
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
            
            bool hasExtra{};
            
            bool hasValue{};
            
            Node(Value value_ = Traits::valueNeutral(),
                 Extra extra_ = Traits::extraNeutral(),
                 bool hasExtra_ = false,
                 bool hasValue_ = false)
                : value(value_), extra(extra_), hasExtra(hasExtra_), hasValue(hasValue_) { }
            
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
            bool& hasExtra() { return node.hasExtra; }
            bool& hasValue() { return node.hasValue; }
            const Value& value() const { return node.value; }
            const Extra& extra() const { return node.extra; }
            const bool& hasExtra() const { return node.hasExtra; }
            const bool& hasValue() const { return node.hasValue; }
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
            data.assign(n == 0 ? 0 : 2 * n - 1, Node());
        }
        
        /*******************************************************************************
         *  Apply a lazy operation to a node
         ******************************************************************************/
        template<typename NodeDst, typename NodeSrc>
        static void apply(NodeDst dst, const NodeSrc& src) {
            Traits::push(dst, src);
            dst.hasExtra() = true;
        }
        
        /*******************************************************************************
         *  Lazy propagation from node to its children
         ******************************************************************************/
        void push(int v, int l, int r, int m) {
            if (data[v].hasExtra) {
                apply(
                    NodeWrapper<Node&>(l, m, data[v+1]),
                    NodeWrapper<const Node&>(l, r, data[v])
                );
                apply(
                    NodeWrapper<Node&>(m+1, r, data[v+2*(m-l+1)]),
                    NodeWrapper<const Node&>(l, r, data[v])
                );
                data[v].extra = Traits::extraNeutral();
                data[v].hasExtra = false;
            }
        }
        
        /*******************************************************************************
         *  Update node using children values
         ******************************************************************************/
        void pull(int v, int l, int r, int m) {
            assert(!data[v].hasExtra);
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
                data[v] = Node(arr[tl], Traits::extraNeutral(), false, true);
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
            if (n > 0)
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
                apply(
                    NodeWrapper<Node&>(tl, tr, data[v]),
                    NodeWrapper<Node>(ql, qr, Node(Traits::valueNeutral(), extra, true))
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
    
} // namespace SegTreeLazy
} // namespace algos
#endif // __SEGTREELAZY_HPP__