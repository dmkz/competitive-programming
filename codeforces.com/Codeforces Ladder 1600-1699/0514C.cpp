/*
	Problem: 514C. Watto and Mechanism
	
	Solution: rolling hash, binary search, strings, O((n + 3 * q) * log(n))
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <functional>
#include <cassert>

typedef unsigned long long ull;

const ull mod = (ull(1) << 61)-1;
ull base = 1;

ull gen_base(ull low, ull high) {
	ull SEED = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	SEED ^= ull(new char);
	std::mt19937 gen(SEED);
	assert(low+2 <= high-2);
	std::uniform_int_distribution<ull> dist(low+2, high-2);
	ull ret = dist(gen);
	return (ret & 1) ? ret : ret+1;
}

ull add(ull a, ull b) {
	return (a += b) >= mod ? a - mod : a;
}

ull sub(ull a, ull b) {
	return (a -= b) >= mod ? a + mod : a;
}

ull mul(ull a, ull b) {
	ull l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
	ull l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
	ull ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
	ret = (ret & mod) + (ret >> 61);
	ret = (ret & mod) + (ret >> 61);
	return ret-1;
}

ull pow(int n) {
	static std::vector<ull> pow = {1};
	while ((int)pow.size()-1 < n) {
		pow.push_back(mul(pow.back(), base));
	}
	return pow[n];
}

struct Hash {
	
	std::vector<ull> data;
	
	Hash(const std::string& s) {
		const int n = (int)s.size();
		data.push_back(0);
		for (int i = 0; i < n; ++i) {
			data.push_back(add(mul(data.back(), base), s[i]));
		}
	}
	
	ull operator()(const int pos, const int len) const {
		return sub(data[pos+len], mul(data[pos], pow(len)));
	}	
};

int main() {
	base = gen_base(1e9, 2e9);
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	// Calculate hashes from string in set:
	int n, q;
	std::cin >> n >> q;
	std::vector<ull> hashes;
	for (int i = 0; i < n; ++i) {
		std::string s; std::cin >> s;
		Hash hash(s);
		hashes.push_back(hash(0, (int)s.size()));
	}
	std::sort(hashes.begin(), hashes.end());
	hashes.erase(std::unique(hashes.begin(), hashes.end()), hashes.end());
	// Answering to queries:
	while (q--) {
		std::string s; std::cin >> s;
		Hash hash(s);
		bool flag = false;
		const int len = (int)s.size();
		for (int p = 0; !flag && p < len; ++p) {
			for (char c = 'a'; !flag && c <= 'c'; ++c) {
				if (c == s[p]) continue;
				ull tmp = add(mul(add(mul(hash(0, p), base), c), pow(len-(p+1))), hash(p+1,len-(p+1)));
				flag = std::binary_search(hashes.begin(), hashes.end(), tmp);
			}
		}
		std::cout << (flag ? "YES\n" : "NO\n");
	}
	return 0;
}