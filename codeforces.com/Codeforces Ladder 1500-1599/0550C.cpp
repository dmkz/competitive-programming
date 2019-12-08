/*
    Problem: 550C. Divisibility by Eight
    Solution: brute force, math, O(n^3)
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0); cerr.tie(0);
	string s; cin >> s; int n = (int) s.size();
	// 1-digit numbers:
    for (int i = 0; i < n; ++i) {
		if ((s[i]-'0')%8==0) {
			cout << "Yes\n" << s[i]; return 0;
		}
    }
    // 2-digit numbers:
	for (int i = 0; i < n; ++i)
		for (int j = i+1; j < n; ++j) {
			int d1 = s[i] - '0';
			int d2 = s[j] - '0';
			if ((d1*10+d2)% 8 == 0) {
				cout << "Yes\n" << d1*10+d2; return 0;
			}
		}
    // 3-digit numbers:
	for (int i = 0; i < n; ++i)
		for (int j = i+1; j < n; ++j)
			for (int k = j+1; k < n; ++k) {
				int d1 = s[i]-'0', d2 = s[j] - '0', d3 = s[k] - '0';
				int num = d3 + 10* (d2 + 10 * d1);
				if (num % 8 ==0 ) {
					cout << "Yes\n" << num; return 0;
				}
			}
	cout << "No";
	return 0;
}