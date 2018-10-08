/*
    Problem: 157A. Game Outcome
    
    Solution: brute force, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	int n; std::cin >> n;
	std::vector<int> row(n), col(n);
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			int a; std::cin >> a;
			row[r] += a; col[c] += a;
		}
	}
	int answ = 0;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			answ += col[c] > row[r];
		}
	}
	std::cout << answ;
	return 0;
}