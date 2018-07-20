/*
    Problem: 628B. New Skateboard

    Solution: combinatorics, math, O(n)

    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

typedef long long ll;

int main() {
    char buf[300000+1]; 
    scanf("%300000s", buf);
    std::string s(buf);
    ll answer = (s[0] -'0') % 4 == 0;
    for (int i = 1; i < (int)s.size(); ++i) {
        int cur = (s[i-1]-'0') * 10 + s[i]-'0';
        if (cur % 4 == 0) {
            answer += i;
        }
        answer += (s[i] - '0') % 4 == 0;
    }
    std::cout << answer << std::endl;
    return 0;
}