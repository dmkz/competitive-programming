/*
    Problem: 103B. Cthulhu
    
    Solution: graphs, dfs, cycles, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdlib>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
void answer(bool eq) {
	std::cout << (eq ? "FHTAGN!" : "NO") << std::endl;
	std::exit(0);
}
int main() {
	//freopen("input.txt", "rt", stdin);
	// Input:
	int n, m;
	std::cin >> n >> m;
	vvi edges(1+n);
	while (m--) {
		int u, v; std::cin >> u >> v;
		edges[u].push_back(v);
		edges[v].push_back(u);
	}
	// Find one simple cycle:
	vi color(1+n), cycle, from(1+n); int nCycles = 0;
	std::function<void(int,int)> find_cycle = [&](int u, int p) {
		color[u] = 1;
		for (int v : edges[u]) {
			if (v == p) continue;
			if (color[v] == 0) {
				from[v] = u;
				find_cycle(v,u);
			} else if (color[v] == 1) {
				vi temp{v};
				for (int t = u; t != v; t = from[t]) {
					temp.push_back(t);
				}
				++nCycles;
				if (nCycles == 2) answer(false);
				cycle = temp;
			}
		}
		color[u] = 2;
	};
	find_cycle(1, 0);
	if (nCycles == 0) answer(false);
	for (int u = 1; u <= n; ++u) {
		if (color[u] != 2) answer(false);
	}
	answer(true);
	return 0;
}