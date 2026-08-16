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
	int n, m, r, c; cin >> n >> m >> r >> c;
	int maxN = n + m;
	// Предподсчитываем факториалы, чтобы быстро получать каждое сочетание.
	vector<ll> fact(maxN + 1), invFact(maxN + 1);
	fact[0] = 1;
	for (int i = 1; i <= maxN; i++) fact[i] = fact[i - 1] * i % mod;
	invFact[maxN] = power(fact[maxN], mod - 2);
	for (int i = maxN; i >= 1; i--) invFact[i - 1] = invFact[i] * i % mod;
	auto combination = [&](int all, int chosen) {
		if (chosen < 0 || chosen > all) return 0LL;
		return fact[all] * invFact[chosen] % mod * invFact[all - chosen] % mod;
	};
	// Вычитаем пути через закрытую клетку из числа всех маршрутов.
	ll allWays = combination(n + m - 2, n - 1);
	ll throughCell = combination(r + c - 2, r - 1) * combination(n + m - r - c, n - r) % mod;
	cout << (allWays - throughCell + mod) % mod << '\n';
}