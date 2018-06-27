/*
    "Белоснежка и n гномов": жадный алгоритм, сортировка, O(n log(n))
*/

#include <stdio.h>
#include <algorithm>
#include <vector>

struct Pair {
    int prepare, sleep, id;
};

int main() {
    int n;
    scanf("%d", &n);
    
    std::vector<Pair> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i].id = i+1;
    }
    
    for (auto& it : arr) scanf("%d", &it.prepare);
    for (auto& it : arr) scanf("%d", &it.sleep);
    
    long long sum_prepare = 0;
    for (auto& it : arr) {
        sum_prepare += it.prepare;
    }
    
    // Первым нужно выбрать того, кто спит больше общего времени на подготовку ко сну остальных.
    // Среди кандидатов нужно выбрать того, кого дольше всего готовить ко сну.
    int min = -1;
    for (int i = 0; i < n; ++i) {
        if (arr[i].sleep + arr[i].prepare > sum_prepare && (min == -1 || arr[i].prepare > arr[min].prepare)) {
            min = i;
        }
    }
    if (min == -1) {
        printf("-1");
        return 0;
    }
    std::swap(arr[0], arr[min]);

    // Остальных необходимо отсортировать по величине "время сна" + "время подготовки" в порядке невозрастания:
    std::stable_sort(arr.begin(), arr.end(), [](const Pair& a, const Pair& b) {
        return a.sleep + a.prepare > b.sleep + b.prepare;
    });
    
    // Проход по отсортированным гномам и проверка на существование минуты отдыха:
    int t = arr[0].sleep;
    for (int i = 1; i < n; ++i) {
        t -= arr[i].prepare;
        if (t <= 0) {
            printf("-1");
            return 0;
        }
        t = std::min(arr[i].sleep, t);
    }
    
    // Вывод ответа:
    for (auto& it : arr) {
        printf("%d ", it.id);
    }
    return 0;
}