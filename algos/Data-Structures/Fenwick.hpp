#ifndef __FENWICK_HPP__
#define __FENWICK_HPP__

template<typename T>
struct Fenwick {
    
    std::vector<T> data;
    
    Fenwick(int n = 0) { build(n); }
    
    Fenwick(const auto &a) { build(a); }
    
    void build(int n) { data.assign(n, T{}); }
    
    void build(const auto &a) {
        const int n = (int)std::size(a);
        build(n);
        for (int i = 0; i < n; i++)
            inc(i, a[i]);
    }

    // Sum on segment [0, r]:
    T sum(int r) const {
        assert(r < (int)data.size());
        T result = 0;
        for (; r >= 0; r = (r & (r+1)) - 1)
            result += data[r];
        return result;
    }
    T operator()(int r) const { return sum(r); }
    // Increase value on position `p` by delta:
    void inc(int p, T delta) {
        assert(p >= 0);
        for (; p < (int)data.size(); p = (p | (p+1)))
            data[p] += delta;
    }

    // Sum on segment [l, r]:
    T sum (int l, int r) const { return sum(r) - sum(l-1); }
    T operator()(int l, int r) const { return sum(l, r); }
    // Lower bound for sum `s`: sum[0]+...+sum[p-1] < s >= sum[0]+...+sum[p]
    template<typename cmp = std::less<T>>
    int binary_lifting(T s) const {
        int pos = 0;
        for (int p = std::__lg((int)data.size()); p >= 0; p--) {
            int next = pos + (1 << p) - 1;
            if (next < (int)data.size() && cmp()(data[next],s)) {
                s -= data[next];
                pos = next + 1;
            }
        }
        return pos;
    }
    
    int last_less_equal(T s) const {
        // returns index in a range [-1, n-1]
        // the result is equivalent to next binary search:
        // int low = -1, high = n;
        // while (high - low > 1) {
        //     int mid = (low + high) / 2;
        //     if (sum(0, mid) <= c) low = mid;
        //     else high = mid;
        // }
        // return low;
        //
        return binary_lifting<std::less_equal<T>>(s) - 1;
    }
    
    struct Reference
    {
        int index;
        Fenwick<T> &fenw;
        Reference &operator+=(T x) { return (fenw.inc(index, x),*this); }
        Reference &operator-=(T x) { return *this += (-x); }
        Reference &operator=(T x) { return *this += x-T(*this); }
        operator T() { return fenw(index,index); }
    };
    Reference operator[](int index) { return Reference{index, *this}; }
};
template<typename T>
struct FenwickSet : public Fenwick<T>
{
    FenwickSet(int n = 0) : Fenwick<T>(n) { }
    FenwickSet(const auto &a) : Fenwick<T>(a) { }
    // Works as same as find_by_order in OrderedSet
    int find_by_order(T order) const { return this->binary_lifting(order+1); }
    //int operator[](T order) const { return find_by_order(order); }
    // Works as same as order_of_key in OrderedSet
    T order_of_key(int key) const { return this->sum(key-1); }
    T count_less(int key) const { return this->sum(key-1); }
    T count_less_equal(int key) const { return this->sum(key); }
    T count_greater(int key) const { return this->sum(key+1, size()-1); }
    T count_equal(int key) const { return this->sum(key, key); }
    // Works as same as size in OrderedSet
    T size() const { return this->sum((int)this->data.size()-1); }
    // Works as same as insert/erase in OrderedSet
    void insert(int key, T delta = +1) { this->inc(key, delta); }
    void erase(int key, T delta = -1) { this->inc(key, delta); }
    // Works as same as npos in string
    int npos() const { return (int)this->data.size(); }
};
#endif // __FENWICK_HPP__