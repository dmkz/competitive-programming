#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // из условия задачи:
    // sum1 - сумма на некотором префиксе
    // sum3 - сумма на некотором суффиксе
    // найти: префикс == суффикс, из всех вариантов
    // выбрать максимальный по сумме
    
    // решение: вставляем все префиксы в set
    // перебираем все суффиксы и ищем, если ли префикс с такой суммой
    
    // читаем данные + вставляем префиксы:
    int n; cin >> n;
    vector<int> d(n);
    multiset<int64_t> prefixes;
    int64_t prefSum = 0;
    for (int i = 0; i < n; i++) {
        cin >> d[i];
        prefSum += d[i];
        prefixes.insert(prefSum);
    }
    // перебираем суффиксы + ищем префикс:
    int64_t maxSum = 0, suffSum = 0;
    for (int i = n-1; i >= 0; i--) {
        // вырезаем префикс, включающий рассматривающий элемент:
        prefixes.erase(prefixes.find(prefSum));
        // пересчитываем сумму на суффиксе и префиксе:
        suffSum += d[i];
        prefSum -= d[i];
        // ищем суффикс + обновляем ответ:
        if (auto iter = prefixes.find(suffSum); iter != prefixes.end())
            maxSum = max(maxSum, suffSum);
    }
    // выводим ответ:
    cout << maxSum << '\n';
}