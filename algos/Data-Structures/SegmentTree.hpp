#ifndef __SEGMENTTREE_HPP__
#define __SEGMENTTREE_HPP__
namespace algos {
/**
 *  Efficient template SegmentTree<ItemType, ItemTraits> bottom-to-top implementation.
 *  ItemTraits should contain static functions `update`, `merge` and `neutral` (see examples below).
 *  Default Segment Tree is SegmentTree<int64_t, TraitsMinSet<int64_t>> with operations:
 *      1) min-query on segment `[l, r]` (zero-indexed)
 *      2) set-query on position `p` with value `x`
 */

namespace SegmentTree {
    /**
     * Traits for min on segment and set single element queries (by default)
     */
    template<typename T>
    struct TraitsMinSet {
        static T neutral() { return std::numeric_limits<T>::max(); }
        static void update(T& dst, T src) { dst = src; }
        static void merge(T& dst, const T& lhs, const T& rhs) { dst = std::min(lhs, rhs); }
    };
    
    /**
     *  List of additional traits, implemented below
     */
    template<typename T> struct TraitsMaxSet; // max on segment, set single element
    template<typename T> struct TraitsSumSet; // sum on segment, set single element
    template<typename T> struct TraitsMulSet; // mul on segment, set single element
    template<typename T> struct TraitsGCDSet; // gcd on segment, set single element
    template<typename T> struct TraitsMinAdd; // min on segment, add to single element
    template<typename T> struct TraitsMaxAdd; // max on segment, add to single element
    template<typename T> struct TraitsSumAdd; // sum on segment, add to single element
    template<typename T> struct TraitsGCDAdd; // gcd on segment, add to single element
    
    /**
     * SegmentTree class. Effective bottom-to-top implementation
     */
    template<typename ItemType = int64_t, typename ItemTraits = TraitsMinSet<ItemType>>
    struct SegmentTree {
        /**
         * Public data: `n` - number of items in array and `data` - tree's container
         */ 
        int n; std::vector<ItemType> data;

        /**
         * Main methods: resize(nItems), build(array), get(left, right), where 0 <= left <= right < nItems
         */ 
        void resize(const int n_){
            n = n_;
            int pow = 1;
            while (pow < n) { pow *= 2; }
            data.assign(2 * pow, ItemTraits::neutral());
        }
        
        template<typename T>
        void build(const std::vector<T>& arr) {
            resize((int)arr.size());
            for (int v = 0; v < n; ++v) {
                data[v + n] = arr[v]; 
            }
            for (int v = n-1; v >= 1; --v) {
                ItemTraits::merge(data[v], data[2*v], data[2*v+1]);
            }
        }
        
        ItemType get(int ql, int qr) const {
            ItemType ret = ItemTraits::neutral();
            for (ql += n, qr += n; ql <= qr; ql /= 2, qr /= 2) {
                if (ql % 2 == 1) { ItemTraits::merge(ret, ret, data[ql++]); }
                if (qr % 2 == 0) { ItemTraits::merge(ret, ret, data[qr--]); }
            }
            return ret;
        }
        
        void update(int pos, ItemType val) {
            int v = pos + n;
            ItemTraits::update(data[v], val);
            for (v /= 2; v > 0; v /= 2) {
                ItemTraits::merge(data[v], data[2*v], data[2*v+1]);
            }
        }
    }; /** SegmentTree class end */
    
    template<typename ItemType = int64_t, typename ItemTraits = TraitsMinSet<ItemType>>
    struct SegmentTreeRecursive {
        
        int n; std::vector<ItemType> data;

        /**
         * Main methods: resize(nItems), build(array), get(left, right), where 0 <= left <= right < nItems
         */ 
        void resize(const int n_){
            n = n_;
            int pow = 1;
            while (pow < n) { pow *= 2; }
            data.assign(2 * pow, ItemTraits::neutral());
        }
        
        template<typename T>
        void build(int v, int l, int r, const std::vector<T>& arr)
        {
            if (l+1==r) {
                data[v] = arr[l];
                return;
            }          
            int m = (l+r)/2;
            build(2*v+1,l,m,arr);
            build(2*v+2,m,r,arr);
            ItemTraits::merge(data[v], data[2*v+1], data[2*v+2]);
        }
        
