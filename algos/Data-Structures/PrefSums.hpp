#ifndef __PREFSUMS_HPP__
#define __PREFSUMS_HPP__
namespace algos {
namespace prefsums {
template<typename T>
struct PrefSums {
    std::vector<T> pref;
    PrefSums(const auto &a) {
        pref = {0};
        for (auto it : a)
            pref.push_back(pref.back() + it);
    }
    T operator()(int l, int r) const {
        return l > r ? 0 : pref[r+1] - pref[l];
    }
};
template<typename T>
struct PrefIncs {
    std::vector<T> data;
    PrefIncs(int n) : data(n+1, T{}) { }
    void inc(int l, int r, T x) {
        data[l] += x;
        data[r+1] -= x;
    }
    void build() {
        for (int i = 1; i < (int)data.size(); i++)
            data[i] += data[i-1];
    }
    T operator[](int i) const { return data[i]; }
};
} // namespace prefsums
} // namespace algos
#endif // __PREFSUMS_HPP__