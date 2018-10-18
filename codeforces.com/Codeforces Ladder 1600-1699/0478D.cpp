/*
	Problem: 478D. Red-Green Towers
	
	Solution: dynamic programming, O(n sqrt(n))
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

const int mod = (int)1e9+7;

struct State {
	int nGreen, result;
};

void update(State& a, State b) {
	a.nGreen = std::max(a.nGreen, b.nGreen);
	a.result += b.result;
	if (a.result >= mod) a.result -= mod;
}

int main() {
	int nR, nG;
	std::cin >> nR >> nG;
	int h = 1;
	while ((h+1) * (h+2) / 2 <= nR + nG) ++h;
	std::vector<State> prev(1+nR), curr(1+nR);
	curr[nR] = State{nG, 1};
	for (int lvl = 1; lvl <= h; ++lvl) {
		prev.swap(curr);
		std::fill(curr.begin(), curr.end(), State{0,0});
		for (int r = 0; r <= nR; ++r) {
			int g = prev[r].nGreen;
			int a = prev[r].result;
			if (r >= lvl) { update(curr[r-lvl], State{g, a}); }
			if (g >= lvl) { update(curr[r], State{g-lvl, a}); }
		}
	}
	int answ = 0;
	for (int r = 0; r <= nR; ++r) {
		answ += curr[r].result;
		if (answ >= mod) answ -= mod;
	}
	printf("%d\n", answ);
	return 0;
}