/*
    "Строки - 4": комбинаторика, математика, O(n)
*/

#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>

typedef long long ll;

inline int dist(char a, char b) {
    return a > b ? dist(b, a) : std::min(b-a, std::abs(a+26-b));
}

ll solve(std::string a, std::string b) {
    std::vector<int> ca(26), cb(26);
    for (auto& it : a) ca[it-'a']++;
    for (auto& it : b) cb[it-'a']++;
    ll answ = 0;
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            answ += ll(a.size()) * ca[i] * cb[j] * dist('a' + i, 'a' + j);
        }
    }
    return answ;
}

int main() {
    char buf[100000+1];
    scanf("%100000s", buf);
    std::string a(buf);
    scanf("%100000s", buf);
    std::string b(buf);
    assert(a.size() == b.size());
    std::cout << solve(a, b);
    return 0;
}