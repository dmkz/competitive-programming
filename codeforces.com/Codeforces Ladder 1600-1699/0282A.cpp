/*
	Problem: 282A. Bit++
	
	Solution: implementation, strings, O(n)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

int main() {
	int n;
	while (std::cin >> n) {
		int x = 0;
		while (n--) {
			std::string s; std::cin >> s;
			if (s.find('+') != std::string::npos) {
				++x;
			} else --x;
		}
		std::cout << x << std::endl;
	}
	return 0;
}