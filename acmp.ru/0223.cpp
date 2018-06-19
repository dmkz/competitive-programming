#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#include <cassert>
#include <functional>
#include <iostream>
#include <iomanip>

typedef __float128 Int;

std::ostream& operator<<(std::ostream& os, __float128 number) {
    auto high = (long long)(number / 1e15L);
    auto low = (long long)(number - __float128(high) * 1e15L);
    if (high == 0) {
        return os << low;
    } else {
        return os << high << std::setw(15) << std::setfill('0') << low << std::setfill(' ');
    }    
}

Int solve(const std::string& a, const std::string& b) {
    const int n = a.size();
    assert(n == (int)b.size());
    
    static Int count[1+50][1+50][1+50]; // count[len][pos1][pos2]
    
    // Начальная инициализация:
    for (int len = 0; len <= n; ++len) {
        for (int p1 = 0; p1 <= n; ++p1) {
            for (int p2 = 0; p2 <= n; ++p2) {
                if (len == 0) {
                    count[len][p1][p2] = 1;
                } else if (len == 1) {
                    count[len][p1][p2] = (p1 == n || p2 == n || a[p1] == b[p2]);
                } else {
                    count[len][p1][p2] = -1;
                }
            }
        }
    }
    
    // Ленивое ДП:
    std::function<Int(int,int,int)> get = [&](const int len, const int p1, const int p2) {
        if (count[len][p1][p2] == -1) {
            Int answ = 0;
            for (int pos = p2; pos < p2 + len; ++pos) { // a[p1] --> b[pos]
                if (a[p1] == b[pos]) {
                    const int len1 = pos-p2;
                    const int len2 = p2+len-1-pos;
                    // a[     p1+1, ...,  p1+len1] --> b[   p2,  p2+len1-1]
                    // a[p1+1+len1, ..., p1+len-1] --> b[pos+1, pos+1+len2]
                    answ += get(len1, p1+1, p2) * get(len2, p1+len1+1, pos+1);
                }
            }
            count[len][p1][p2] = answ;
        }
        return count[len][p1][p2];
    };
    
    return get(n, 0, 0);
}

int main() {
    char buf[1+50];
    scanf("%50s", buf);
    std::string a(buf);
    scanf("%50s", buf);
    std::string b(buf);
    std::cout << solve(a, b);
    return 0;
}