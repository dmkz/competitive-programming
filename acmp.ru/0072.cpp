#pragma GCC diagnostic ignored "-Wunused-result"

#include <stdio.h>
#include <bits/stdc++.h>

int main() {
    std::string s; 
    std::cin >> s;
    std::next_permutation(s.begin(), s.end());
    std::cout << s << std::endl;
    return 0;
}