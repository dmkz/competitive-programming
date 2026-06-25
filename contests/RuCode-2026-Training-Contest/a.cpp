// интерактив, ветвление, O(1)
// Задача: A, Вердикт: OK, Время: 3ms, Память: 2.01Mb
#include <bits/stdc++.h>
#include <cassert>
main() {
    int r, q;
    std::cin >> r >> q;
    if (r > 0) {
        std::cout << "1" << std::endl;
        int r1, q1;
        std::cin >> r1 >> q1;
        if (r1 + 1 == r && q1 - 1 == q) {
            std::cout << "r" << std::endl;
        } else {
            std::cout << "c" << std::endl;
        }
    } else {
        assert(q > 0);
        std::cout << "2" << std::endl;
        int r1, q1;
        std::cin >> r1 >> q1;
        if (r1 - 1 == r && q1 + 1 == q) {
            std::cout << "r" << std::endl;
        } else {
            std::cout << "c" << std::endl;
        }
    }
}
