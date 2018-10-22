/*
	Problem: 230A. Dragons
	
	Solution: greedy, sorting, O(n log(n))
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
struct Pair {
	int strength, bonus;
};
bool operator<(const Pair& a, const Pair& b) {
	return a.strength < b.strength || (a.strength == b.strength && a.bonus > b.bonus);
}
int main() {
	int strength, n;
	while (std::cin >> strength >> n) {
		std::vector<Pair> pairs(n);
		for (auto& p : pairs) {
			std::cin >> p.strength >> p.bonus;
		}
		std::sort(pairs.begin(), pairs.end());
		bool win = true;
		for (auto& p : pairs) {
			if (strength > p.strength) {
				strength += p.bonus;
			} else {
				win = false;
				break;
			}
		}
		std::cout << (win ? "YES\n" : "NO\n");
	}
	return 0;
}