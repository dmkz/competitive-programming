/*
    Problem: 340A. The Wall
    
    Solution: math, gcd, lcm, O(log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

typedef long long ll;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

ll lcm(int a, int b) {
    return ll(a) / gcd(a,b) * b;
}

int solve(int x, int y, int r) {
    return int(r / lcm(x,y));
}

int main() {
    int x, y, a, b; std::cin >> x >> y >> a >> b;
    std::cout << solve(x,y,b)-solve(x,y,a-1);
    return 0;
}