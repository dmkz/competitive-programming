/*
    Problem: 797D. Broken BST
    
    Solution: stack, DFS, trees, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include <cassert>
#include <numeric>
#include <cmath>
#include <map>
#include <ext/pb_ds/assoc_container.hpp>

#define ios_fast std::ios_base::sync_with_stdio(0); \
std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);

#define  input(x) for (auto& it : (x)) std::cin >> it
#define    all(x) (x).begin(), (x).end()
#define   size(x) (int)((x).size())
#define unique(x) (x).erase(std::unique(all((x))), (x).end())

const bool debug = false;

const int INF = (int)1e9+7;
typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<ll> vll;

int main() {
    ios_fast;
    int n; std::cin >> n;
    
    vi item, value(n), left(n), right(n);
    for (int i = 0; i < n; ++i) {
        int v, l, r; 
        std::cin >> v >> l >> r; 
        l = std::max(l-1,-1);
        r = std::max(r-1,-1);
        value[i] = v;
        left[i] = l;
        right[i] = r;
        item.push_back(v);
    }
    std::sort(all(item));
    unique(item);
    vi cnt(size(item)), can(size(item));
    for (int i = 0; i < n; ++i) {
        value[i] = int(std::lower_bound(all(item), value[i]) - item.begin());
        cnt[value[i]]++;
    }
    int root = -1;
    {
        vi order, visited(n);
        std::function<void(int)> top_sort = [&](int vert) {
            int l = left[vert], r = right[vert];
            if (l != -1 && !visited[l]) {
                visited[l] = true;
                top_sort(l);
            }
            if (r != -1 && !visited[r]) {
                visited[r] = true;
                top_sort(r);
            }
            order.push_back(vert);
        };
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                visited[i] = true;
                top_sort(i);
            }
        }
        root = order.back();
    }
    assert(root != -1);
    vi lsval{INF}, rsval{-INF}, lsmin{INF}, rsmax{-INF};
    
    std::function<void(int)> visit = [&](int vert) {
        int val = value[vert];
        assert(!lsmin.empty() && !rsmax.empty());
        if (lsmin.back() > val && val > rsmax.back()) {
            can[val] = 1;
        }
        // left
        int l = left[vert];
        if (l != -1) {
            lsmin.push_back(std::min(lsmin.back(), val));
            visit(l);
            lsmin.pop_back();
        }
        
        // right
        int r = right[vert];
        if (r != -1) {
            rsmax.push_back(std::max(rsmax.back(), val));
            visit(r);
            rsmax.pop_back();
        }
    };
    
    visit(root);
    
    int answ = n;
    for (int i = 0; i < size(item); ++i) {
        answ -= cnt[i] * can[i];
    }
    std::cout << answ;
    
    return 0;
}