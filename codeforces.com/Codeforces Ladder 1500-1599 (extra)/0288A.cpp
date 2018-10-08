/*
    Problem: 288A. Polo the Penguin and Strings
    
    Solution: constructive, greedy, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

int main() {
    int n, k; std::cin >> n >> k;
    if (k > n || (k == 1 && n > 1)) { std::cout << -1; return 0; }
    if (k == 1 && n == 1) { std::cout << "a"; return 0; }
    std::string s(n,'.');
    s[0] = 'a';
    for (int i = 1; i < n; ++i) s[i] = char('b' - s[i-1] + 'a');
    k -= 2; char c = 'c';
    for (int i = n-k; i < n; ++i) {
        s[i] = c++;
    }
    std::cout << s;
    return 0;
}