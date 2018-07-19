/*
    Problem: 628C. Bear and String Distance

    Solution: greedy, strings, O(n)
*/

#include <iostream>
#include <string>
#include <algorithm>

int main() {
    int n, k; 
    std::cin >> n >> k;
    
    std::string s;
    std::cin >> s;
    
    std::string t(n, '?');
    
    for (int i = 0; i < n; ++i) {
        int left = s[i] - 'a';
        int right = 'z' - s[i];
        if (left < right) {
            t[i] = s[i] + std::min(k, right);
            k -= std::min(k, right);
        } else {
            t[i] = s[i] - std::min(k, left);
            k -= std::min(k, left);
        }
    }
    
    std::cout << (k > 0 ? "-1" : t);
    
    return 0;
}