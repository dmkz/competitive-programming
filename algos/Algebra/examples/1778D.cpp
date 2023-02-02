/*
    problem: 1778D. Flexible String Revisit
    solution: probability theory, expected value, tridiagonal matrices, gauss elimination
*/
#pragma GCC optimize("Ofast")
#include "template.hpp"
#include "numeric.hpp"
#include "algebra.hpp"
const int mod = 998244353;
using namespace algos::numeric;
using Int = IntMod<mod>;
int main() {
    int tt; std::cin >> tt;
    while(tt--) {
        int n; std::cin >> n;
        algos::algebra::Tridiag<Int> system(n+1);
        auto [A,b] = system.getView();
        for (int i = 0; i <= n; i++) {
            if (i == 0) {
                A(i,i)   = 1;
                A(i,i+1) = -1;
                b(i) = 1;
            } else if (i == n) {
                A(i,i) = 1;
                b(i) = 0;
            } else {
                A(i,i-1) = -Int(i)/n;
                A(i,i) = 1;
                A(i,i+1) = -Int(n-i)/n;
                b(i) = 1;
            }
        }
        std::string s,t; std::cin >> s >> t;
        int nEq = 0;
        for (int i = 0; i < n; i++)
            nEq += (s[i] == t[i]);
        std::cout << system.solve()[nEq] << '\n';
    }
}
