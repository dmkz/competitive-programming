/*
    Problem: 525E. Anya and Cubes
    
    Solution: meet-in-the-middle, binary search, brute force, O(3^(n/2) * k * n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

#define all(x) (x).begin(), (x).end()

typedef long long ll;
typedef std::vector<int> vi;

const int NMAX = 25, FMAX = 18;
ll fact[1+FMAX];

struct Solver {

    std::vector<std::vector<ll>> data; // data[nFact] --> vector of possible sums

    Solver(int limFact, ll limSum, const vi& arr) {
        data.resize(limFact+1);
        data[0].push_back(0);
        brute(0, arr, 0, limFact, 0, limSum);
        for (auto& it : data) {
            std::sort(it.begin(), it.end());
        }
    }
    
    void brute(int pos, const vi& arr, int curFact, int limFact, ll curSum, ll limSum) {
        if (pos >= (int)arr.size()) return;
        int item = arr[pos];
        if (curFact < limFact && item <= FMAX && curSum + fact[item] <= limSum) {
            data[curFact+1].push_back(curSum + fact[item]);
            brute(pos+1, arr, curFact+1, limFact, curSum + fact[item], limSum);
        }
        if (curSum + item <= limSum) {
            data[curFact].push_back(curSum + item);
            brute(pos+1, arr, curFact, limFact, curSum + item, limSum);
        }
        brute(pos+1, arr, curFact, limFact, curSum, limSum);
    }
    
    ll count(int limFact, ll limSum, const Solver& solver) const {
        ll answ = 0;
        for (int f1 = 0; f1 <= limFact; ++f1) {
            for (int f2 = 0; f1 + f2 <= limFact; ++f2) {
                for (auto s : data[f1]) {
                    auto pair = std::equal_range(all(solver.data[f2]), limSum - s);
                    answ += int(pair.second-pair.first);
                }
            }
        }
        return answ;
    }
};

int main() {
    fact[0] = fact[1] = 1;
    for (int i = 2; i <= FMAX; ++i) {
        fact[i] = fact[i-1] * i;
    }
    int n, k; ll s;
    while (std::cin >> n >> k >> s) {
        vi fi, se;
        for (int i = 0, v; i < n; ++i) {
            std::cin >> v;
            if (i & 1) {
                fi.push_back(v);
            } else {
                se.push_back(v);
            }
        }
        Solver solver1(k, s, fi), solver2(k, s, se);
        std::cout << solver1.count(k, s, solver2) << std::endl;
    }
    return 0;
}