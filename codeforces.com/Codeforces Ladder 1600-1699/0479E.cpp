/*
	Problem: 479E. Riding in a Lift
	
	Solution: dynamic programming, O(n*k)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

const int mod = (int)1e9+7;

void addmod(int& a, int b) {
	a += b;
	if (a >= mod) a -= mod;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	int n, a, b, k;
	while (std::cin >> n >> a >> b >> k) {
		std::vector<int> prev(1+n+1), curr(1+n+1), add(1+n+1);
		curr[a] = 1;
		for (int i = 1; i <= k; ++i) {
			prev.swap(curr);
			std::fill(add.begin(), add.end(), 0);
			std::fill(curr.begin(), curr.end(), 0);
			for (int f = 1; f <= n; ++f) {
				int dist = std::abs(f-b);
				// f - l < dist
				// f - dist < l
				int left = std::max(1, f + 1 - dist);
				if (left < f) {
					addmod(add[left], prev[f]);
					addmod(add[f], mod-prev[f]);
				}
				// r - f < dist
				// r < dist + f
				int right = std::min(f + dist - 1, n);
				if (right > f) {
					addmod(add[f+1], prev[f]);
					addmod(add[right+1], mod-prev[f]);
				}
			}
			int balance = 0;
			for (int f = 1; f <= n; ++f) {
				addmod(balance, add[f]);
				curr[f] = balance;
			}
		}
		int res = 0;
		for (int f = 1; f <= n; ++f) {
			addmod(res, curr[f]);
		}
		std::cout << res << std::endl;
	}
	return 0;
}