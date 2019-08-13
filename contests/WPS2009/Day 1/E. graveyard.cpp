/*
    Problem: E. graveyard
    Solution: implementation, constructive, O(n)
*/
#include <bits/stdc++.h>
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n, x, y; std::cin >> n >> x >> y; ) {
        char sign = '+'; y--,x--;
        if (x > y) { sign = '-'; x = n - x - 1; y = n - y - 1; }
        assert(x < y);
        int a = x, b = y - x - 1, c = n - 1 - y;
        if (b == 0 && a > 0 && c > 0) {
            std::cout << 0 << "\n";
            continue;
        }
        int p = x;
        if (a > 0) {
            while (p - 2 >= 0) {
                p -= 2;
                char dir = char('+'-sign+'-');
                std::cout << dir << "2 ";
            }
            if (p != 0) {
                assert(p == 1);
                p -= 1;
                char dir = char('+'-sign+'-');
                std::cout << dir << "1 ";
            } else {
                p += 1;
                std::cout << sign << "1 ";
                assert(p == 1);
            }
            while (p < x) {
                p += 2;
                std::cout << sign << "2 ";
            }
            assert(p == x+1);
        }
        while (p+1 < y) {
            p++;
            std::cout << sign << "1 ";
        }
        if (p == y) {
            assert(c == 0);
            std::cout << std::endl;
            continue;
        }
        assert(p == y-1);
        if (c > 0) {
            while (p + 2 < n) {
                p += 2;
                std::cout << sign << "2 ";
            }
            if (p == n-1) {
                p -= 1;
                char dir = char('+'-sign+'-');
                std::cout << dir << "1 ";
            } else {
                p += 1;
                std::cout << sign << "1 ";
            }
            while (p > y) {
                p -= 2;
                char dir = char('+'-sign+'-');
                std::cout << dir << "2 ";
            }
            assert(p == y);
        } else {
            std::cout << sign << "1 ";
            p += 1;
            assert(p == y);
        }
        std::cout << std::endl;
    }
    return 0;
}