#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1000000007;
ll power(ll a, ll exponent) {
	ll answ = 1;
	while (exponent > 0) {
		if (exponent % 2 == 1)
			answ = answ * a % mod;
		a = a * a % mod;
		exponent /= 2;
	}
	return answ;
}
main() {
	int n, k; cin >> n >> k;
	// Предподсчитываем факториалы для сочетания C(n - 1, k - 1).
	vector<ll> fact(n + 1), invFact(n + 1);
	fact[0] = 1;
	for (int i = 1; i <= n; i++)
		fact[i] = fact[i - 1] * i % mod;
	invFact[n] = power(fact[n], mod - 2);
	for (int i = n; i >= 1; i--)
		invFact[i - 1] = invFact[i] * i % mod;
	// Выбираем k - 1 промежутков между n единицами для знаков сложения.
	ll answ = fact[n - 1];
	answ = answ * invFact[k - 1] % mod;
	answ *= invFact[n - k];
	answ %= mod;
	cout << answ << '\n';
}