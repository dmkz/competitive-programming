/*
    Problem: 111A. Petya and Inequiations
    
    Solution: greedy, math, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

typedef long long ll;
typedef std::vector<int> vi;

vi solve(int n, ll x, int y) {
    vi arr(n);
    for (int i = 0; i < n-1; ++i) {
        arr[i] = 1;
    }
    arr.back() = y - (n-1);
    if (arr.back() < 1) {
        return {-1};
    }
    ll res = (ll)arr.back()*arr.back()+n-1;
    if (res >= x) {
        return arr;
    } else {
        return {-1};
    }
}

int main() {
    int n, y; ll x;
    while (std::cin >> n >> x >> y) {
        vi answ = solve(n,x,y);
        for (auto it : answ) {
            std::cout << it << "\n";
        }
    }
    return 0;
}