#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>

typedef long long ll;

int main() {
    int n, cost; std::cin >> n >> cost;
    std::vector<int> a;
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        a.push_back(s == "half");
    }
    std::reverse(a.begin(), a.end());
    
    ll sum = 0, prev = 0;
    assert(a[0] == 0);
    for (auto& it : a) {
        if (it == 0) { // halfplus
            prev = 2 * prev+1;
        } else { // half
            prev = 2 * prev;
        }
        sum += cost * prev / 2;
    }
    std::cout << sum << std::endl;
    
    return 0;
}