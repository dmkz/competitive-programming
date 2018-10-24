/*
	Problem: 282C. XOR and OR
	
	Solution: strings, constructive, O(n)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <cassert>

bool solve(const std::string& s, const std::string& t) {
	if (s.size() != t.size()) return false;
	int n1s = 0, n1t = 0;
	for (auto& it : s) n1s += (it == '1');
	for (auto& it : t) n1t += (it == '1');
	return (n1s == 0 && n1t == 0) || (n1s > 0 && n1t > 0);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::string s, t;
	while (std::cin >> s >> t) {
		std::cout << (solve(s,t) ? "YES" : "NO") << std::endl;
	}
	return 0;
}