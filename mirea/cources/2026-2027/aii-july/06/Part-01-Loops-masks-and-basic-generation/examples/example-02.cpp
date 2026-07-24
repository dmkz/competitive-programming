// Пример: все двоичные строки длины n через маски.
#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	// Считываем длину строки.
	int n;
	cin >> n;

	for (int mask = 0; mask < (1 << n); mask++) {
		string s;
		for (int i = 0; i < n; i++) {
			// Бит i определяет символ на позиции i.
			if ((mask >> i) & 1) s += '1';
			else s += '0';
		}
		// Печатаем строку, закодированную маской.
		cout << s << '\n';
	}

	return 0;
}