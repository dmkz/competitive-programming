/*
    problem: 1102E. Monotonic Renumeration
    solution: combinatorics, prefix, suffix, counting, std::map
*/
#include "template.hpp"
#include "numeric.hpp"
using namespace algos::numeric;
const int mod = 998244353;
using Int = IntMod<mod>;
/*
    1 2 1 2 3
    answer: 2
    0 0 0 0 0
    0 0 0 0 1
*/
/*
    100 1
    answer: 2
    0 0
    0 1
*/
/*
    1 3 3 7
    answer: 4
    0 0 0 0
    0 0 0 1
    0 1 1 1
    0 1 1 2
*/
/*
    мы не можем увеличивать, если справа есть такие же элементы, как слева
    иначе всегда можем увеличить и ответ умножается на 2
    ответ равен степени двойки, равной числу описанных выше ситуаций
*/
int main() {
    int n; std::cin >> n;
    vi a(n); std::cin >> a;
    std::map<int,int> cntLeft, cntRight;
    for (auto &it : a)
        cntRight[it]++;
    int nSame = 0;
    auto add = [&](int x) {
        int a = ++cntLeft[x];
        int b = --cntRight[x];
        if (b == 0 && a > 1)
            nSame--;
        if (a == 1 && b > 0)
            nSame++;
    };
    Int answer{1};
    for (int i = 0; i + 1 < n; i++) {
        add(a[i]);
        if (nSame == 0)
            answer *= 2;
    }
    std::cout << answer << std::endl;
}
