/*
    Problem: 439A. Devu, the Singer and Churu, the Joker
    
    Solution: greedy, implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
	int n,d; std::cin >> n >> d;
	std::vector<int> arr(n);
	for (auto& it : arr) std::cin >> it;
	int s = std::accumulate(arr.begin(), arr.end(), 0);
	if (d - s < 0 || (d - s) / 10 < n-1) {
		std::cout << -1; return 0;
	}
	std::cout << (d - s) / 5;
	return 0;
}