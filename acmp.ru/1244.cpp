#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cassert>

typedef long double Real;

int main() {
    Real r1, R1, r2, R2;
    Real A, B, C, D;
    Real x, y;
    std::cin >> r1 >> R1 >> r2 >> R2 >> A >> B >> C >> D >> x >> y;
    int extra = 1;
    Real answ = 0;
    if (x*x+y*y > R1*R1) {
        printf("0");
        return 0;
    } else if (x*x + y*y >= r1 * r1) {
        extra = 2;
    } else if (R2 * R2 >= x*x + y*y && x*x + y*y >= r2 * r2) {
        extra = 3;
    }
    if (x > 0) {
        if (y > 0) {
            answ = extra * A;
        } else if (y < 0) {
            answ = extra * D;
        } else {
            assert(y == 0);
            answ = extra * std::max(A, D);
        }
    } else if (x < 0) {
        if (y > 0) {
            answ = extra * B;
        } else if (y < 0) {
            answ = extra * C;
        } else {
            assert(y == 0);
            answ = extra * std::max(B, C);
        }
    } else {
        assert(x == 0);
        if (y > 0) {
            answ = extra * std::max(A, B);
        } else if (y < 0) {
            answ = extra * std::max(C, D);
        } else {
            assert(y == 0);
            
            answ = extra * std::max({A, B, C, D});
        }
    }
    std::cout << std::fixed << std::setprecision(0) << answ;
    return 0;
}