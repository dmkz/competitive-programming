/*
    problem: 1102C. Doors Breaking and Repairing
    solution: game theory
*/
#include "template.hpp"
int main() {
    int n, x, y;
    std::cin >> n >> x >> y;
    vi a(n); std::cin >> a;
    if (x > y) {
        std::cout << n << std::endl;
        return 0;
    }
    int notGreater{};
    for (auto &it : a)
        notGreater += !(x < it);
    std::cout << (notGreater+1)/2 << std::endl;
}
