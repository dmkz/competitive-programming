/*
	Problem: 231A. Team
	
	Solution: implementation, counting, O(n)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <iostream>
int main() {
	int n; 
	while (std::cin >> n) {
		int cnt = 0, a, b, c;
		while (n--) {
			std::cin >> a >> b >> c;
			cnt += (a + b + c >= 2);
		}
		std::cout << cnt << std::endl;
	}
	return 0;
}