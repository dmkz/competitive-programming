#ifndef __SEGTREELAZYTRAITS_HPP__
#define __SEGTREELAZYTRAITS_HPP__
/*******************************************************************************************
 * File "SegTreeLazyTraits.hpp" is a part of competitive programming C++ library "algos".  *
 * You can find it here: https://github.com/dmkz/competitive-programming/tree/master/algos *
 *******************************************************************************************/
namespace algos {
namespace SegTreeLazyTraits {
    /*******************************************************************************
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
    template<typename Value, typename Extra> struct LazyMinAdd;
    template<typename Value, typename Extra> struct LazyMaxAdd;
    template<typename Value, typename Extra> struct LazySumSet;
    template<typename Value, typename Extra> struct LazySumAdd;
    template<typename Value, typename Extra> struct LazySumMul;
    template<typename Value, typename Extra, auto Base> struct LazyGeomSumMul;
    
    /*******************************************************************************
     *  Traits for minimal value on segment. 
     *  Get-query:    get minimal value in segment [l, r]
     *  Update-query: add const to each value in segment [l, r]
     ******************************************************************************/
    template<typename Value, typename Extra>
    struct LazyMinAdd {
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
     *  Traits for maximal value on segment. 
     *  Get-query:    get maximal value in segment [l, r]
     *  Update-query: add const to each value in segment [l, r]
     ******************************************************************************/
    template<typename Value, typename Extra>
    struct LazyMaxAdd {
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
     *  Traits for sum of values on segment. 
     *  Get-query:    sum of values on segment [l, r]
     *  Update-query: set const to each value in segment [l, r]
     ******************************************************************************/
    template<typename Value, typename Extra>
    struct LazySumSet {
        // Definition of neutral element for `Value`:
        static Value valueNeutral() { return Value(0); }
        // The value is irrelevant while a node has no pending operation.
        static Extra extraNeutral() { return Extra(0); }
        // Definition of how should combine `Extra` with `Value`:
        template<typename Node>
        static Value getValue(const Node& src) {
            return src.hasExtra() ? src.extra() * src.len() : src.value();
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
     *  Traits for sum on segment with addition. 
     *  Get-query:    sum of values on segment [l, r]
     *  Update-query: add const to each value on segment [l, r]
     ******************************************************************************/
    template<typename Value, typename Extra>
    struct LazySumAdd {
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
    struct LazySumMul {
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
    
    /*******************************************************************************
     * Traits for a geometric progression sum on a segment.
     * Initial value at position i is Base^i.
     * Get-query:    sum of values on segment [l, r]
     * Update-query: multiply each value on segment [l, r] by a constant
     ******************************************************************************/
    template<typename Value, typename Extra, auto Base>
    struct LazyGeomSumMul {
        // Definition of neutral element for `Value`:
        static Value valueNeutral() { return Value(0); }
        // Definition of neutral element for `Extra`:
        static Extra extraNeutral() { return Extra(1); }
        // Definition of how should combine `Extra` with `Value`:
        template<typename Node>
        static Value getValue(const Node& src) {
            const auto value = src.hasValue()
                ? src.value()
                : geometricSum(Value(Base), src.len()) * binpow(Value(Base), src.left());
            return value * src.extra();
        }
        // Definition of how should combine `Value` with `Value` (children to root):
        template<typename NodeRoot, typename NodeLt, typename NodeRt>
        static void pull(NodeRoot root, const NodeLt& lt, const NodeRt& rt) {
            root.value() = getValue(lt) + getValue(rt);
            root.hasValue() = true;
        }
        // Definition of how should combine `Extra` with `Extra`:
        template<typename NodeDst, typename NodeSrc>
        static void push(NodeDst dst, const NodeSrc& src) {
            dst.extra() *= src.extra();
        }
    };
    
} // namespace SegTreeLazyTraits
} // namespace algos
#endif // __SEGTREELAZYTRAITS_HPP__