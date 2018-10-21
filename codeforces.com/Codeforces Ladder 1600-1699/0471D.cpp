/*
	Problem: 471D. MUH and Cube Walls
	
	Solution: sequence, math, rolling hash, O(n)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <random>

typedef unsigned long long ull;
ull BASE1 = 1, BASE2 = 1;
const ull MOD1 = (ull)4e9+7;
const ull MOD2 = (ull)4e9+9;
std::vector<ull> pow1, pow2;

ull gen_base(ull low, ull high) {
	ull SEED = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	SEED ^= ull(new char);
	std::mt19937 gen(SEED);
	std::uniform_int_distribution<ull> dist(low+2, high-2);
	ull base = dist(gen);
	return base % 2 == 0 ? base + 1 : base;
}

void prepare(const int MXLEN) {
	if (BASE1 == 1 && BASE2 == 1) {
		BASE1 = gen_base((ull)2e9, MOD1);
		BASE2 = gen_base((ull)2e9, MOD2);
		assert(BASE1 != BASE2);
	}
	if (pow1.empty() && pow2.empty()) {
		pow1.push_back(1);
		pow2.push_back(1);
	}
	while ((int)pow1.size()-1 < MXLEN) {
		pow1.push_back(pow1.back() * BASE1 % MOD1);
		pow2.push_back(pow2.back() * BASE2 % MOD2);
	}
}

struct Hash {

	std::vector<ull> data1, data2;
	
	Hash(const std::vector<int>& s) {
		const int n = (int)s.size();
		data1.push_back(0);
		data2.push_back(0);
		for (int i = 0; i < n; ++i) {
			data1.push_back((data1.back() * BASE1 + s[i] + (ull)1e9) % MOD1);
			data2.push_back((data2.back() * BASE2 + s[i] + (ull)1e9) % MOD2);
		}
	}
	
	std::pair<ull,ull> operator()(int pos, int len) const {
		ull h1 = (MOD1 + data1[pos+len] - data1[pos] * pow1[len] % MOD1) % MOD1;
		ull h2 = (MOD2 + data2[pos+len] - data2[pos] * pow2[len] % MOD2) % MOD2;
		return std::make_pair(h1,h2);
	}
	
};

int solve(std::vector<int> s, std::vector<int> t) {
	const int n = (int)s.size(), m = (int)t.size();
	prepare(n+m);
	for (int i = n-1; i > 0; --i) { s[i] -= s[i-1]; }
	for (int i = m-1; i > 0; --i) { t[i] -= t[i-1]; }
	if (m == 1) { return n; }
	Hash hs(s), ht(t);
	int answ = 0;
	for (int i = 0; i + m <= n; ++i) {
		answ += hs(i+1, m-1) == ht(1, m-1);
	}
	return answ;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	int n, m;
	while (std::cin >> n >> m) {
		std::vector<int> s(n), t(m);
		for (auto& it : s) std::cin >> it;
		for (auto& it : t) std::cin >> it;
		std::cout << solve(s, t) << std::endl;
	}
	return 0;
}