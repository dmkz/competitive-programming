/*
	Problem: 486C. Palindrome Transformation
	
	Solution: greedy, strings, palindrome, math, O(n)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

int dist(char a, char b) {
	if (a > b) return dist(b,a);
	return std::min(b-a, a+26-b);
}

int solve(const std::string& s, int pos) {
	const int n = (int)s.size();
	if (n - pos - 1 < pos) {
		return solve(s, n - pos - 1);
	}
	int answ = 0, lt = n, rt = 0;
	for (int i = 0, j = n-1; i <= j; ++i, --j) {
		answ += dist(s[i], s[j]);
		if (s[i] != s[j]) {
			lt = std::min(lt, i);
			rt = std::max(rt, i);
		}
	}
	int add = std::min(std::abs(pos - lt), std::abs(pos - rt)) + rt - lt;
	return (answ == 0) ? 0 : answ + add;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
	int n, pos; std::string s;
	while (std::cin >> n >> pos >> s) {
		std::cout << solve(s, pos-1) << std::endl;
	}
	return 0;
}