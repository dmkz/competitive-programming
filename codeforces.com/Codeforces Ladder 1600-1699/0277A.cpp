/*
	Problem: 277A. Learning Languages
	
	Solution: greedy, graphs, DFS, connected components, O(n*m)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
typedef std::vector<int> vi;
int main() {
	int nP, nL;
	while (std::cin >> nP >> nL) {
		// vertices for people is {1, ..., nP}
		// vertices for languages is {nP+1, ..., nP + nL}
		// answer is number of connected components
		std::vector<vi> next(1+nP+nL);
		bool wasNonEmpty = false;
		for (int p = 1; p <= nP; ++p) {
			int k; std::cin >> k;
			wasNonEmpty = wasNonEmpty || k > 0;
			while (k--) {
				int l; std::cin >> l;
				l += nP;
				next[p].push_back(l);
				next[l].push_back(p);
			}
		}
		vi vis(1+nP+nL);
		std::function<void(int)> visit = [&](int u) {
			if (vis[u]) return;
			vis[u] = true;
			for (int v : next[u]) {
				visit(v);
			}
		};
		int answ = 0;
		for (int p = 1; p <= nP; ++p) {
			if (vis[p]) continue;
			answ++;
			visit(p);
		}
		std::cout << (wasNonEmpty ? answ-1  : answ) << std::endl;
	}
	return 0;
}