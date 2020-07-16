/*
    Problem: 78A. Haiku
    Solution: strings, counting, O(n)
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
std::string alp = "aeiou";
using vi = std::vector<int>;
int main() {
    std::sort(all(alp));
    vi vec;
    for (std::string s; std::getline(std::cin, s); ) {
        int cnt(0);
        for (auto it : s) cnt += std::binary_search(all(alp), it);
        vec.push_back(cnt);
    }
    std::cout << (vec == vi{5,7,5} ? "YES" : "NO") << std::endl;
}