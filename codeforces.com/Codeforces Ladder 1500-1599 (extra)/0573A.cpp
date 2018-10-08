/*
    Problem: 573A. Bear and Poker
    
    Solution: gcd, math, O(n log(MAX))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
inline int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
bool check(int number) {
    while (number % 2 == 0) number /= 2;
    while (number % 3 == 0) number /= 3;
    return number == 1;
}
int main() {
    int n; std::cin >> n;
    std::vector<int> arr(n);
    for (auto& it : arr) std::cin >> it;
    int gcd = arr[0];
    for (int i = 1; i < n; ++i) {
        gcd = ::gcd(gcd, arr[i]);
    }
    for (auto& it : arr) it /= gcd;
    bool flag = true;
    for (auto it : arr) {
        if (!check(it)) {
            flag = false;
            break;
        }
    }
    std::cout << (flag ? "Yes" : "No");
    return 0;
}