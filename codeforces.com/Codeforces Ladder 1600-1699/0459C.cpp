/*
	Problem: 459C. Pashmak and Buses
	
	Solution: constructive, math, number theory, O(n*d)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

bool inc(std::vector<int>& number, int base) {
	const int n = (int)number.size();
	for (int i = n-1; i >= 0; --i) {
		if (number[i] != base) {
			number[i]++;
			return true;
		} else {
			number[i] = 1;
		}
	}
	return false;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	int n, nBusses, nDays;
	std::cin >> n >> nBusses >> nDays;
	std::vector<std::vector<int>> table(n, std::vector<int>(nDays, 1));
	for (int i = 1; i < n; ++i) {
		table[i] = table[i-1];
		if (!inc(table[i], nBusses)) {
			std::cout << -1; return 0;
		}
	}
	for (int d = 0; d < nDays; ++d) {
		for (int s = 0; s < n; ++s) {
			std::cout << table[s][d] << ' ';
		}
		std::cout << "\n";
	}
	return 0;
}