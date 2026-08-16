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
	int maxN, q; cin >> maxN >> q;
	// Предподсчитываем факториалы до наибольшей границы запросов.
	vector<ll> fact(maxN + 1), invFact(maxN + 1);
	fact[0] = 1;
	for (int i = 1; i <= maxN; i++)
		fact[i] = fact[i - 1] * i % mod;
	// Один обратный факториал восстанавливает все остальные движением вниз.
	invFact[maxN] = power(fact[maxN], mod - 2);
	for (int i = maxN; i >= 1; i--)
		invFact[i - 1] = invFact[i] * i % mod;
	// Для каждого запроса подставляем три предподсчитанных значения в формулу.
	while (q --> 0) {
		int n, k; cin >> n >> k;
		if (k < 0 || k > n) cout << 0 << '\n';
		else cout << fact[n] * invFact[k] % mod * invFact[n - k] % mod << '\n';
	}
}