/*
    problem: 1102A. Integer Sequence Dividing
    solution: math, sum of arithmetic progression
*/
#include "template.hpp"
int main() {
    int n; std::cin >> n;
    ll sum = n * (n+1LL)/2;
    std::cout << sum % 2 << std::endl;
}
