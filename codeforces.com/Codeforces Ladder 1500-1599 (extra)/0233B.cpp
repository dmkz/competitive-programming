/*
    Problem: 233B. Non-square Equation
    
    Solution: math, number theory, O(log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <cmath>
typedef long long ll;
typedef long double Real;
int digits_sum(ll number) {
	int ret = 0;
	do {
		ret += number % 10;
		number /= 10;
	} while (number > 0);
	return ret;
}

ll solve(ll n) {
	ll answ = n+1;
	for (ll sum = 1; sum <= 18 * 9; ++sum) {
		// x^2 + sum * x - n = 0
		// d = sum^2 - 4 * a * c
		Real d = sum * sum + Real(4) * n;
		if (d < 0) continue;
		d = std::sqrt(d);
		ll x = (ll)std::round((-sum + d) / 2);
		if (x <= 0) continue;
		if (digits_sum(x) == sum && x * (x+sum) == n) answ = std::min(answ, x);
	}
	if (answ == n+1) answ = -1;
	return answ;
}
int main() {
	//freopen("input.txt", "rt", stdin);
	ll n;
	while (std::cin >> n) {
		std::cout << solve(n) << std::endl;
	}
	
	return 0;
}