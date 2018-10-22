/*
	Problem: 214A. System of Equations
	
	Solution: brute force, O(sqrt(n)+sqrt(m))
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
int main() {
	int n, m;
	while (std::cin >> n >> m) {
		int cnt = 0;
		for (int a = 0; a <= m && a * a <= n; ++a) {
			for (int b = 0; a * a + b <= n && a + b * b <= m; ++b) {
				cnt += a * a + b == n && a + b * b == m;
			}
		}
		std::cout << cnt << std::endl;
	}
	return 0;
}