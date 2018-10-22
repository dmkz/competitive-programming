/*
	Problem: 318A. Even Odds
	
	Solution: math, number theory, O(1)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
typedef long long ll;
int main() {
	ll n, k;
	while (std::cin >> n >> k) {
		ll nOdd = (n+1)/2;
		ll answ = (k <= nOdd) ? (2 * k - 1) : 2 * (k - nOdd);
		std::cout << answ << std::endl;
	}
	return 0;
}