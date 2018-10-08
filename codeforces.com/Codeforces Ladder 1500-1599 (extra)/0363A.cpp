/*
    Problem: 363A. Soroban
    
    Solution: implementation, strings, O(log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cassert>

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

int main() {
    int n; std::cin >> n;
    do {
        int digit = n % 10;
        n /= 10;
        std::string s;
        switch(digit) {
            case 0: s = "O-|-OOOO"; break;
            case 1: s = "O-|O-OOO"; break;
            case 2: s = "O-|OO-OO"; break;
            case 3: s = "O-|OOO-O"; break;
            case 4: s = "O-|OOOO-"; break;
            case 5: s = "-O|-OOOO"; break;
            case 6: s = "-O|O-OOO"; break;
            case 7: s = "-O|OO-OO"; break;
            case 8: s = "-O|OOO-O"; break;
            case 9: s = "-O|OOOO-"; break;
        };
        std::cout << s << '\n';
    } while (n > 0);
    return 0;
}