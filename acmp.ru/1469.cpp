#include <stdio.h>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

typedef long long ll;

std::vector<int> primes;

void prepare() {
// Генерация всех простых чисел при помощи решета Эратосфена:
    assert(primes.empty());
    const int n = 500; // ~sqrt(200000)
    std::vector<bool> is_prime(1+n, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i*i <= n; ++i) {
        if (!is_prime[i]) {
            continue;
        }
        for (int j = i * i; j <= n; j += i) {
            is_prime[j] = false;
        }
    }
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
}

ll solve(const std::vector<int>& arr) {
// Делим все числа на квадраты простых чисел до тех пор пока делятся
// Остальные простые множители в разложении либо отсутствуют, либо имеют степень 1
// Тогда полный квадрат можно составить из одинаковых сомножителей
    std::vector<int> numbers;
    for (auto value : arr) {
        const int limit = value;
        for (auto p : primes) {
            if (value < p || p * p > limit) {
                break;
            }
            while (value % (p * p) == 0) {
                value /= p * p;
            }
        }        
        assert(value != 0);
        numbers.push_back(value);
    }
    assert(!numbers.empty());
    std::sort(numbers.begin(), numbers.end());
    // Считаем размеры групп из одинаковых чисел:
    ll answ = 0;
    int last = numbers.front(), cnt = 0;
    for (auto it : numbers) {
        if (last == it) {
            cnt++;
        } else {
            answ += cnt * (cnt-1LL) / 2;
            last = it;
            cnt = 1;
        }
    }
    answ += cnt * (cnt-1LL) / 2;
    return answ;
}

int main() {
    prepare();
    int n; scanf("%d", &n);
    std::vector<int> arr(n);
    for (auto& it : arr) {
        scanf("%d", &it);
    }
    std::cout << solve(arr);
    return 0;
}