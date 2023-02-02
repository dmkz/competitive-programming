/*
    problem: 4508. maximum xor (hard)
    solution: xor, basis, linear algebra, maximum xor, O(n log(A))
*/
#include "template.hpp"
#include "algebra.hpp"
int main() {
    using namespace algos::algebra;
    int n; std::cin >> n;
    XorBasis<int> basis;
    for (int i = 0, x; i < n; i++) {
        std::cin >> x;
        basis += x;
    }
    std::cout << basis.max() << std::endl;
}