        template<typename T>
        void build(const std::vector<T>& arr) {
            resize((int)arr.size());
            build(0,0,n,arr);
        }
        
        ItemType get(int v, int l, int r, int ql, int qr) const
        {
            if (qr <= l || r <= ql) return ItemTraits::neutral();
            if (ql <= l && r <= qr) return data[v];
            int m = (l+r)/2;
            auto left = get(2*v+1,l,m,ql,qr);
            auto right = get(2*v+2,m,r,ql,qr);
            auto res = ItemTraits::neutral();
            ItemTraits::merge(res, left, right);
            return res;
        }
        
        ItemType get(int ql, int qr) const
        {
            return get(0,0,n,ql,qr+1);
        }
        
        void update(int v, int l, int r, int pos, ItemType val) {
            if (pos < l || pos >= r) return;
            if (l+1==r) {
                data[v] = val;
                return;
            }
            int m = (l+r)/2;
            update(2*v+1,l,m,pos,val);
            update(2*v+2,m,r,pos,val);
            ItemTraits::merge(data[v],data[2*v+1],data[2*v+2]);
        }
        
        void update(int pos, ItemType val) {
            update(0,0,n,pos,val);
            
        }
    };
    
    /**
     * Traits for max on segment and set single element queries
     */
    template<typename T>
    struct TraitsMaxSet {
        static T neutral() { return std::numeric_limits<T>::min(); }
        static void update(T& dst, T src) { dst = src; }
        static void merge(T& dst, const T& lhs, const T& rhs) { dst = std::max(lhs, rhs); }
    };
    
    /**
     * Traits for sum on segment and set single element queries
     */
    template<typename T>
    struct TraitsSumSet {
        static T neutral() { return T{}; }
        static void update(T& dst, T src) { dst = src; }
        static void merge(T& dst, const T& lhs, const T& rhs) { dst = lhs + rhs; }
    };
    
    /**
     * Traits for mul on segment and set single element queries
     */
    template<typename T>
    struct TraitsMulSet {
        static T neutral() { return T{1}; }
        static void update(T& dst, T src) { dst = src; }
        static void merge(T& dst, const T& lhs, const T& rhs) { dst = lhs * rhs; }
    };
    
    /**
     * Traits for gcd on segment and set single element queries
     */
    template<typename T>
    struct TraitsGCDSet {
        static T neutral() { return T(0); }
        static void update(T& dst, T src) { dst = src; }
        static void merge(T& dst, const T& lhs, const T& rhs) { dst = std::__gcd(lhs, rhs); }
    };
    
    /**
     * Traits for min on segment and add to single element queries
     */
    template<typename T>
    struct TraitsMinAdd {
        static T neutral() { return std::numeric_limits<T>::max(); }
        static void update(T& dst, T src) { dst += src; }
        static void merge(T& dst, const T& lhs, const T& rhs) { dst = std::min(lhs, rhs); }
    };
    
    /**
     * Traits for max on segment and add to single element queries
     */
    template<typename T>
    struct TraitsMaxAdd {
        static T neutral() { return std::numeric_limits<T>::min(); }
        static void update(T& dst, T src) { dst += src; }
        static void merge(T& dst, const T& lhs, const T& rhs) { dst = std::max(lhs, rhs); }
    };
    
    /**
     * Traits for sum on segment and add to single element queries
     */
    template<typename T>
    struct TraitsSumAdd {
        static T neutral() { return T(0); }
        static void update(T& dst, T src) { dst += src; }
        static void merge(T& dst, const T& lhs, const T& rhs) { dst = lhs + rhs; }
    };

    /**
     * Traits for gcd on segment and add to single element queries
     */
    template<typename T>
    struct TraitsGCDAdd {
        static T neutral() { return T(0); }
        static void update(T& dst, T src) { dst += src; }
        static void merge(T& dst, const T& lhs, const T& rhs) { dst = std::__gcd(lhs, rhs); }
    };
    
} /** SegmentTree namespace end */
} // namespace algos
#endif // __SEGMENTTREE_HPP__