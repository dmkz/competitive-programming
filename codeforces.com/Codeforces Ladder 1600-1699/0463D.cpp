/*
	Problem: 463D. Gargari and Permutations
	
	Solution: dynamic programming, topological sorting, graphs, O(k*n^2)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <functional>

#define all(x) (x).begin(), (x).end()

int main() {
	// Input graph:
	int n, k; scanf("%d %d", &n, &k);
	std::vector<std::vector<int>> next(1+n);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			next[i].push_back(j);
		}
	}
	for (int i = 0; i < k; ++i) {
		std::vector<int> arr(n);
		for (auto& it : arr) { scanf("%d", &it); }
		std::vector<int> list;
		for (int j = n-1; j >= 0; --j) {
			int u = arr[j];
			std::vector<int> tmp;
			std::set_intersection(all(list), all(next[u]), std::back_inserter(tmp));
			next[u] = tmp;
			list.push_back(u);
			for (int t = (int)list.size()-2; t >= 0; --t) {
				if (list[t] > list[t+1]) {
					std::swap(list[t], list[t+1]);
				} else break;
			}
		}
	}
	// topological sorting:
	std::vector<int> order, visited(1+n, false);
	std::function<void(int)> topsort = [&](int u) {
		if (visited[u]) return;
		visited[u] = true;
		for (auto& it : next[u]) {
			topsort(it);
		}
		order.push_back(u);
	};
	for (int u = 1; u <= n; ++u) { topsort(u); }
	std::reverse(all(order));
	// dynamic programming over topological order:
	std::vector<int> mxLen(1+n, 1);
	for (int u : order) {
		for (int v : next[u]) {
			mxLen[v] = std::max(mxLen[v], mxLen[u]+1);
		}
	}
	// output answer:
	std::cout << *std::max_element(all(mxLen)) << std::endl;
	return 0;
}