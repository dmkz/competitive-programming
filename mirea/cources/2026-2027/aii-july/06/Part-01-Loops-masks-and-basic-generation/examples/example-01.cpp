// Пример: все перестановки чисел от 1 до n через next_permutation.
#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	// Считываем размер перестановки.
	int n;
	cin >> n;

	// Стартуем с первой перестановки в лексикографическом порядке.
	vector<int> p(n);
	iota(p.begin(), p.end(), 1);
	do {
		// Печатаем текущую перестановку.
		for (int i = 0; i < n; i++) {
			if (i) cout << ' ';
			cout << p[i];
		}
		cout << '\n';
		// next_permutation переставляет элементы в следующую лексикографическую форму.
	} while (next_permutation(p.begin(), p.end()));

	return 0;
}