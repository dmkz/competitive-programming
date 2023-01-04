//#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <bitset>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>
#include <numeric>
#include <iterator>
#include <math.h>
#include <set>
#include <functional>
#include <fstream>
#include <chrono>
#include <random>
#include <assert.h>

#define all(x) begin(x), end(x)
#define isz(x) int(size(x))
#define forx(x, n) for(int x = 0; x < n; ++x)
using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::pair;
using ll = long long;
using ull = unsigned long long;
using real = long double;
using uint = unsigned int;
using pii = std::pair<int, int>;
using pll = std::pair<ll, ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using vpii = vector<pii>;
using vvpii = vector<vpii>;
using vvvpii = vector<vvpii>;

const auto ready = []()
{
	cin.tie(0);
	std::ios_base::sync_with_stdio(false);
	return true;
}();

ull fact(ll n)
{
	ull ans = 1;
	for (ull i = 1; i <= n; ++i)
		ans *= i;
	return ans;
}

vector<ll> solved(ll n, ll k)
{
	vector<ll> vec(n);
	std::iota(all(vec), 1);
	vector<ll> sum(n, 0LL);
	int i = 0;
	do
	{
		forx(i, n) sum[i] += vec[i];
		std::next_permutation(all(vec));
		++i;
	} while (i < k);
	return sum;
}

vector<ll> solve(ll n, ll k, vector<ll> vec)
{
	vector<ll> sum(n, 0LL);
	int i = 0;
	do
	{
		forx(i, n) sum[i] += vec[i];
		std::next_permutation(all(vec));
		++i;
	} while (i < k);
	return sum;
}

vector<ll> full(ll n, ll k, vector<ll> vec)
{
	ll sum = std::accumulate(all(vec), 0LL);
	vector<ll> ans(n);
	forx(i, n) ans[i] = (k / n) * sum;
	return ans;
}

vector<ll> solveTask(ll n, ll k, vector<ll> vec)
{
	if (n <= 2)
	{
		return solve(n, k, vec);
	}
	else if (n <= 20)
	{
		vector<ll> ans(n);
		ll prev = fact(n - 1);
		ll tmp = k;
		int ptr = 0;
		while (tmp >= prev)
		{
			vector<ll> prev_vec;
			for (int i = 0; i < n; ++i)
			{
				if (i != ptr)
				{
					prev_vec.push_back(vec[i]);
				}
			}
			auto it = full(n - 1, prev, prev_vec);
			ans[0] += vec[ptr] * prev;
			for (int i = 1; i < n; ++i) ans[i] += it[i - 1];
			++ptr;
			tmp -= prev;
		}
		if (tmp > 0)
		{
			vector<ll> prev_vec;
			for (int i = 0; i < n; ++i)
			{
				if (i != ptr)
				{
					prev_vec.push_back(vec[i]);
				}
			}
			auto it = solveTask(n - 1, tmp, prev_vec);
			ans[0] += vec[ptr] * tmp;
			for (int i = 1; i < n; ++i) ans[i] += it[i - 1];
		}
		return ans;
	}
}


int main()
{

	int t;
	cin >> t;
	while (t--)
	{
		ll n, k;
		ll test = 20;
		cin >> n >> k;
		int save_n = n;
		if (n > test)
		{
			n = test;
		}
		vector<ll> vec(n);
		std::iota(all(vec), 1);
		auto ans = solveTask(n, k, vec);
		//cout << "Before\n";
		//for (auto &el : ans) cout << el << " ";
		//cout << "\n";
		if (save_n > n)
		{
			std::reverse(all(ans));
			ll diff = save_n - n;
			for (int i = 0; i < n; ++i) ans[i] += k * diff;
			for (int i = n; i < save_n; ++i) ans.push_back(k * (save_n - i));
			std::reverse(all(ans));
		}
		for (auto &el : ans) cout << el << " ";
		cout << "\n";
	}
	return 0;
}