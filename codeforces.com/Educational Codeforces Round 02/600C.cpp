/*
    Sort by counting, palindrome, greedy, O(n)
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int main() {    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::string s; std::cin >> s;
    
    std::vector<int> count(26); // count of (letter - 'a')
    
    // sort by counting:
    for (auto it : s) {
        count[it-'a']++;
    }
    
    int l = 0, r = 25;
    while (true) {
        while (l < 26 && count[l] % 2 == 0) ++l;
        while (r >= l && count[r] % 2 == 0) --r;
        if (l >= r) {
            break;
        }
        count[l]++;
        count[r]--;
    }
    
    // Building a palindrome:
    std::string s1;
    for (int i = 0; i < 26; ++i) {
        s1 += std::string(count[i] / 2, 'a'+i);
    }
    std::string s2 = s1;
    
    std::reverse(s2.begin(), s2.end());    
    
    for (int i = 0; i < 26; ++i)
        if (count[i] % 2 == 1) {
            s1 += char('a'+i);
            break;
        }
    std::cout << s1 << s2 << std::endl;
    return 0;
}