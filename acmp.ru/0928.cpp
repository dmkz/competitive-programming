/*
    Задача: 928. Березовая аллея
    
    Решение: Sqrt-декомпозиция, дерево отрезков, динамическое программирование, бинарный поиск, O(n*m*log(n+m)^2)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <limits>

/**
 * Traits for min-queries on ranges, modifications disabled
 */
template<typename T>
struct MinRangeTraits {
    static T merge(const T& lhs, const T& rhs) { return std::min(lhs, rhs); }
    static T neutral() { return std::numeric_limits<T>::max(); }
};

/**
 * SegmentTree class. Effective bottom-to-top implementation
 */
template<typename ItemType, typename ItemTraits = MinRangeTraits<ItemType>>
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
            data[v] = ItemTraits::merge(data[2*v], data[2*v+1]);
        }
    }
    
    ItemType get(int ql, int qr) const {
        ql += n, qr += n;
        ItemType ret = ItemTraits::neutral();
        while (ql <= qr) {
            if (ql % 2 == 1) { ret = ItemTraits::merge(ret, data[ql++]); }
            if (qr % 2 == 0) { ret = ItemTraits::merge(ret, data[qr--]); }
            ql /= 2; qr /= 2;
        }
        return ret;
    }
}; /** SegmentTree class end */

/**
 * SqrtDecomposition class
 */
template<typename ItemType, typename ItemTraits = MinRangeTraits<ItemType>>
struct SqrtDecomposition {
/**
 * Public data: `data` - original array, `group` - additional information per group, `gsize` - size of each group
 */
    int gsize;
    std::vector<ItemType> data, group;    
    
/**
 * Main methods: resize(nItems), build(array), get(left, right), where 0 <= left <= right < nItems
 */ 
    void resize(const int n) {
        gsize = std::max(1, (int)std::sqrt((double)(n) / 2));
        data.assign(n, ItemTraits::neutral());
        group.assign((n + gsize - 1) / gsize, ItemTraits::neutral());
    }
    
    template<typename T>
    void build(const std::vector<T>& arr) {
        resize((int)arr.size());
        for (int i = 0; i < (int)data.size(); ++i) {
            data[i] = arr[i];
        }
        for (int g = 0; g < (int)group.size(); ++g) {
            const int begin = g * gsize;
            const int after = std::min(begin + gsize, (int)data.size());
            for (int i = begin; i < after; ++i) {
                group[g] = ItemTraits::merge(group[g], data[i]);
            }
        }
    }
    
    ItemType get(const int l, const int r) const {
        const int gl = l / gsize;
        const int gr = r / gsize;
        ItemType result = ItemTraits::neutral();
        if (gl == gr) {
            for (int i = l; i <= r; ++i) {
                result = ItemTraits::merge(result, data[i]);
            }
        } else {
            for (int i = l; i < (gl+1) * gsize; ++i) {
                result = ItemTraits::merge(result, data[i]);
            }
            for (int g = gl+1; g < gr; ++g) {
                result = ItemTraits::merge(result, group[g]);
            }
            for (int i = gr * gsize; i <= r; ++i) {
                result = ItemTraits::merge(result, data[i]);
            }
        }
        return result;
    }
}; /** SqrtDecomposition class end */

/**
 * Solution of original problem
 */
template<typename RMQ>
int solve(const int mxLen, const int width, const std::vector<int>& a, const std::vector<int>& b) {
    const int n = (int)(a.size()), m = (int)(b.size());
    // i + j == const
    std::vector<RMQ> diag(n + m - 1);
    auto dist = [&](const int i, const int j) {
        return (double)std::sqrt(double(a[i] - b[j]) * (a[i] - b[j]) + (double)(width) * width);
    };
    std::vector<int> minOnDiag(n + m - 1, (int)1e9), maxOnDiag(n + m - 1, -(int)1e9);
    for (int d = 0; d < n + m - 1; ++d) {
        std::vector<double> arr;
        for (int i = 0; i <= d; ++i) {
            const int j = d - i;
            if (j < 0 || j >= m) { continue; }
            double p = dist(0,0) + (a[i] - a[0]) + (b[j] - b[0]) + dist(i, j);
            arr.push_back(p);
            minOnDiag[d] = std::min(i, minOnDiag[d]);
            maxOnDiag[d] = std::max(i, maxOnDiag[d]);
        }
        diag[d].resize((int)arr.size());
        diag[d].build(arr);
    }
    
    auto can = [&](const int count) {
        //return canSlow(count);
        bool ok = false;
        for (int d = count - 2; d < n + m - 1; ++d) {
            for (int i = 0; i < n; ++i) {
                const int j = d - count - i + 2;
                if (j < 0 || j >= m) { continue; }
                // (t-i+1)+(k-j+1) == count
                // t + k = count + i + j - 2
                // t = i --> k = count + j - 2
                // k = j --> t = count + i - 2
                // t + k == d
                // i <= t && t <= n-1
                // j <= k && k <= m-1
                
                // i <= t && t <= (n-1)
                // j <= (d-t) && (d-t) <= (m-1)
                
                // i <= t && t < n
                // t <= d - j && (d - m + 1) <= t
                
                int r = std::min(n-1, d - j);
                int l = std::max(i, d - m + 1);
                if (l > r) { continue; }
                assert(i <= l && l <= n-1);
                assert(i <= r && r <= n-1);
                assert(j <= (d-l) && (d-l) <= m-1);
                assert(j <= (d-r) && (d-r) <= m-1);
                assert(l >= minOnDiag[d]);
                assert(r <= maxOnDiag[d]);
                l -= minOnDiag[d];
                r -= minOnDiag[d];
                auto res = diag[d].get(l, r) - diag[i+j].get(i-minOnDiag[i+j], i-minOnDiag[i+j]) + 2 * dist(i,j);
                ok = ok || (res <= mxLen + 1e-5);
                if (ok) { return true; }
            }
        }
        return ok;
    };
    int low = 1, high = (int)(n + m + 1);
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (can(mid)) { low = mid; } 
        else { high = mid; }
    }
    return (low == 1) ? 0 : low;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int mxLen, width, n, m;
    while (std::cin >> mxLen >> width) {
        
        std::cin >> n;
        std::vector<int> a(n);
        for (auto &it : a) { std::cin >> it; }
        
        std::cin >> m;
        std::vector<int> b(m);
        for (auto &it : b) { std::cin >> it; }
        
        std::sort(a.begin(), a.end());
        std::sort(b.begin(), b.end());
        std::cout << solve<SegmentTree<double>>(mxLen, width, a, b) << std::endl;
    }    
    return 0;
}