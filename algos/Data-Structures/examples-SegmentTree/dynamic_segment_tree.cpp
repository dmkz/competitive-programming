#pragma GCC optimize("Ofast")
#include "template.hpp"
#include "numeric.hpp"

using namespace algos::numeric;
const int mod = 998244353;
using Int = IntMod<mod>;
Int getBase();

#include "segmenttreelazytraits.hpp"
#include "dynamiclazysegmenttree.hpp"
using namespace algos::DynamicLazySegmentTree;
using namespace algos::SegmentTreeLazyTraits;

Int b;
Int getBase() { return b; }

void solve() {
	int q, b_; std::cin >> q >> b_;
	b = b_;
	Int invB = Int(1) / b;
	const ll last = (ll)1e18L;
    SegmentTree<Int,Int,LazyGeomSumMul<Int,Int>> st(last+1);
	std::set<ll> set{0, last+1};
	while (q --> 0) {
		std::string s; std::cin >> s;
		if (s == "sum") {
			ll L, R;
			std::cin >> L >> R;
			auto result = st.get(L,R);
			std::cout << result << "\n";
		} else {
			assert(s == "set");
			ll k; std::cin >> k;
			auto rightBegin = set.upper_bound(k);
			auto leftBegin = std::prev(rightBegin);
			st.update(k, *rightBegin-1, binpow(invB, k-*leftBegin));
			set.insert(k);
		}
	}
}

main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	int tt; std::cin >> tt;
	while (tt --> 0)
		solve();
}
