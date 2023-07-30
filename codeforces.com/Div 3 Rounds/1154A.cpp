/*
    problem: 1154A. Restoring Three Numbers
    solution: math, sorting, max
*/
#include "template.hpp"
int main() {
    // из максимального вычесть остальные
    vi a(4); std::cin >> a;
    std::sort(all(a));
    int max = a--;
    for (auto &it : a)
        std::cout << (it = max - it) << ' ';
    return 0;
}
