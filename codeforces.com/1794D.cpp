// problem: 1794D. Counting Factorizations
// solution: combinatorics, primes, sum over all multiplications
#include "template.hpp"
#include "numeric.hpp"
#include "factor.hpp"

const int mod = 998244353, NMAX = 1 << 20;
using namespace algos::factor;
using namespace algos::numeric;
const auto C = Combinatorics<mod>(NMAX);
using Int = IntMod<mod>;
const auto pr = genPrimes(NMAX);
bool isPrime(int x) { return std::binary_search(all(pr), x); }


template<typename T>
std::vector<T> calcSum(const auto &a)
{
// дано n чисел a[0], a[1], a[2], ..., a[n]
// число x = 1. Мы можем либо взять i-е число и умножить x на a[i]
// либо не брать. Для каждого k - где k, кол-во взятых чисел, посчитать
// сумму по всем вариантам произведений
// например, a = {2, 3}
// взяли 0 чисел: 1
// взяли 1 число: 1*2 + 1*3 = 5
// взяли 2 числа: 1*2*3 = 6
// calcSum(vi{2,3}) вернёт {1, 5, 6}
    const int n = isz(a);
    std::vector cache(n, std::vector(n+1, T(0)));
    vvi visited(n, vi(n+1,0));
    std::function<T(int,int)> dfs =
    [&](int i, int take) -> T
    {
        // рассматриваем i-й элемент. Должны взять take
        // не можем набрать:
        const int cntItems = i+1;
        if (cntItems < take || take < 0)
            return 0;
        // придётся брать все:
        if (cntItems == 0)
            return (take == 0);
        assert(i >= 0);
        if (visited[i][take])
            return cache[i][take];
        visited[i][take] = 1;
        T res;
        if (cntItems == take) {
            res = std::accumulate(a.begin(), a.begin()+i+1, T(1),
                                     std::multiplies<T>());
        } else {
            // можем либо взять, либо не взять
            res = dfs(i-1,take-1)*a[i]+dfs(i-1,take);
        }
        return cache[i][take] = res;
    };
    std::vector<T> answ(n+1);
    for (int k = 0; k <= n; k++)
        answ[k] = dfs(n-1, k);
    return answ;
}
Int solve(int n, vi a) {
    vpii b;
    std::map<int,int> cnt;
    for (int i = 0; i < isz(a); i++) {
        if (isPrime(a[i])) {
            if (b.empty() || b.back().first != a[i])
                b << pii(a[i],0);
            if (b.back().first == a[i])
                b.back().second++;
        } else {
            cnt[a[i]]++;
        }
    }
    if (isz(b) < n)
        return 0;
    Int coeff = C.fact[n];
    for (auto &[_, x] : cnt)
        coeff /= C.fact[x];
    std::vector<Int> temp;
    for (auto &[_, x] : b) {
        coeff /= C.fact[x];
        temp << x;
    }
    return coeff * calcSum<Int>(temp)[n];
}
int main() {
    int n; std::cin >> n;
    vi a(2*n); std::cin >> a;
    std::sort(all(a));
    std::cout << solve(n,a) << std::endl;
}
