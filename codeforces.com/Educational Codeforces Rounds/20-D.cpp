/*
    Problem: 803D. Magazine Ad
    
    Solution: binary search, greedy, O(log(n)*n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

const int INF = (int)1e9+1;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int wrap(const std::string& s, int begin, int after, int width) {
    int last = -2;
    for (int i = begin; i < after; ++i) {
        if (i-begin >= width) {
            return last+1;
        }
        if (s[i] == '-') {
            last = i;
        }
        
    }
    return after;
}

bool solve(const std::string& s, int limit, int width) {
    int n = (int)s.size();
    int p = 0, count = 0;
    do {
        ++count;
        p = wrap(s, p, n, width);
        if (p == -1) {
            return false;
        }
    } while (p < n);
    return count <= limit;
}

int main() {
    int k; char c; scanf("%d%c", &k, &c); assert(c == '\n');
    std::vector<char> buf(1+1000*1000,'?');
    scanf("%1000000[^\n]", &buf[0]);
    std::string s(&buf[0]);
    for (auto& it : s) {
        if (it == ' ') it = '-';
    }
    int low = 0, high = (int)s.size();
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (solve(s, k, mid)) {
            high = mid;
        } else {
            low = mid;
        }
    }
    std::cout << high;
    return 0;
}