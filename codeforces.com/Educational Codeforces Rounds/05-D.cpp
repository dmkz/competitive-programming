/*
    Problem: 616D. Longest k-Good Segment
    
    Solution: two pointers, O(n log(n))
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <map>
#include <cassert>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
	int n, k;
	std::cin >> n >> k;
	std::vector<int> a(n);
	for (auto & it:a) std::cin >> it;
	std::map<int,int>count;
	int l = 0, r = -1;
	int best_l = 0, best_r = -1;
	while (r < n) {
		while (r < n && (int)count.size() <= k) {
			++r;
			count[a[r]]++;
		}
		if (r - l > best_r - best_l) {
			best_l = l;
			best_r = r;
		}
		do {
			auto it = count.find(a[l]);
			it->second--;
			if (it->second == 0) {
				count.erase(it);
            }
			++l;
		} while ((int)count.size() > k);
	}
	assert(best_r != -1);
	std::cout << best_l+1 << " " << best_r << std::endl;
	return 0;
}