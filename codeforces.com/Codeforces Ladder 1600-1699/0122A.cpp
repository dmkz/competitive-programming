/*
	Problem: 122A. Lucky Division
	
	Solution: brute force, number theory, O(n*log(n))
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

bool is_lucky(int n) {
	do {
		if (!(n % 10 == 4 || n % 10 == 7)) return false;
		n /= 10;
	} while (n > 0);
	return true;
}

int main() {
	int n;
	while (std::cin >> n) {
		bool flag = false;
		for (int div = 4; !flag && div <= n; ++div) {
			if (is_lucky(div) && n % div == 0) {
				flag = true;
			}
		}
		std::cout << (flag ? "YES\n" : "NO\n");
	}
	return 0;
}