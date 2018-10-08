/*
    Problem: 471B. MUH and Important Things
    
    Solution: sorting, greedy, O(n * log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
struct Pair { int val, id; };
int main() {
	int n; std::cin >> n;
	std::vector<Pair> arr, c, b;
	for (int i = 1, v; i <= n; ++i) {
		std::cin >> v; arr.push_back(Pair{v, i});
	}
	std::sort(arr.begin(), arr.end(), [](const Pair& a, const Pair& b) {
		return a.val < b.val || (a.val == b.val && a.id < b.id);
	});
	for (int i = 1; c.empty() && i < n; ++i) {
		if (arr[i].val == arr[i-1].val) {
			if (b.empty()) { b = arr; std::swap(b[i], b[i-1]); }
			else if (c.empty()) { c = arr; std::swap(c[i], c[i-1]); }
		}
	}
	if (c.empty()) { std::cout << "NO"; return 0; }
	std::cout << "YES\n";
	for (auto& it : arr) { std::cout << it.id << ' '; } 
	std::cout << "\n";
	for (auto& it : b) { std::cout << it.id << ' '; } 
	std::cout << "\n";
	for (auto& it : c) { std::cout << it.id << ' '; } 
	return 0;
}