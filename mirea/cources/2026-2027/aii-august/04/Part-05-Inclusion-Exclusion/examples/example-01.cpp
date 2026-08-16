#include <bits/stdc++.h>
using namespace std;
using ll = long long;
main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int s; cin >> s;
	int limit = 1 << s;
	// intersection[mask] хранит размер пересечения множеств, выбранных маской.
	vector<ll> intersection(limit);
	for (int mask = 1; mask < limit; mask++)
		cin >> intersection[mask];
	// Нечётное число свойств даёт плюс, чётное число свойств даёт минус.
	ll answ = 0;
	for (int mask = 1; mask < limit; mask++) {
		if (__builtin_popcount(mask) % 2 == 1)
			answ += intersection[mask];
		else answ -= intersection[mask];
	}
	cout << answ << '\n';
}