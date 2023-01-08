#ifndef __BRUTE_HPP__
#define __BRUTE_HPP__

template<typename T>
struct BruteVector : public std::vector<T>
{
    
    const T min, max;
    
    BruteVector(int nItems, T min_, T max_)
        : std::vector<T>(nItems, min_), min(min_), max(max_)
    { }
    
    bool next() {
        for (int i = (int)(this->size())-1; i >= 0; i--) {
            if ((*this)[i] == max) {
                (*this)[i] = min;
            } else {
                (*this)[i]++;
                return true;
            }
        }
        return false;
    }
};

template<typename T>
struct BruteVectorFixedSum
{
    const int n;
    const T min, max, sum;
    
    std::vector<T> data;
    
    BruteVectorFixedSum(int n_, T min_, T max_, T sum_)
        : n(n_), min(min_), max(max_), sum(sum_), data(n, min)
    { }
    
    template<typename Func>
    void for_each(const Func & f, int p = 0, T s = 0)
    {
        if (p == n) {
            if (s == sum) {
                // обработать вектор
                f(data);
            }
            return;
        }
        for (T x = min; x <= max; x++) {
            data[p] = x;
            for_each(f, p+1, s + x);
        }
    }
    
};

template<typename T>
struct BruteDistinct : public std::vector<T>
{
    
    const T min, max;
    
    std::vector<bool> used;
    
    BruteDistinct(int nItems, T min_, T max_)
        : std::vector<T>(nItems, min_), min(min_), max(max_)
        , used(max-min+1, false)
    {
        for (int i = 0; i < nItems; i++) {
            (*this)[i] += i;
            used[(*this)[i]-min] = 1;
        }
        assert(this->back() <= max);
    }
    
    bool next() {
        // нужно найти самую правую позицию, которую можем увеличить
        for (int i = (int)(this->size())-1; i >= 0; i--) {
            int j = (*this)[i]-min+1;
            while (j < (int)used.size() && used[j]) j++;
            if (j == (int)used.size()) {
                // can't increase current item:
                used[(*this)[i]-min] = 0;
                continue;
            }
            // otherwise update current element:
            used[(*this)[i]-min]=0;
            (*this)[i] = j+min;
            used[j] = 1;
            // j - first non used
            j = 0;
            for (int k = i+1; k < (int)(this->size()); k++) {
                while (j < (int)used.size() && used[j]) j++;
                assert(j < (int)used.size());
                (*this)[k] = j+min;
                used[j] = 1;
                j++;
            }
            return true;
        }
        return false;
    }
};


#endif // __BRUTE_HPP__
