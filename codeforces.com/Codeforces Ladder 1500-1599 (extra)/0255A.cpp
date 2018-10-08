/*
    Problem: 255A. Greg's Workout
    
    Solution: implementation, O(n)
    
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
    vi cnt(3);
    for (int i = 0; i < n; ++i) {
        int a; std::cin >> a;
        cnt[i % 3] += a;
    }
    int mx = int(std::max_element(all(cnt))-cnt.begin());
    if (mx == 0) {
        std::cout << "chest";
    } else if (mx == 1) {
        std::cout << "biceps";
    } else {
        std::cout << "back";
    }
    return 0;
}