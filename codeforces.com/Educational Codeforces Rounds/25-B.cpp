/*
    Problem: 825B. Five-In-a-Row
    
    Solution: brute force, implementation, O(n^2*k)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include <queue>

typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<std::string> vs;

void yes() { printf("YES"); std::exit(0); }
void no() { printf("NO"); std::exit(0); }

int main() {
    vs arr(20, std::string(20, 'O'));
    for (int i = 5; i < 5 + 10; ++i) {
        std::cin >> arr[i];
        arr[i] = std::string(5, 'O') + arr[i] + std::string(5, 'O');
    }
    for (int i = 5; i < 15; ++i) {
        for (int j = 5; j < 15; ++j) {
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if (di == 0 && dj == 0) continue;
                    int cntX = 0, cntD = 0;
                    for (int k = 0; k < 5; ++k) {
                        cntX += arr[i+k*di][j+k*dj] == 'X';
                        cntD += arr[i+k*di][j+k*dj] == '.';
                    }
                    if (cntX == 4 && cntD == 1) yes();
                }
            }            
        }
    }
    no();
    return 0;
}