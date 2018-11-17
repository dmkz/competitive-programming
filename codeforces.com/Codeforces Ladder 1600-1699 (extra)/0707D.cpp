/*
    Problem: 707D. Persistent Bookcase
    
    Solution: trees, dfs, queries offline, bitset, O(q+n*m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <bitset>
#include <functional>

typedef unsigned long long ull;

struct Edge {
    int next, type, iG, iE;
};

struct Bitset {

    int size;

    int nOnes;
    
    std::vector<ull> data;
    
    Bitset(int size_ = 0) : size(size_), nOnes(0), data((size_+63)/64,0) { }

    int count() const {
        return nOnes;
    }
    
    int test(int p) const {
        int g = p / 64; p %= 64;
        return int((data[g] >> p) & 1);
    }
    
    void inverse() {
        nOnes = size - nOnes;
        for (auto& it : data) { it = ~it; }
    }
    
    void set(int p, int v) {
        int g = p / 64; p %= 64;
        nOnes -= int((data[g] >> p) & 1);
        nOnes += v;
        (data[g] &= ~(ull(1) << p)) |= (ull(v) << p);
    }
    
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);
    int nG, nE, nQ;
    while (std::cin >> nG >> nE >> nQ) {
        std::vector<Bitset> arr(nG, Bitset(nE)); 
        std::vector<std::vector<Edge>> next(1+nQ);
        int curr = 0;
        for (int i = 1, t, fi, se; i <= nQ; ++i) {
            std::cin >> t;
            if (t == 1 || t == 2) {
                std::cin >> fi >> se;
                next[curr].push_back(Edge{i, t, fi-1, se-1});
            } else if (t == 3) {
                std::cin >> fi;
                next[curr].push_back(Edge{i, t, fi-1, -1});
            } else {
                assert(t == 4);
                std::cin >> fi;
                curr = fi;
                next[curr].push_back(Edge{i, t, -1, -1});
            }
            curr = i;
        }
        int answ = 0;
        std::vector<int> answer(1+nQ, -1);
        std::function<void(int)> dfs = [&](int u) {
            assert(answer[u] == -1);
            answer[u] = answ;
            for (auto& e : next[u]) {
                if (e.type == 1 || e.type == 2) {
                    int i = e.iG, j = e.iE;
                    int prev = arr[i].test(j);
                    answ -= prev;
                    arr[i].set(j, e.type % 2);
                    answ += e.type % 2;
                    dfs(e.next);
                    answ -= e.type % 2;
                    arr[i].set(j, prev);
                    answ += prev;
                } else if (e.type == 3) {
                    int i = e.iG;
                    answ -= (int)arr[i].count();
                    arr[i].inverse();
                    answ += (int)arr[i].count();
                    dfs(e.next);
                    answ -= (int)arr[i].count();
                    arr[i].inverse();
                    answ += (int)arr[i].count();
                } else {
                    dfs(e.next);
                }
            }
        };
        dfs(0);
        for (int i = 1; i <= nQ; ++i) {
            std::cout << answer[i] << "\n";
        }
        std::cout << std::endl;
    }
    return 0;
}