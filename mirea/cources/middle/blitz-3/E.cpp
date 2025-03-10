#include <bits/stdc++.h>
using namespace std;
using ld = long double;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
	cout << fixed << setprecision(6);
	ld n, k, m;
	cin >> n >> k >> m;
    // пусть x это кол-во дверей, которые мы не выбрали и ведущий не выбрал
    ld x = n - k - m;
    ld p = 1 / n; // <-- такая вероятность у выбранных нами дверей
    // вероятность, что нужная дверь не среди выбранных нами k дверей:
    ld remProbability = 1 - p * k;
    // эта вероятность распределяется по x невыбранных ни нами, ни ведущим дверей
    // как и написано в условии задачи:
    ld q = remProbability / x;
    ld ans = p * k; // это если мы оставим свой выбор таких каков он был
    if (p < q) // иначе мы можем набрать новые двери (улучшить ответ)
               // двери с вероятностью p заменяются дверями с вероятностью q
        ans += (q - p) * min(x, k);
    cout << ans << endl;
}
