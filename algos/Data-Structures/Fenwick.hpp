#ifndef __FENWICK_HPP__
#define __FENWICK_HPP__

template<typename T>
struct Fenwick {
    
    std::vector<T> data;
    
    Fenwick(int n = 0) : data(n, T{}) { }
    
    Fenwick(const auto &a) : Fenwick((int)std::size(a)) { build(a); }
    
    void build(const auto &a) {
        for (int i = 0; i < (int)std::size(a); i++)
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

    // Increase value on position `p` by delta:
    void inc(int p, T delta) {
        assert(p >= 0);
        for (; p < (int)data.size(); p = (p | (p+1)))
            data[p] += delta;
    }

    // Sum on segment [l, r]:
    T sum (int l, int r) const { return sum(r) - sum(l-1); }
    
    // Lower bound for sum `s`: sum[0]+...+sum[p-1] < s >= sum[0]+...+sum[p]
    int binary_lifting(T s) const {
        int pos = 0;
        for (int p = std::__lg((int)data.size()); p >= 0; p--) {
            int next = pos + (1 << p) - 1;
            if (next < (int)data.size() && data[next] < s) {
                s -= data[next];
                pos = next + 1;
            }
        }
        return pos;
    }
    
    // Works as same as find_by_order in OrderedSet
    int find_by_order(int order) const { return binary_lifting(order+1); }
    // Works as same as order_of_key in OrderedSet
    T order_of_key(int key) const { return sum(key-1); }
    T count_less(int key) const { return sum(key-1); }
    T count_less_equal(int key) const { return sum(key); }
    T count_greater(int key) const { return sum(key+1, size()-1); }
    T count_equal(int key) const { return sum(key, key); }
    // Works as same as size in OrderedSet
    T size() const { return sum((int)data.size()-1); }
    // Works as same as insert/erase in OrderedSet
    void insert(int key, T delta = +1) { inc(key, delta); }
    void erase(int key, T delta = -1) { inc(key, delta); }
    // Worsk as same as npos in string
    int npos() const { return (int)data.size(); }
};
#endif // __FENWICK_HPP__