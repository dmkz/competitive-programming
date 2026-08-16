#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1000000007;
ll power(ll a, ll exponent) {
	ll answ = 1;
	while (exponent > 0) {
		if (exponent % 2 == 1) answ = answ * a % mod;
		a = a * a % mod;
		exponent /= 2;
	}
	return answ;
}
main() {
	int n, k; cin >> n >> k;
	int limit = min(k, n - k);
	// Последовательно домножаем числитель и делим на очередной знаменатель.
	ll answ = 1;
	for (int i = 1; i <= limit; i++) {
		answ = answ * (n - i + 1) % mod;
		answ = answ * power(i, mod - 2) % mod;
	}
	cout << answ << '\n';
}