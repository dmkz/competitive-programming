#include <bits/stdc++.h>

typedef int64_t Int;

int main() {
    Int nSweets, nPeople, xMax, dMax;
    std::cin >> nSweets >> nPeople >> xMax >> dMax;
    Int answ = 0;
    for (Int curr = 1; curr <= dMax; ++curr) {
        // Для текущего curr находим максимальное x из условия:
        // (curr-1) * nPeople * x + x <= nSweets
        // При умножении nPeople * (curr-1) возможно переполнение
        Int x = std::min(xMax, Int(nSweets / (__float128(curr-1) * nPeople + 1)));
        answ = std::max(answ, x * curr);
    }
    std::cout << answ << std::endl;
    return 0;
}