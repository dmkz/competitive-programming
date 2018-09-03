/*
    Problem: 797C. Minimal string
    
    Solution: strings, stack, greedy, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include <cassert>
#include <numeric>
#include <cmath>

#define ios_fast std::ios_base::sync_with_stdio(0); \
std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);

#define  input(x) for (auto& it : (x)) std::cin >> it
#define    all(x) (x).begin(), (x).end()
#define   size(x) (int)((x).size())
#define unique(x) (x).erase(std::unique(all((x))), (x).end())

const int mod = (int)1e9+7;
typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<ll> vll;

void update(int& a, int b) {
    a = std::max(a,b);
}

int main() {
    ios_fast;
    std::string s; std::cin >> s;
    vi cnt(26,0);
    for (auto& it : s) cnt[it-'a']++;
    std::string stack, answer;
    int pos = 0;
    for (char c = 'a'; c <= 'z'; ++c) {
        while (!stack.empty() && stack.back() <= c) {
            answer += stack.back();
            stack.pop_back();
        }
        while (cnt[c-'a'] > 0) {
            assert(pos < size(s));
            if (s[pos] != c) {
                stack.push_back(s[pos]);
            } else {
                answer.push_back(s[pos]);
            }
            cnt[s[pos++]-'a']--;
        }
    }
    while (!stack.empty()) {
        answer.push_back(stack.back());
    }
    std::cout << answer;
    return 0;
}