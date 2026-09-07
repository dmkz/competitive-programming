#ifndef __SEGTREELAZYDYN_HPP__
#define __SEGTREELAZYDYN_HPP__
/*******************************************************************************************
 * The file "SegTreeLazyDyn.hpp" is a part of competitive programming C++ library "algos". *
 * You can find it here: https://github.com/dmkz/competitive-programming/tree/master/algos *
 *******************************************************************************************/
#include "SegTreeLazyTraits.hpp"
namespace algos {
namespace SegTreeLazyDyn {
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
     *  Available traits, implemented in header file SegTreeLazyTraits.hpp
     ******************************************************************************/
    template<typename Value, typename Extra> using TraitsMinAdd = LazyMinAdd<Value, Extra>;
    template<typename Value, typename Extra> using TraitsMaxAdd = LazyMaxAdd<Value, Extra>;
    template<typename Value, typename Extra> using TraitsSumSet = LazySumSet<Value, Extra>;
    template<typename Value, typename Extra> using TraitsSumAdd = LazySumAdd<Value, Extra>;
    template<typename Value, typename Extra> using TraitsSumMul = LazySumMul<Value, Extra>;
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
            
            int leftChild{};
            
            Node(Value value_ = Traits::valueNeutral(),
                 Extra extra_ = Traits::extraNeutral(),
                 bool hasExtra_ = false,
                 bool hasValue_ = false)
                : value(value_), extra(extra_), hasExtra(hasExtra_), hasValue(hasValue_) { }
            
            Value getValue(int64_t l, int64_t r) const { return Traits::getValue(NodeWrapper<Node>(l, r, *this)); }
            
            Node *getLeftChild(SegmentTree *owner) {
                if (!leftChild) {
                    leftChild = owner->newNode();
                    owner->newNode();
                }
                return &(owner->nodes[leftChild]);
            }
            
            Node *getRightChild(SegmentTree *owner) {
                if (!leftChild) {
                    leftChild = owner->newNode();
                    owner->newNode();
                }
                return &(owner->nodes[leftChild+1]);
            }
        };
        
        /*******************************************************************************
         *  NodeWrapper class
         ******************************************************************************/
        template<typename NodeType>
        struct NodeWrapper {
            int64_t l, r;
            NodeType node;
            NodeWrapper(int64_t l_, int64_t r_, NodeType node_)
                : l(l_), r(r_), node(node_) { }
            int64_t  left() const { return l; }
            int64_t right() const { return r; }
            int64_t   mid() const { return l + (r-l)/2; }
            int64_t   len() const { return r - l + 1; }
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
        int64_t n{}; std::deque<Node> nodes;
        
        SegmentTree(int64_t n_ = 0) { resize(n_); }
        
        int newNode() {
            nodes.push_back(Node());
            return int(nodes.size())-1;
        }
        
        /*******************************************************************************
         *  Resize segment tree data to needed size
         ******************************************************************************/
        void resize(int64_t n_) {
            n = n_;
            nodes.assign(1, Node());
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
        void push(Node *curr, int64_t l, int64_t r, int64_t m) {
            assert(curr);
            if (curr->hasExtra) {
                apply(
                    NodeWrapper<Node&>(l, m, *(curr->getLeftChild(this))),
                    NodeWrapper<const Node&>(l, r, *curr)
                );
                apply(
                    NodeWrapper<Node&>(m+1, r, *(curr->getRightChild(this))),
                    NodeWrapper<const Node&>(l, r, *curr)
                );
                curr->extra = Traits::extraNeutral();
                curr->hasExtra = false;
            }
        }
        
        /*******************************************************************************
         *  Update node using children values
         ******************************************************************************/
        void pull(Node *curr, int64_t l, int64_t r, int64_t m) {
            assert(curr);
            assert(!curr->hasExtra);
            Traits::pull(
                NodeWrapper<Node&>(  l, r, *curr), 
                NodeWrapper<const Node&>(  l, m, *(curr->getLeftChild(this))), 
                NodeWrapper<const Node&>(m+1, r, *(curr->getRightChild(this)))
            );
        }
        
        /*******************************************************************************
         *  Get-query on range [ql, qr]
         ******************************************************************************/
        Node get(int64_t ql, int64_t qr, Node *curr, const int64_t tl, const int64_t tr) {
            if (ql == tl && qr == tr) {
                return *curr;
            } else {
                int64_t tm = tl + (tr-tl)/2;
                push(curr, tl, tr, tm);
                Node ret;
                if (qr <= tm) {
                    ret = get(ql, qr, curr->getLeftChild(this),   tl, tm);
                } else if (ql > tm) {
                    ret = get(ql, qr, curr->getRightChild(this), tm+1, tr);
                } else {
                    const auto lt = get(  ql, tm, curr->getLeftChild(this),   tl, tm);
                    const auto rt = get(tm+1, qr, curr->getRightChild(this), tm+1, tr);
                    Traits::pull(
                        NodeWrapper<Node&>(  ql, qr, ret), 
                        NodeWrapper<const Node&>(  ql, tm, lt), 
                        NodeWrapper<const Node&>(tm+1, qr, rt)
                    );
                }
                pull(curr, tl, tr, tm);
                return ret;
            }
        }
        
        Value get(const int64_t ql, const int64_t qr) {
            return get(ql, qr, &nodes[0], 0, n-1).getValue(ql, qr);
        }
        
        /*******************************************************************************
         *  Update query on range [ql, qr] by extra
         ******************************************************************************/
        void update(const int64_t ql, const int64_t qr, const Extra& extra, Node *curr, const int64_t tl, const int64_t tr) {
            if (ql == tl && tr == qr) {
                apply(
                    NodeWrapper<Node&>(tl, tr, *curr),
                    NodeWrapper<Node>(ql, qr, Node(Traits::valueNeutral(), extra, true))
                );
            } else {
                int64_t tm = tl + (tr-tl)/2;
                push(curr, tl, tr, tm);
                if (qr <= tm) {
                    update(ql, qr, extra, curr->getLeftChild(this), tl, tm);
                } else if (ql > tm) {
                    update(ql, qr, extra, curr->getRightChild(this),tm+1,tr);
                } else {
                    update(ql, tm, extra, curr->getLeftChild(this),   tl, tm);
                    update(tm+1, qr, extra, curr->getRightChild(this), tm+1, tr);
                }
                pull(curr, tl, tr, tm);
            }
        }

        void update(const int64_t ql, const int64_t qr, const Extra& extra) {
            update(ql, qr, extra, &nodes[0], 0, n-1);
        }

    };
    
} // namespace SegTreeLazyDyn
} // namespace algos
#endif // __SEGTREELAZYDYN_HPP__