#ifndef __DYNAMICLAZYSEGMENTTREE_HPP__
#define __DYNAMICLAZYSEGMENTTREE_HPP__
namespace algos {
namespace DynamicLazySegmentTree {
using namespace SegmentTreeLazyTraits;
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
     *  Available traits, implemented in header file SegmentTreeLazyTraits.hpp
     ******************************************************************************/
    template<typename Value, typename Extra> using TraitsMinAdd = LazyMinAdd<Value, Extra>;
    template<typename Value, typename Extra> using TraitsMaxAdd = LazyMaxAdd<Value, Extra>;
    template<typename Value, typename Extra> using TraitsSumSet = LazySumSet<Value, Extra>;
    template<typename Value, typename Extra> using TraitsSumMul = LazySumMul<Value, Extra>;
        
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
            
			int leftChild{};
			
            Node(Value value_ = Traits::valueNeutral(), Extra extra_ = Traits::extraNeutral())
                : value(value_), extra(extra_) { }
            
            Value getValue(ll l, ll r) const { return Traits::getValue(NodeWrapper<Node>(l, r, *this)); }
			
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
            ll l, r;
            NodeType node;
            NodeWrapper(ll l_, ll r_, NodeType node_)
                : l(l_), r(r_), node(node_) { }
            ll  left() const { return l; }
            ll right() const { return r; }
            ll   mid() const { return (l+r)/2; }
            ll   len() const { return r - l + 1; }
            Value& value() { return node.value; }
            Extra& extra() { return node.extra; }
            const Value& value() const { return node.value; }
            const Extra& extra() const { return node.extra; }
        };        
        
		/*******************************************************************************
         *  SegmentTree public data: n - number of items, data - vector for nodes
         ******************************************************************************/
        ll n; std::deque<Node> nodes{Node()};
        
        SegmentTree(ll n_ = 0) { resize(n_); }
        
		int newNode() {
			nodes.push_back(Node());
			return int(nodes.size())-1;
		}
		
        /*******************************************************************************
         *  Resize segment tree data to needed size
         ******************************************************************************/
        void resize(ll n_) { n = n_; }
        
        /*******************************************************************************
         *  Lazy propagation from node to its children
         ******************************************************************************/
        void push(Node *curr, ll l, ll r, ll m) {
            assert(curr);
			if (curr->extra != Traits::extraNeutral()) {
                Traits::push(
                    NodeWrapper<Node&>(l, m, *(curr->getLeftChild(this))), 
                    NodeWrapper<const Node&>(l, r, *(curr))
                );
                Traits::push(
                    NodeWrapper<Node&>(m+1, r, *(curr->getRightChild(this))),
                    NodeWrapper<const Node&>(l, r, *curr)
                );
                curr->extra = Traits::extraNeutral();
            }
        }
        
        /*******************************************************************************
         *  Update node using children values
         ******************************************************************************/
        void pull(Node *curr, ll l, ll r, ll m) {
            assert(curr);
			assert(curr->extra == Traits::extraNeutral());
            Traits::pull(
                NodeWrapper<Node&>(  l, r, *curr), 
                NodeWrapper<const Node&>(  l, m, *(curr->getLeftChild(this))), 
                NodeWrapper<const Node&>(m+1, r, *(curr->getRightChild(this)))
            );
        }
        
        /*******************************************************************************
         *  Get-query on range [ql, qr]
         ******************************************************************************/
        Node get(ll ql, ll qr, Node *curr, const ll tl, const ll tr) {
            if (ql == tl && qr == tr) {
                return *curr;
            } else {
                ll tm = (tl + tr) / 2;
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
        
        Value get(const ll ql, const ll qr) {
			return get(ql, qr, &nodes[0], 0, n-1).getValue(ql, qr);
		}
        
        /*******************************************************************************
         *  Update query on range [ql, qr] by extra
         ******************************************************************************/
        void update(const ll ql, const ll qr, const Extra& extra, Node *curr, const ll tl, const ll tr) {
            if (ql == tl && tr == qr) {
                Traits::push(
                    NodeWrapper<Node&>(tl, tr, *curr),
                    NodeWrapper<Node>(ql, qr, Node(Traits::valueNeutral(), extra))
                );
            } else {
                ll tm = (tl + tr) / 2;
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

        void update(const ll ql, const ll qr, const Extra& extra) {
            update(ql, qr, extra, &nodes[0], 0, n-1);
        }

    };
    
} // namespace DynamicLazySegmentTree
} // namespace algos
#endif // __DYNAMICLAZYSEGMENTTREE_HPP__