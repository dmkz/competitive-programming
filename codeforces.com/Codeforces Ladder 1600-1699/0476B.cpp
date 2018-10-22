/*
	Problem: 476B. Dreamoon and WiFi
	
	Solution: probability theory, brute force, O(n*2^n)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cassert>

typedef long double Real;

bool is_same_result(const std::string& s, const std::string& t) {
	int balance = 0;
	for (auto& it : s) {
		balance += it == '+' ? +1 : -1;
	}
	for (auto& it : t) {
		balance -= it == '+' ? +1 : -1;
	}
	return balance == 0;
}

Real solve(const std::string& s, const std::string& t) {
	int nPos = 0;
	for (auto& it : t) {
		nPos += it == '?';
	}
	if (nPos == 0) {return is_same_result(s, t);}
	Real answ = 0;
	for (int mask = 0; mask < (1 << nPos); ++mask) {
		int p = 0, cnt = 0;		
		auto tmp = t;
		while (cnt < nPos) {
			while (p < (int)tmp.size() && tmp[p] != '?') ++p;
			assert(tmp[p] == '?');
			tmp[p] = ((mask >> cnt) & 1) ? '+' : '-';
			++cnt;
		}
		answ += is_same_result(tmp, s);
	}
	return answ / (1 << nPos);
}

int main() {
	std::cout << std::fixed << std::setprecision(9);
	std::string s, t;
	while (std::cin >> s >> t) {
		std::cout << solve(s, t) << std::endl;
	}
	return 0;
}