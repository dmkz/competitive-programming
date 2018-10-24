/*
	Problem: 255C. Almost Arithmetical Progression
	
	Solution: sorting, two pointers, brute force, O(n^2)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

#define all(x) (x).begin(), (x).end()

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

const int MAX = (int)1e6;

int max_subseq(const vi& a, const vi& b) {
	int lt = 0, rt = 0, answ = 1;
	while (true) {
		while (rt < (int)b.size() && b[rt] <= a[lt]) {
			++rt;
		}
		if (rt == (int)b.size()) {
			break;
		}
		answ++;
		while (lt < (int)a.size() && a[lt] <= b[rt]) {
			++lt;
		}
		if (lt == (int)a.size()) {
			break;
		}
		answ++;
	}
	return answ;
}

int solve(vi arr) {
	vvi pos(1+MAX);
	for (int i = 0; i < (int)arr.size(); ++i) {
		pos[arr[i]].push_back(i);
	}
	std::sort(all(arr));
	arr.erase(std::unique(all(arr)), arr.end());
	int answ = 0;
	for (int i = 0; i < (int)arr.size(); ++i) {
		for (int j = 0; j < (int)arr.size(); ++j) {
			answ = std::max(answ, max_subseq(pos[arr[i]], pos[arr[j]]));
		}
	}
	return answ;
}


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	int n; 
	while (std::cin >> n) {
		std::vector<int> arr(n);
		for (auto& it : arr) { std::cin >> it; }
		std::cout << solve(arr) << std::endl;
	}
	return 0;
}