/*
    "Веревочный мост": сортировка, рекурсия, жадный алгоритм, O(n log(n))
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    
    std::vector<int> time(n);
    
    for (auto& it : time) {
        std::cin >> it;
    }
    
    std::sort(time.begin(), time.end());
    
    std::vector<ll> answ(n);
    
    std::function<ll(int)> solve = [&](const int size) {
        if (size < 2) {
            return (ll)time[size];
        }
        if (!answ[size]) {
            answ[size] = std::min(
                time[1] + time[0] + time[size] + time[1] + solve(size-2), 
                time[size] + time[0] + solve(size-1)
            );
        }
        return answ[size];
    };
    
    std::cout << solve(n-1);
    
    return 0;
}