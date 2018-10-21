/*
	Problem: 264B. Good Sequences
	
	Solution: number theory, dynamic programming, O(n sqrt(n))
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

const int AMAX = (int)1e5, INF = (int)1e9+1;

std::vector<int> prime_divisors(int n) {
	std::vector<int> answ;
	for (int i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			answ.push_back(i);
			while (n % i == 0) n /= i;
		}
	}
	if (n > 1) { answ.push_back(n); }
	for (int i = (int)answ.size()-2; i >= 0; --i) {
		if (answ[i] > answ[i+1]) {
			std::swap(answ[i], answ[i+1]);
		} else break;
	}
	return answ;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	int n;
	while (std::cin >> n) {
		std::vector<int> mxLen(1+AMAX, 0);
		while (n--) {
			int a, max = 1; std::cin >> a;
			if (a == 1) {
				mxLen[a] = 1;
			} else {
				auto pd = prime_divisors(a);
				for (int d : pd) {
					max = std::max(max, mxLen[d]+1);
				}
				for (int d : pd) {
					mxLen[d] = std::max(max, mxLen[d]);
				}
			}
		}
		std::cout << *std::max_element(mxLen.begin(), mxLen.end()) << std::endl;
	}
	return 0;
}