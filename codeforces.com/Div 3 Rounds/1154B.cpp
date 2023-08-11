/*
    problem: 1154B. Make Them Equal
    solution: constructive, min, max, O(n)
*/
#include "template.hpp"
int main() {
    int n; std::cin >> n;
    vi a(n); std::cin >> a;
    // min + d == max - d, d >= 0
    // 2 * d = max - min
    // d = (max - min) / 2
    // случай выше если мы меняем и максимум, и минимум
    // иначе мы не меняем либо минимум, либо максимумoooo
    std::sort(all(a));
    auto check = [&](int targetItem) {
        vi items;
        int delta = 0;
        for (int i = 0; i < isz(a); i++) {
            int d = std::abs(a[i] - targetItem);
            items << d;
            if (d != 0)
                delta = d;
        }
        std::sort(all(items));
        reuniq(items);
        if (isz(items) == 1 || (isz(items) == 2 && items.front() == 0))
            return delta;
        else
            return -1;
    };
    const int min = a.front(), max = a.back();
    for (int target : {min + (max-min)/2, min, max})
        if (auto res = check(target); res != -1) {
            std::cout << res << std::endl;
            return 0;
        }
    std::cout << -1 << std::endl;
    return 0;
}
