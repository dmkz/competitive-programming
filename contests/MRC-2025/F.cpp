// Задача: F, Вердикт: OK, Время: 48ms, Память: 2.06Mb
#include <bits/stdc++.h>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout << std::setprecision(12) << std::fixed;
    int n; std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    // каждый элемент либо уменьшается, либо увеличивается в каждый момент времени
    // значит минимум увеличивается, а максимум - уменьшается. всё закончится,
    // когда максимум сравняется с минимумом:
    auto [min,max] = std::minmax_element(a.begin(), a.end());
    std::cout << (*max - *min) / 2.0 << std::endl;
}
