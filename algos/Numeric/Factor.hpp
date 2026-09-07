#ifndef __FACTOR_HPP__
#define __FACTOR_HPP__
/*******************************************************************************************
 * The file "Factor.hpp" is a part of competitive programming C++ library "algos".         *
 * You can find it here: https://github.com/dmkz/competitive-programming/tree/master/algos *
 *******************************************************************************************/
namespace algos {
namespace factor {
    
    /**
     * Generates the list of all primes not greater than `n`
     */
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

    /**
     * Generates the least prime factor for every integer from `0` to `n`
     */
    inline std::vector<int> genMinPrime(int n) {
        std::vector<int> minPrime(n+1);
        for (int i = 2; i <= n; i++) {
            if (minPrime[i]) continue;
            minPrime[i] = i;
            if (1LL*i*i <= n)
                for (int j = i*i; j <= n; j += i)
                    if (!minPrime[j])
                        minPrime[j] = i;
        }
        return minPrime;
    }

    /**
     * Calls `func` for every prime power occurring in the factorization of `x`
     */
    template<typename T, typename Func>
    inline void forEachPrimePower(T x, const std::vector<int> &minPrime, Func func) {
        while (x > 1) {
            int p = minPrime[x];
            T pw = 1;
            while (x % p == 0) {
                x /= p;
                func(pw *= p);
            }
        }
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
    
    template<typename T>
    inline
    void generateAllDivisors(const std::vector<std::pair<T,int>> &res,
                             auto &divs, int initial = 1)
    {
        divs.clear();
        divs.push_back(initial);
        for (const auto &[p,cnt] : res) {
            T pp = 1;
            const int saved = isz(divs);
            for (int x = 1; x <= cnt; x++) {
                pp *= p;
                for (int i = 0; i < saved; i++)
                    divs << divs[i] * 1LL * pp;
            }
            /*
            // faster way:
            for (int block = saved; block < isz(divs); block *= 2) {
                for (int left = 0; left < isz(divs); left += 2 * block) {
                    auto M = divs.begin()+std::min(left+block,isz(divs));
                    auto R = divs.begin()+std::min(left+2*block,isz(divs));
                    std::inplace_merge(divs.begin()+left, M, R);
                }
            }*/
            ///*
            // slower way:
            for (int x = 1; x <= cnt; x++) {
                std::inplace_merge(divs.begin(), divs.begin()+x*saved, 
                                   divs.begin()+(x+1)*saved);
            }
            //*/
        }
    }
    
    template<typename T>
    inline
    void generateAllDivisors(T res, auto &divs,
                             const std::vector<int>& pr,
                             int initial = 1)
    {
        static std::vector<std::pair<T,int>> expansion;
        factor(res,expansion,pr);
        generateAllDivisors(expansion,divs,initial);
    }
    
} // namespace factor
} // namespace algos
#endif // __FACTOR_HPP__