#include <bits/stdc++.h>
using namespace std;
using ll = long long;
main() {
	int n, k; cin >> n >> k;
	// Считаем произведение всех чисел от 1 до n.
	ll permutation = 1;
	for (int i = 1; i <= n; i++)
		permutation *= i;
	// В размещении выбираем только первые k множителей.
	ll arrangement = 1;
	for (int i = 0; i < k; i++)
		arrangement *= n - i;
	// После каждого шага частное остаётся целым и равно очередному сочетанию.
	ll combination = 1;
	for (int i = 1; i <= k; i++)
		combination = combination * (n - i + 1) / i;
	cout << permutation << '\n' << arrangement << '\n' << combination << '\n';
}