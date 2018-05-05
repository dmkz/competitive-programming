#pragma GCC diagnostic ignored "-Wunused-result"

#include <stdio.h>
#include <bits/stdc++.h>

int main() {
    std::string s; std::cin >> s; std::sort(s.begin(), s.end());
    do {
        printf("%s\n", s.c_str());
    } while (std::next_permutation(s.begin(), s.end()));
    return 0;
}