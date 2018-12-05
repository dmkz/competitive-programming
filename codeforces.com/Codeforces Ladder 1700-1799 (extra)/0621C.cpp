/*
    Problem: 621C. Wet Shark and Flowers
    
    Solution: math, probability theory, expected value, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <vector>

typedef long double Real;

int number_of_dividing(int bound, int prime) {
    return bound / prime;
}

int number_of_dividing(int left, int right, int prime) {
    return number_of_dividing(right,prime)-number_of_dividing(left-1,prime);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    std::cout << std::fixed << std::setprecision(6);
    int n, p;
    while (std::cin >> n >> p) {
        std::vector<int> lt(1+n), rt(1+n);
        for (int i = 0; i < n; ++i) {
            std::cin >> lt[i] >> rt[i];
        }
        lt.back() = lt.front(), rt.back() = rt.front();
        Real answ = 0;
        for (int i = 0; i < n; ++i) {
            Real p1 = number_of_dividing(lt[i+0],rt[i+0],p) / Real(rt[i+0]-lt[i+0]+1);
            Real p2 = number_of_dividing(lt[i+1],rt[i+1],p) / Real(rt[i+1]-lt[i+1]+1);
            answ += 2000 * (1 - (1-p1)*(1-p2));
        }
        std::cout << answ << std::endl;
    }
    return 0;
}