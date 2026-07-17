// Пример: функция Эйлера от произведения чисел на отрезке.
// Ввод: n, q, массив чисел от 1 до 300 и q запросов [l, r] в единичной индексации.
// Вывод: phi(product(a[l..r])) по модулю 10^9 + 7 для каждого запроса.

#include <iostream>
#include <vector>

using namespace std;

const int LIMIT = 300;
const long long MOD = 1000000007LL;

vector<int> build_primes() {
    vector<int> primes;
    vector<bool> is_prime(LIMIT + 1, true);
    is_prime[0] = false;
    is_prime[1] = false;

    for (int value = 2; value <= LIMIT; value++) {
        if (!is_prime[value]) {
            continue;
        }
        primes.push_back(value);
        for (int multiple = value * 2; multiple <= LIMIT; multiple += value) {
            is_prime[multiple] = false;
        }
    }
    return primes;
}

long long mod_pow(long long base, int exponent) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent & 1) {
            result = result * base % MOD;
        }
        base = base * base % MOD;
        exponent >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> primes = build_primes();
    int primes_count = static_cast<int>(primes.size());

    // factors[value][j] хранит степень j-го простого в разложении value.
    vector<vector<int>> factors(LIMIT + 1, vector<int>(primes_count, 0));
    for (int value = 1; value <= LIMIT; value++) {
        int current = value;
        for (int j = 0; j < primes_count; j++) {
            int prime = primes[j];
            while (current % prime == 0) {
                factors[value][j]++;
                current /= prime;
            }
            if (current == 1) {
                break;
            }
        }
    }

    // pref[i][j] хранит суммарную степень j-го простого среди первых i чисел.
    vector<vector<int>> pref(n + 1, vector<int>(primes_count, 0));
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i];
        for (int j = 0; j < primes_count; j++) {
            pref[i + 1][j] += factors[a[i]][j];
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        --l;
        --r;

        long long answer = 1;
        for (int j = 0; j < primes_count; j++) {
            int exponent = pref[r + 1][j] - pref[l][j];
            if (exponent == 0) {
                continue;
            }

            // phi(p^k) = p^k - p^(k-1), а затем перемножаем множители по модулю.
            long long full_power = mod_pow(primes[j], exponent);
            long long smaller_power = mod_pow(primes[j], exponent - 1);
            long long term = (full_power - smaller_power + MOD) % MOD;
            answer = answer * term % MOD;
        }

        cout << answer << '\n';
    }

    return 0;
}