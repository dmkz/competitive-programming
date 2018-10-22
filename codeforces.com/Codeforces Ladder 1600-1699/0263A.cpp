/*
	Problem: 263A. Beautiful Matrix
	
	Solution: implementation, geometry, O(n^2)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <cstdlib>
int main() {
	int answ = 0;
	for (int r = 1; r <= 5; ++r) {
		for (int c = 1; c <= 5; ++c) {
			int v; std::cin >> v;
			if (v == 1) {
				answ = std::abs(r-3) + std::abs(c-3);
			}
		}
	}
	std::cout << answ << std::endl;
	return 0;
}
