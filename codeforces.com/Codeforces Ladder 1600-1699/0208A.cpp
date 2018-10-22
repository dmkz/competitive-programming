/*
	Problem: 208A. Dubstep
	
	Solution: strings, implementation, O(n)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
#include <vector>
int main() {
	std::string s;
	while (std::cin >> s) {
		std::vector<std::string> words;
		s = "WUB" + s + "WUB";
		while (!s.empty()) {
			while (!s.empty() && s.substr(0, 3) == "WUB") {
				s = s.substr(3);
			}
			if (s.empty()) break;
			auto p = s.find("WUB");
			assert(p != std::string::npos);
			words.push_back(s.substr(0, p));
			s = s.substr(p);
		}
		for (auto& it : words) std::cout << it << ' ';
		std::cout << std::endl;
	}
	return 0;
}