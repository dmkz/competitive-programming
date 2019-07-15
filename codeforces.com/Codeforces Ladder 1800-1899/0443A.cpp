/*
    Problem: 443A. Anton and Letters
    Solution: strings, implementation, O(n*log(n))
*/
#include <bits/stdc++.h>
int main() {
    std::string s;
    std::getline(std::cin, s);
    std::set<char> set;
    for (auto it : s) {
        if ('a' <= it && it <= 'z') {
            set.insert(it);
        }
    }
    std::cout << set.size() << std::endl;
    return 0;
}