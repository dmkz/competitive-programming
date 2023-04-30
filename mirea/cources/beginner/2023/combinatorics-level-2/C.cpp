#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // функция в задаче: ксор от ксоров на всех подотрезках
    // будем считать следующим образом: в какое количество слагаемых в итоговой
    // ксор-сумме войдёт i-й элемент? i-й элемент войдёт во все подотрезки, содержащие его
    int n; cin >> n;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    int res{};
    for (int i = 0; i < n; i++) {
        int cntLeft = i+1; // число способов выбрать левую границу
        int cntRight = n - i; // число способов выбрать правую границу
        int64_t nSegments = cntLeft * 1LL * cntRight;
        if (nSegments % 2 == 1)
            res ^= a[i];
    }
    cout << res << '\n';
}
