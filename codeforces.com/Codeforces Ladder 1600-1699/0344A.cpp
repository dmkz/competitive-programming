/*
	Problem: 344A. Magnets
	
	Solution: strings, implementation, O(n)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
int main() {
	int n;
	while (std::cin >> n) {
		int answ = 0;
		std::string group = "";
		while (n--) {
			std::string s; std::cin >> s;
			if (group.empty() || group.back() == s.front()) {
				group = s;
				++answ;
			} else {
				group.insert(group.end(), s.begin(), s.end());
			}
		}
		std::cout << answ << std::endl;
	}
	return 0;
}