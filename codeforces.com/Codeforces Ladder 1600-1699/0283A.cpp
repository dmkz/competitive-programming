/*
	Problem: 283A. Cows and Sequence
	
	Solution: stack, implementation, O(n)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cassert>

typedef long long ll;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout << std::fixed << std::setprecision(6);
	
	int nQ; ll sum = 0; std::cin >> nQ;
	std::vector<ll> set{0}; std::vector<ll> add{0};
	while (nQ--) {
		int t; std::cin >> t;
		if (t == 1) {
			// increase items:
			int cnt, extra; std::cin >> cnt >> extra;
			assert(cnt != 0);
			assert(cnt-1 < (int)add.size());
			add[cnt-1] += extra;
			sum += ll(cnt) * extra;
		} else if (t == 2) {
			// push back item:
			int x; std::cin >> x;
			add.push_back(0);
			set.push_back(x);
			sum += x;
		} else if (t == 3) {
			// pop back item:
			assert(add.size() >= 2u);
			int last = (int)add.size()-1;
			sum -= add[last] + set[last];
			add[last-1] += add[last];
			set.pop_back();
			add.pop_back();
		}
		std::cout << sum / (long double)(set.size()) << "\n";
	}
	return 0;
}