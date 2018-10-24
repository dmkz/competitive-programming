/*
	Problem: 75C. Modified GCD
	
	Solution: binary search, number theory, divisors, O(n log(n))
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

#define all(x) (x).begin(), (x).end()

typedef std::vector<int> vi;

vi divisors(int n) {
	vi answ{1}, stack{n};
	for (int i = 2; i * i <= n; ++i) {
		int j = n / i;
		if (j * i == n) {
			answ.push_back(i);
			stack.push_back(j);
		}
	}
	while (!stack.empty() && stack.back() == answ.back()) {
		stack.pop_back();
	}
	while (!stack.empty()) {
		answ.push_back(stack.back());
		stack.pop_back();
	}
	return answ;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
	int a, b;
	std::cin >> a >> b;
	auto divA = divisors(a);
	auto divB = divisors(b);
	vi same;
	std::set_intersection(all(divA), all(divB),std::back_inserter(same));
	int nQ; std::cin >> nQ;
	while (nQ--) {
		int low, high;
		std::cin >> low >> high;
		int pos = int(std::upper_bound(all(same), high)-same.begin())-1;
		assert(0 <= pos && pos < (int)same.size());
		int div = same[pos];
		int answ = (low <= div && div <= high) ? div : -1;
		std::cout << answ << "\n";
	}
	return 0;
}