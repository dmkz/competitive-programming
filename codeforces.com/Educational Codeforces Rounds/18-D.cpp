/*
    Problem: 792D. Paths in a Complete Binary Tree
    
    Solution: trees, implementation, O(q * log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>
#include <functional>

typedef long long ll;

ll solve(ll n, ll vert, const std::string& s) {
    std::vector<ll> stack{n / 2 + 1};
    ll add = 0;
    while (stack.back() != vert) {
        if (vert > stack.back()) {
            ll old = add;
            add += (stack.back()-old);
            stack.push_back((stack.back() - old) / 2 + add);
        } else {
            stack.push_back((stack.back() - add) / 2 + add);
        }
    }
    
    stack.pop_back();
    
    std::function<void(void)> up = [&]() {
        if (stack.empty()) return;
        if (vert > stack.back()) {
            add = stack.back() - 2 * (vert-add);
        }
        vert = stack.back();
        stack.pop_back();
    };
    
    std::function<void(void)> left = [&]() {
        if (vert - add == 1) return;
        stack.push_back(vert);
        vert = (vert - add) / 2 + add;
    };
    
    std::function<void(void)> right = [&]() {
        if (vert - add == 1) return;
        stack.push_back(vert);
        ll old = add;
        add += (vert-old);
        vert = (vert - old) / 2 + add;
    };
    
    for (auto c : s) {
        if (c == 'U') {
            up();
        } else if (c == 'L') {
            left();
        } else if (c == 'R') {
            right();
        }
    }
    return vert;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    ll n, q; std::cin >> n >> q;
    
    while (q--) {
        ll vert; std::cin >> vert;
        std::string s; std::cin >> s;
        std::cout << solve(n, vert, s) << '\n';
    }
    
    return 0;
}