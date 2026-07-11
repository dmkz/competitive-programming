#include <chrono>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // Качественно перемешиваем биты числа.
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        // Один случайный сдвиг на весь запуск программы.
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int main() {
    vector<long long> data = {10, 20, 10, 35, 20, 10};

    // Подключаем custom_hash и для множества, и для словаря.
    unordered_set<long long, custom_hash> used;
    unordered_map<long long, int, custom_hash> cnt;

    // Заранее выделяем место и уменьшаем среднюю плотность бакетов.
    used.reserve(1024);
    used.max_load_factor(0.25f);
    cnt.reserve(1024);
    cnt.max_load_factor(0.25f);

    // Заполняем set уникальными ключами, а map -- частотами.
    for (long long x : data) {
        used.insert(x);
        cnt[x]++;
    }

    // Проверка наличия и чтение частот.
    cout << "10 in used = " << (used.count(10) ? "yes" : "no") << '\n';
    cout << "15 in used = " << (used.count(15) ? "yes" : "no") << '\n';
    cout << "count[10] = " << cnt.find(10)->second << '\n';
    cout << "count[20] = " << cnt.find(20)->second << '\n';

    cout << "keys = {";
    bool first = true;
    for (long long x : used) {
        if (!first) cout << ',';
        cout << x;
        first = false;
    }
    cout << "}" << '\n';
}
