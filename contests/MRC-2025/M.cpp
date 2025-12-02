// Задача: M, Вердикт: OK, Время: 86ms, Память: 2.06Mb
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using ll = long long;
// модульная арифметика
const int mod = 998244353;
void mulby(int &x, int y) {
    x = int(x * 1LL * y % mod);
}
void addto(int &x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
}
int mul(int x, int y) {
    mulby(x, y);
    return x;
}
int binpow(int a, int n) {
    int r = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            mulby(r, a);
        }
        mulby(a, a);
        n >>= 1;
    }
    return r;
}
int inv(int a) {
    return binpow(a, mod-2);
}
const int NMAX = 100100;
const auto fact = [](){
    std::vector<int> res(NMAX+1, 1);
    for (int i = 2; i <= NMAX; i++)
        res[i] = mul(res[i-1], i);
    return res;
}();
const auto ifact = [](){
    std::vector<int> res(NMAX+1, 1);
    res[NMAX] = inv(fact[NMAX]);
    for (int i = NMAX-1; i >= 0; i--)
        res[i] = mul(res[i+1], i+1);
    return res;
}();
// решение задачи
int solve(std::string s) {
    // считаем количество каждой цифры:
    std::vector<int> cnt(10, 0), saved(10, 0);
    for (int i = 0; i < isz(s); i++)
        cnt[s[i]-'0']++;
    // если длина нечётная, то число a состоит только из цифр 9:
    // также число a не может быть пустым
    if (s.size() % 2 == 1) {
        int half = isz(s) / 2;
        if (isz(s) == 1) // пустое
            return 0;
        return (cnt[0] == half && cnt[9] == half && cnt[1] == 1);
    }
    // иначе длина чётная
    int lenA = isz(s) / 2;
    if (lenA == 1 && cnt[0] > 0)
        return 0; // число a должно быть положительным по условию
    // переберём, где произошёл переход разряда
    int answer = 0;
    for (int p = 0; p < lenA; p++) {
        // в позиции p произошёл переход разряда
        // значит в числе "a" до позиции p стояли только 9
        // а в числе "a+1" --- только 0
        // дополнительно переберём какая цифра осталась на позиции p:
        int startD = 1;
        if (p + 1 == lenA && p > 0)
            startD++; // число a не может начинаться с 0
        for (int d = startD; d <= 9; d++) {
            std::memcpy(saved.data(), cnt.data(), 10 * sizeof(cnt[0]));
            cnt[d]--; // на позиции p в числе "a+1"
            cnt[d-1]--; // на позиции p в числе "a"
            cnt[9] -= p; // до позиции p в числе "a"
            cnt[0] -= p; // до позиции p в числе "a+1"
            // оставшиеся цифры должны иметь чётное неотрицательное кол-во
            // а если есть нули, то хотя бы одна цифра должна быть ненулевой
            bool ok = true;
            for (int i = 0; i <= 9; i++)
                ok &= (cnt[i] >= 0 && cnt[i] % 2 == 0);
            if (ok) { // все цифры положительны и чётные
                int nonZeros = 0;
                for (int i = 1; i <= 9; i++)
                    nonZeros += cnt[i];
                ok &= (cnt[0] == 0 || (cnt[0] > 0 && nonZeros > 0));
                if (ok) { // нет лидирующих нулей
                    // нашли решение
                    bool was = false;
                    for (int leading = 1; leading <= 9; leading++) {
                        if (cnt[leading] >= 2) {
                            was = true;
                            cnt[leading] -= 2;
                            int curr = 1, sum = 0;
                            for (int i = 0; i <= 9; i++) {
                                mulby(curr, ifact[cnt[i]/2]);
                                sum += cnt[i]/2;
                            }
                            mulby(curr, fact[sum]);
                            addto(answer, curr);
                            cnt[leading] += 2;
                        }
                    }
                    if (!was)
                        addto(answer, 1);
                }
            }
            std::memcpy(cnt.data(), saved.data(), 10 * sizeof(cnt[0]));
        }
    }
    return answer;
}
int solve() {
    std::string s; std::cin >> s;
    return solve(s);
}
// стресс-тест для поиска контр-тестов:
void stress() {
    std::map<std::string, std::vector<int>> slow;
    for (int a = 1; a < 1000000; a++) {
        std::string s = std::to_string(a) + std::to_string(a+1);
        std::sort(all(s));
        slow[s].push_back(a);
    }
    for (const auto &[key, data] : slow) {
        int fast = solve(key);
        if (fast != isz(data)) {
            std::cout << "key = " << key << std::endl;
            std::cout << "fast = " << fast << std::endl;
            std::cout << "slow = " << data.size() << std::endl;
            std::exit(0);
        }
    }
}
main() {
    //stress();
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0)
        std::cout << solve() << "\n";
}
