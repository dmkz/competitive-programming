#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include <set>

typedef long long ll;

// Взятие модуля от числа num по основанию b:
int mod(ll num, int b) {
    return num >= 0 ? num % b : b - (-num) % b;
}

// Генерация массива случайных чисел из диапазона [0, 1e9]:
std::vector<int> gen(int n) {
    std::vector<int> arr(n);
    for (auto& it : arr) {
        it = mod(1LL * std::rand() * std::rand() * std::rand(), 1000000001);
        assert(0 <= it && it <= 1000000000);
    }
    return arr;
}

// Проверка выполнимости свойства задачи на каждом префиксе:
double count_diff(const std::vector<int>& arr) {
    std::set<int> diff;
    double min = 100;
    for (int r = 1; r < (int)arr.size(); ++r) {
        for (int l = r-1; l >= 0; --l) {
            diff.insert(std::abs(arr[r]-arr[l]));
        }
        min = std::min(min, 1.0 * diff.size() / ((r+1) * r / 2));
    }
    assert(min >= 0.95);
    return min;
}

int main() {
    std::srand(124070620);
    int n;
    scanf("%d", &n);
    for (auto it : gen(n)) {
        printf("%d ", it);
    }   
    
    return 0;
}