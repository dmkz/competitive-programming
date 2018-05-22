#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

int main() {
    int n; std::cin >> n;
    std::vector<int> a(n); for (auto& it : a) std::cin >> it;
    std::vector<int> len(n, 1);
    for (int curr = 1; curr < n; ++curr) {
        for (int prev = curr-1; prev >= 0; --prev) {
            if (a[prev] < a[curr] && len[prev]+1 > len[curr]) {
                len[curr] = len[prev]+1;
            }
        }
    }
    std::vector<int> answ;
    int curr = int(std::max_element(len.begin(), len.end()) - len.begin());
    int max = len.at(curr);
    answ.push_back(a.at(curr));
    for (int prev = curr-1; prev >= 0; prev--) {
        if (a[prev] < a[curr] && len[prev]+1 == len[curr]) {
            answ.push_back(a[prev]);
            curr = prev;
        }
    }
    std::reverse(answ.begin(), answ.end());
    assert((int)answ.size() == max);
    std::cout << answ.size() << std::endl;
    for (auto& it : answ) {
        std::cout << it << ' ';
    }
    std::cout << std::endl;
    return 0;
}