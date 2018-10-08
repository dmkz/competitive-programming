/*
    Problem: 514B. Han Solo and Lazer Gun
    
    Solution: geometry, math, std::set, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <set>
int gcd(int a, int b) {
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	return b == 0 ? a : gcd(b, a % b);
}
struct Pair {
	int x, y;
	
	Pair(int x_ = 0, int y_ = 1) : x(x_), y(y_) {
		if (x < 0) { x = -x; y = -y; }
		if (x == 0) { y = 1; }
		if (y == 0) { x = 1; }
		int d = gcd(x,y);
		x /= d;
		y /= d;
	}
};

bool operator<(const Pair& a, const Pair& b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

int main() {
//	freopen("input.txt", "rt", stdin);
	int n, xc, yc;
	std::cin >> n >> xc >> yc;
	std::set<Pair> set;
	while (n--) {
		int x, y; std::cin >> x >> y;
		set.insert(Pair(x-xc,y-yc));
	}
	std::cout << set.size();
	return 0;
}