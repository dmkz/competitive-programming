/*
	Problem: 236A. Boy or Girl
	
	Solution: strings, counting sort, O(n)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
int main() {
	std::string s; 
	while (std::cin >> s) {
		std::vector<int> in(256);
		for (auto& it : s) in[it] = 1;
		int sum = std::accumulate(in.begin(), in.end(), 0);
		std::cout << (sum % 2 == 1 ? "IGNORE HIM!\n" : "CHAT WITH HER!\n");
	}
	return 0;
}