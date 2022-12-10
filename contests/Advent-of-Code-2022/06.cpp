#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
// 123456789012345678901234567890
// mjqjpqmgbljsphdztnvjfqwrcgsmlb
//       3210987654321
int main() {
    std::string s;
    const bool easy_task = false;
    const int sublen = easy_task ? 4 : 14;
    while(std::getline(std::cin, s)) {
        int result = -1;
        for (int i = 0; i + sublen <= isz(s); i++) {
            std::set<char> ss(s.begin()+i,s.begin()+i+sublen);
            if (isz(ss) == sublen) {
                result = i + sublen;
                break;
            }
        }
        assert(result != -1);
        std::cout << "s = " << s << std::endl;
        std::cout << "r = " << result << std::endl;
    }
}