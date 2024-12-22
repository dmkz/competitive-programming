#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using ll = long long;
void setmin(auto &x, const auto &y) { if (y < x) x = y; }

ll getNext(ll curr, int steps = 1) {
    assert(steps >= 0);
    while (steps --> 0) {
        curr = ((curr * 64) ^ curr) % 16777216;
        curr = ((curr / 32) ^ curr) % 16777216;
        curr = ((curr * 2048) ^ curr) % 16777216;
    }
    return curr;
}

void part1(const auto &numbers) {
    ll res = 0;
    for (auto it : numbers)
        res += getNext(it, 2000);
    std::cout << "part1 = " << res << std::endl;
}

void part2(const auto &numbers) {
    std::map<std::array<ll, 4>, ll> total;
    for (auto it : numbers) {
        // генерируем последовательность
        std::vector<ll> sequence{it % 10};
        for (int steps = 2000; steps --> 0; ) {
            it = getNext(it);
            sequence.push_back(it % 10);
        }
        // получаем ответы для каждой подпоследовательности разностей
        // в текущей последовательности:
        std::array<ll, 4> key;
        std::map<std::array<ll, 4>, ll> map;
        for (int i = isz(sequence)-1; i >= 4; i--) {
            // считаем ключ:
            for (int j = 0; j < 4; j++)
                key[j] = (sequence[i-3+j] - sequence[i-4+j]);
            // вставка значения для текущего ключа:
            map[key] = sequence[i];
        }
        // добавить ответы в глобальные суммы (по всем последовательностям)
        for (const auto &[Key, Value] : map)
            total[Key] += Value;
    }
    // ищем максимум:
    ll res = 0;
    for (const auto &[_, val] : total)
        res = std::max(res, val);
    std::cout << "part2 = " << res << std::endl;
}

main() {
    std::vector<ll> numbers;
    for (ll x; std::cin >> x; numbers.push_back(x));
    part1(numbers);
    part2(numbers);
}
