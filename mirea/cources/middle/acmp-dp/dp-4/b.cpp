#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pli = pair<ll, int>;
int main() {
    // читаем времена, приводим их к целым числам [0, 12*60*60-1] и сортируем
    int n; scanf("%d", &n);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        int hh, mm, ss;
        scanf("%d:%d:%d", &hh, &mm, &ss);
        hh--;
        a[i] = ss + 60 * (mm + 60 * hh);
    }
    sort(a.begin(), a.end());
    // ответ равен одному из a[i], поэтому переберём каждый вариант
    // и быстро посчитаем ответ для него, используя суммы на префиксе и суффиксе
    ll suffSum = accumulate(a.begin(), a.end(), 0LL);
    ll prefSum = 0;
    pli best(1e18L, -1);
    for (int i = 0; i < n; i++) {
        // устанавливаем на всех часах время a[i] и считаем ответ
        prefSum += a[i];
        suffSum -= a[i];
        // на суффиксе мы крутим до 12*3600, а потом до a[i]
        // на префиксе сразу крутим до a[i]
        ll curr = i * 1LL * a[i] - prefSum;
        curr += (n-i) * (12*3600LL+a[i]) - suffSum;
        best = min(best, pli(curr, a[i]));
    }
    // выводим ответ
    int result = best.second;
    int ss = result % 60;
    int mm = result / 60 % 60;
    int hh = result / 3600;
    printf("%1d:%02d:%02d", 1+hh, mm, ss);
}
