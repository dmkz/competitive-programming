/*
	Problem: 540D. Bad Luck Island
	
	Solution: probability theory, dynamic programming, O(n^3)
	
	Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cassert>

typedef long double Real;

int main() {
	static Real prob[3][101][101][101];
	for (int a = 1; a <= 100; ++a) {
		for (int b = 1; b <= 100; ++b) {
			// Rocks beat scissors
			prob[0][a][b][0] = 1;
			prob[1][a][b][0] = 0;
			// Scissors beat papers:
			prob[1][0][a][b] = 1;
			prob[2][0][a][b] = 0;
			// Papres beat rocks:
			prob[2][a][0][b] = 1;
			prob[0][a][0][b] = 0;
		}
	}
	for (int t = 0; t < 3; ++t) {
		for (int a = 1; a <= 100; ++a) {
			for (int b = 1; b <= 100; ++b) {
				for (int c = 1; c <= 100; ++c) {
					prob[t][a][b][c] = (
						a * b * prob[t][a][b-1][c] +
						a * c * prob[t][a-1][b][c] + 
						b * c * prob[t][a][b][c-1]
					) / (a * b + a * c + b * c);
				}
			}
		}
	}
	std::cout << std::fixed << std::setprecision(9);
	int n1, n2, n3;
	while (std::cin >> n1 >> n2 >> n3) {
		for (int t = 0; t < 3; ++t) {
			std::cout << prob[t][n1][n2][n3] << ' ';
		}
		std::cout << std::endl;
	}
	return 0;
}