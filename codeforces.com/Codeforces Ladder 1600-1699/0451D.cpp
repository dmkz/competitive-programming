/*
	Problem: 451D. Count Good Substrings
	
	Solution: strings, dynamic programming, prefix sums, O(n)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

typedef long long ll;

template <typename X, typename Y>
std::ostream& operator<<(std::ostream& os, const std::pair<X, Y>& p) {
	return os << p.first << ' ' << p.second;
}

std::pair<ll,ll> solve(const std::string& s) {
	const int n = (int)s.size();
	ll even = 0, odd = 0;
	std::vector<int> nOddA(n+1), nEvenA(n+1), nOddB(n+1), nEvenB(n+1);
	for (int i = n-1; i >= 0; --i) {
		nOddA[i]  =  nOddA[i+1] + (s[i] == 'a' && ((i & 1) == 1));
		nOddB[i]  =  nOddB[i+1] + (s[i] == 'b' && ((i & 1) == 1));
		nEvenA[i] = nEvenA[i+1] + (s[i] == 'a' && ((i & 1) == 0));
		nEvenB[i] = nEvenB[i+1] + (s[i] == 'b' && ((i & 1) == 0));
	}
	for (int i = 0; i < (int)s.size(); ++i) {
		int nOddFrom  = (s[i] == 'a') ?  nOddA[i] :  nOddB[i];
		int nEvenFrom = (s[i] == 'a') ? nEvenA[i] : nEvenB[i];
		if (i & 1) {
			even += nEvenFrom;
			odd  +=  nOddFrom;
		} else {
			even +=  nOddFrom;
			odd  += nEvenFrom;
		}
	}
	return std::make_pair(even, odd);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	
	std::string s;
	while (std::cin >> s) {
		std::cout << solve(s) << std::endl;
	}
	return 0;
}