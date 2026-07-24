// Пример: все строки из цифр 0, 1, 2 длины n через троичную запись числа.
#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	// Считываем длину строки.
	int n;
	cin >> n;

	// Всего строк ровно 3^n.
	int limit = 1;
	for (int i = 0; i < n; i++) limit *= 3;

	for (int mask = 0; mask < limit; mask++) {
		string s;
		for (int i = 0, tmp = mask; i < n; i++, tmp /= 3) {
			// Последняя цифра в троичной записи задаёт текущую позицию.
			s += char('0' + (tmp % 3));
		}
		// Печатаем строку, соответствующую числу mask.
		cout << s << '\n';
	}

	return 0;
}