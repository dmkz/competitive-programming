#ifndef __FACTOR_HPP__
#define __FACTOR_HPP__
namespace algos {
namespace factor {
    
    inline std::vector<int> genPrimes(int n) {
        std::vector<bool> isPrime(1+n, 1);
        isPrime[0] = isPrime[1] = 0;
        for (int i = 2; i * i <= n; i++)
            if (isPrime[i])
                for (int j = i * i; j <= n; j += i)
                    isPrime[j] = false;
        std::vector<int> res;
        for (int i = 2; i <= n; i++)
            if (isPrime[i])
                res.push_back(i);
        return res;
    }

    template<typename A, typename B>
    inline
    void factorOnePrime(A p, B &x, std::vector<std::pair<B,int>> &res)
    {
        if (auto j = x / p; j * p == x) {
            int pw = 1;
            for (x = j; (j = x / p) * p == x; x = j)
                pw++;
            res.emplace_back(p, pw);
        }
    }
    
    template<typename T>
    inline void sortByPower(std::vector<std::pair<T,int>> &res)
    {
        std::sort(all(res), [](const auto &a, const auto &b)
        {
            return a.second < b.second || (a.second == b.second && a.first < b.first);
        });
    }
    
    template<typename T>
    inline void factorAsPower(T x, std::vector<std::pair<T,int>> &res)
    {
        if (T root3 = (T)cbrtl(x); root3 * root3 * root3 == x) {
            res.emplace_back(root3, 3);
        }
        else
        if (T root2 = (T)sqrtl(x); root2 * root2  == x) {
            res.emplace_back(root2, 2);
        }
        else
            res.emplace_back(x, 1);
    }
    
    template<typename T>
    inline void factor(T x, std::vector<std::pair<T,int>> &res,
                       const std::vector<int>& pr,
                       bool needSortByPower = false)
    {
        res.clear();
        for (int i = 0; i < isz(pr) && T(pr[i])*pr[i] <= x; i++)
            factorOnePrime(pr[i], x, res);
        if (x > 1) factorAsPower(x, res);
        if (needSortByPower) sortByPower(res);
    }
    
    template<typename T>
    inline void factor(T x, std::vector<std::pair<T,int>> &res,
                       bool needSortByPower = false)
    {
        res.clear();
        for (int p = 2; T(p) * p <= x; p++)
            factorOnePrime(p, x, res);
        if (x > 1) factorAsPower(x, res);
        if (needSortByPower) sortByPower(res);
    }
    
    template<typename T>
    inline
    std::vector<std::pair<T,int>>
    factor(T x, const std::vector<int>& primes,
           bool needSortByPower = false)
    {
        std::vector<std::pair<T,int>> res;
        factor(x,res,primes,needSortByPower);
        return res;
    }
    
    template<typename T>
    inline
    std::vector<std::pair<T,int>>
    factor(T x, bool needSortByPower = false)
    {
        std::vector<std::pair<T,int>> res;
        factor(x,res,needSortByPower);
        return res;
    }
    
} // namespace factor
} // namespace algos
#endif // __FACTOR_HPP__