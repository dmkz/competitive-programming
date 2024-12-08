#include <bits/stdc++.h>
using namespace std;
// функция, находящая суммы всех подпоследовательностей:
vector<int> findSums(const vector<int> &a, const int mod) {
    vector<int> sums;
    for (int mask = 0; mask < (1 << a.size()); mask++) {
        int currSum = 0;
        for (int i = 0; i < (int)a.size(); i++)
            if ((mask >> i) & 1) {
                currSum += a[i];
                currSum %= mod;
            }
        sums.push_back(currSum);
    }
    return sums;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // чтение данных:
    int n, mod; cin >> n >> mod;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    // находим суммы в левой и правой половинах:
    const int mid = n / 2;
    auto S1 = findSums(vector(a.begin(), a.begin()+mid), mod);
    auto S2 = findSums(vector(a.begin()+mid, a.end()), mod);
    // сортируем левую половину:
    sort(S1.begin(), S1.end());
    // для каждой суммы правой половины ищем наилучшую левую:
    int answ{};
    for (int s2 : S2) {
        // есть переполнение:
        answ = max(answ, (s2 + S1.back()) % mod);
        // нет переполнения: s2 + s1 < m ==> s1 < m - s2
        auto iter = lower_bound(S1.begin(), S1.end(), mod - s2);
        if (iter != S1.begin()) {
            int s1 = *(--iter);
            answ = max(answ, (s2 + s1) % mod);
        }
    }
    // выводим ответ:
    cout << answ << endl;
}
