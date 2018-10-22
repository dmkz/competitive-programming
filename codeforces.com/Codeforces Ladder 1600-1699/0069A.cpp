/*
	Problem: 69A. Young Physicist
	
	Solution: implementation, geometry, O(n)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
int main() {
	int n;
	while (std::cin >> n) {
		int sx = 0, sy = 0, sz = 0,x,y,z;
		while (n--) {
			std::cin >> x >> y >> z;
			sx += x, sy += y, sz += z;
		}
		std::cout << (sx == 0 && sy == 0 && sz == 0 ? "YES\n" : "NO\n");
	}
	return 0;
}