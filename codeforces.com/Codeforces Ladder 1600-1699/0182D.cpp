/*
	Problem: 182D. Common Divisors
	
	Solution: brute force, strings, math, number theory, O(n sqrt(n))
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>

int solve(const std::string& s, const std::string& t) {
	int n = (int)s.size(), m = (int)t.size(), answ = 0;
	std::string temp1(n, '?'), temp2(m, '?');
	for (int len = 1; len <= std::min(n, m); ++len) {
		if (n % len == 0 && m % len == 0) {
			for (int i = 0; i < len; ++i) {
				temp2[i] = temp1[i] = s[i];
			}
			for (int i = len; i < n; ++i) {
				temp1[i] = temp1[i-len];
			}
			for (int i = len; i < m; ++i) {
				temp2[i] = temp2[i-len];
			}
			answ += (s == temp1) && (t == temp2);
		}
	}
	return answ;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
	
	std::string s, t;
	while (std::cin >> s >> t) {
		std::cout << solve(s, t) << std::endl;
	}

	return 0;
}