/*
    Problem: 501A. Contest
    Solution: implementation
*/
#include <iostream>

int main() {
    double p1, p2, t1, t2;
    std::cin >> p1 >> p2 >> t1 >> t2;
    double r1 = std::max(3*p1/10, p1 - p1 / 250 * t1);
    double r2 = std::max(3*p2/10, p2 - p2 / 250 * t2);
    if (r1 < r2) {
        printf("Vasya");
    } else if (r1 > r2) {
        printf("Misha");
    } else {
        printf("Tie");
    }
    return 0;
}