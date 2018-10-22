/*
	Problem: 281A. Word Capitalization
	
	Solution: strings, implementation, O(n)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

int main() {
	std::string s; 
	while (std::cin >> s) {
		if ('a' <= s[0] && s[0] <= 'z') {
			s[0] = char(s[0] - 'a' + 'A');
		}
		std::cout << s << std::endl;
	}
	return 0;
}