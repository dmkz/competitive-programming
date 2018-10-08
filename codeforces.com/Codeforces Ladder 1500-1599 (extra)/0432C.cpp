/*
    Problem: 432C. Prime Swaps
    
    Solution: math, primes, constructive, sorting, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>
#include <functional>
struct Pair { int a,b; };
int main() {
    // Get primes using sieve:
    const int NMAX = (int)1e5;
    std::vector<bool> is_prime(1+NMAX, 1);
    for (int i = 2; i * i <= NMAX; ++i) {
        if (!is_prime[i]) continue;
        for (int j = i * i; j <= NMAX; j += i) {
            is_prime[j] = false;
        }
    }
    std::vector<int> primes;
    for (int i = 2; i <= NMAX; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    // Input array:
    int n; scanf("%d", &n);
    std::vector<int> arr(n), pos(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
        arr[i]--;
        pos[arr[i]] = i;
    }
    
    // Vector for swaps:
    std::vector<Pair> answ;
    
    // Function for one swap:
    std::function<void(int,int)> exchange = [&](int i, int j) {
        answ.push_back(Pair{i+1,j+1});
        pos[arr[i]] = j;
        pos[arr[j]] = i;
        std::swap(arr[i], arr[j]);
    };
    // Function for moving item from position `curr` to position `need` limited by `nSteps`:
    std::function<void(int,int,int)> step = [&](int curr, int need, int nSteps) {
        assert(curr-need+1 >= 2);
        assert(nSteps > 0);
        if (is_prime[curr-need+1]) {
            exchange(curr, need);
            return;
        }
        auto prime = *std::prev(std::upper_bound(primes.begin(), primes.end(), curr-need+1));
        exchange(curr, curr-prime+1);
        step(curr-prime+1, need, nSteps-1);
    };
    for (int i = 0; i < n; ++i) {
        if (arr[i] != i) step(pos[i], i, 5);
    }
    // Check and output:
    assert(std::is_sorted(arr.begin(), arr.end()));
    assert((int)answ.size() <= 5 * n);
    printf("%d\n", (int)answ.size());
    for (auto& p : answ) {
        if (p.a > p.b) std::swap(p.a,p.b);
        printf("%d %d\n", p.a, p.b);
    }
    return 0;
}