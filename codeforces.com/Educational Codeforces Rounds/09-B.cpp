/*
    Problem: 632B. Alice, Bob, Two Teams
    
    Solution: dynamic programming, prefix sum, suffix sum, O(n)
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>

typedef long long ll;

int main() {
    int n; 
    scanf("%d", &n);
    
    std::vector<int> p(n); 
    for (auto& it : p) scanf("%d", &it);
    
    char buf[500000+1]; 
    scanf("%500001s", buf);
    std::string s(buf);
    
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += int(s[i] == 'B') * p[i];
    }
    
    std::vector<ll> prefix{sum};
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'A') {
            prefix.push_back(prefix.back() + p[i]);
        } else {
            prefix.push_back(prefix.back() - p[i]);
        }
    }
    
    std::vector<ll> suffix{sum};
    for (int i = n-1; i >= 0; --i) {
        if (s[i] == 'A') {
            suffix.push_back(suffix.back() + p[i]);
        } else {
            suffix.push_back(suffix.back() - p[i]);
        }
    }
    
    ll answ = std::max(
        *std::max_element(prefix.begin(), prefix.end()),
        *std::max_element(suffix.begin(), suffix.end())
    );
    printf("%lld\n", answ);
    return 0;
}