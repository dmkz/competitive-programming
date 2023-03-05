#ifndef __SEGMENTTREELAZY_HPP__
#define __SEGMENTTREELAZY_HPP__
namespace algos {
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
     *  Available traits, implemented below 
     ******************************************************************************/
    template<typename Value, typename Extra> struct TraitsMinAdd;
    template<typename Value, typename Extra> struct TraitsMaxAdd;
    template<typename Value, typename Extra> struct TraitsSumSet;
    template<typename Value, typename Extra> struct TraitsSumMul;
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
    
    /*******************************************************************************
     *  Traits for maximal value on segment. 
     *  Get-query:    sum of values on segment [l, r]
     *  Update-query: set const to each value in segment [l, r]
     ******************************************************************************/
    template<typename Value, typename Extra>
    struct TraitsSumSet {
        // Definition of neutral element for `Value`:
        static Value valueNeutral() { return Value(0); }
        // Definition of neutral element for `Extra`:
        static Extra extraNeutral() { return Extra(-1); }
        // Definition of how should combine `Extra` with `Value`:
        template<typename Node>
        static Value getValue(const Node& src) {
            return src.extra() == extraNeutral() ? src.value() : src.len() * src.extra();
        }
        // Definition of how should combine `Value` with `Value` (children to root):
        template<typename NodeRoot, typename NodeLt, typename NodeRt>
        static void pull(NodeRoot root, const NodeLt& lt, const NodeRt& rt) {
            root.value() = getValue(lt) + getValue(rt);
        }
        // Definition of how should combine `Extra` with `Extra`:
        template<typename NodeDst, typename NodeSrc>
        static void push(NodeDst dst, const NodeSrc& src) {
            dst.extra() = src.extra();
        }
    };
	
	/*******************************************************************************
     *  Traits for sum on segment. 
     *  Get-query:    sum of values on segment [l, r]
     *  Update-query: add const to each value on segment [l, r]
     ******************************************************************************/
    template<typename Value, typename Extra>
    struct TraitsSumAdd {
        // Definition of neutral element for `Value`:
        static Value valueNeutral() { return Value(0); }
        // Definition of neutral element for `Extra`:
        static Extra extraNeutral() { return Extra(0); }
        // Definition of how should combine `Extra` with `Value`:
        template<typename Node>
        static Value getValue(const Node& src) {
            return src.value() + src.extra() * src.len();
        }
        // Definition of how should combine `Value` with `Value` (children to root):
        template<typename NodeRoot, typename NodeLt, typename NodeRt>
        static void pull(NodeRoot root, const NodeLt& lt, const NodeRt& rt) {
            root.value() = getValue(lt) + getValue(rt);
        }
        // Definition of how should combine `Extra` with `Extra`:
        template<typename NodeDst, typename NodeSrc>
        static void push(NodeDst dst, const NodeSrc& src) {
            dst.extra() += src.extra();
        }
    };
	
	template<typename Value, typename Extra>
    struct TraitsSumMul {
        // Definition of neutral element for `Value`:
        static Value valueNeutral() { return Value(0); }
        // Definition of neutral element for `Extra`:
        static Extra extraNeutral() { return Extra(1); }
        // Definition of how should combine `Extra` with `Value`:
        template<typename Node>
        static Value getValue(const Node& src) {
			//auto kek = algos::numeric::binpow(src.extra(), src.len());
			//auto kok = (src.extra() ^ src.len());
			//assert(kek == kok);
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
} // namespace SegmentTreeLazy
} // namespace algos
#endif // __SEGMENTTREELAZY_HPP__