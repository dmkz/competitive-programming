// Пример: все двоичные строки длины n через bitset.
// Подходит, если заранее известно, что n не превосходит 24.
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
			// bitset<24>(mask)[i] читает i-й бит маски.
			s += char('0' + bitset<24>(mask)[i]);
		}
		// Печатаем строку, закодированную маской.
		cout << s << '\n';
	}

	return 0;
}