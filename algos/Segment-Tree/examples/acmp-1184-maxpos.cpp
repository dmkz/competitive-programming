/**
 *  Given array `arr[N]` with integers -10^9 <= arr[i] <= 10^9
 *  Need to process M queries:
 *      'l r' means maximal item and its leftmost position on segment arr[l..r]
 */
 
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

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
        static T neutral() { return T(0); }
        static void update(T& dst, T src) { dst = src; }
        static void merge(T& dst, const T& lhs, const T& rhs) { dst = lhs + rhs; }
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

template<typename T>
struct MaxPos {
    T val; int pos;
    MaxPos(T val_ = std::numeric_limits<T>::min(), int pos_ = 0)
        : val(val_), pos(pos_) { }
};

template<typename T>
struct TraitsMaxPos {
    static T neutral() { return T(); }
    static void update(T& dst, T src) { dst = src; }
    static void merge(T& dst, const T& lhs, const T& rhs) {
        dst = (lhs.val > rhs.val || (lhs.val == rhs.val && lhs.pos < rhs.pos)) ? lhs : rhs;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cerr.tie(0); std::cout.tie(0);
    int n; std::cin >> n;
    std::vector<MaxPos<int>> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i].val;
        arr[i].pos = i;
    }
    SegmentTree::SegmentTree<MaxPos<int>, TraitsMaxPos<MaxPos<int>>> segtree;
    segtree.build(arr);
    int q; std::cin >> q;
    while (q--) {
        int fi, se;
        std::cin >> fi >> se;
        auto answ = segtree.get(fi-1,se-1);
        std::cout << answ.val << ' ' << answ.pos+1 << '\n';
    }
    return 0;
}