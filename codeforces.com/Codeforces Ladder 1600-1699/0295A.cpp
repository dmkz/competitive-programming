/*
	Problem: 295A. Greg and Array
	
	Solution: events, queries offline, O(n+m+k)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
typedef long long ll;
struct Query {
	int l, r; ll x;
};
int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	int nItems, nQ, nA;
	while (std::cin >> nItems >> nQ >> nA) {
		// Input array:
		std::vector<ll> arr(nItems);
		for (auto& it : arr) std::cin >> it;
		// Input queries:
		std::vector<Query> queries(nQ);
		for (auto& q : queries) {
			std::cin >> q.l >> q.r >> q.x; q.l--,q.r--;
		}
		// Input applyings:
		std::vector<ll> add(1+nQ), cnt(nQ);
		while (nA--) {
			int s, f; std::cin >> s >> f; --s, --f;
			add[s]++,add[f+1]--;
		}
		// Counting how much one query must be applied:
		ll bal = 0;
		for (int i = 0; i < nQ; ++i) {
			bal += add[i];
			cnt[i] = bal;
		}
		// Apply all queries:
		add.assign(nItems+1,0);
		for (int i = 0; i < nQ; ++i) {
			auto& q = queries[i];
			add[q.l] += q.x * cnt[i];
			add[q.r+1] -= q.x * cnt[i];
		}
		bal = 0;
		for (int i = 0; i < nItems; ++i) {
			bal += add[i];
			arr[i] += bal;
		}
		// Output answer:
		for (auto& it : arr) std::cout << it << ' ';
		std::cout << std::endl;
	}
	return 0;
}