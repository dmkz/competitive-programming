#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>

int main() {
    int n; std::cin >> n;
    std::vector<int> a(n); for (auto& it : a) std::cin >> it;
    const int INF = (int)1e9+1;
    std::vector<int> min(1+n, INF); // [len] --> min element;
    std::vector<int> len(n, 1);
    min[0] = -INF;
    for (int i = 0; i < n; ++i) {
        int j = int(std::upper_bound(min.begin(), min.end(), a[i]) - min.begin());
        assert(j >= 1);
        if (min[j-1] < a[i]) {
            min[j] = a[i];
            len[i] = j;
        }
    }
    std::vector<int> answ;
    int curr = int(std::max_element(len.begin(), len.end())-len.begin());
    answ.push_back(a[curr]);
    for (int prev = curr-1; prev >= 0; --prev) {
        if (a[prev] < a[curr] && len[prev]+1 == len[curr]) {
            answ.push_back(a[prev]);
            curr = prev;
        }
    }
    std::reverse(answ.begin(), answ.end());
    std::cout << answ.size() << std::endl;
    for (auto& it : answ) {
        std::cout << it << ' ';
    }
    std::cout << std::endl;
    
    return 0;
}