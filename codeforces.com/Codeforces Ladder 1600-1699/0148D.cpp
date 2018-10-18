/*
	Problem: 148D. Bag of mice
	
	Solution: probability theory, dynamic programming, O(n^2)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

typedef long double Real;

int main() {
	static Real probability[1001][1001];
	for (int w = 1; w <= 1000; ++w) {
		probability[w][0] = 1;
		probability[w][1] = Real(w)/(w+1);
		probability[w][2] = Real(w)/(w+2) + Real(2) / (w+2) * 1 / (w+1) * probability[w-1][0];
	}
	for (int w = 1; w <= 1000; ++w) {
		for (int b = 3; b <= 1000; ++b) {
			probability[w][b] = Real(w) / (w + b) + Real(b) / (w+b) * (b-1) / (w+b-1) * (
				(b - 2) * probability[w][b-3] / (w + b - 2) +
				w * probability[w-1][b-2] / (w + b - 2)
			);
		}
	}
	int w, b; 
	std::cout << std::fixed << std::setprecision(9);
	while (std::cin >> w >> b) {
		std::cout << probability[w][b] << std::endl;
	}
	return 0;
}