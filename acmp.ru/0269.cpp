#include <stdio.h>
#include <string>
#include <algorithm>
#include <cassert>

int main() {
    char buf[101];
    scanf("%100s", buf);
    std::string s1(buf);
    scanf("%100s", buf);
    std::string s2(buf);
    if (s1.size() > s2.size()) {
        s1.swap(s2);
    }
    const int n1 = (int)s1.size();
    const int n2 = (int)s2.size();
    s2 = std::string(n1, '0') + s2 + std::string(n1, '0');
    s1 = s1 + std::string(n2+n1, '0');
    int answ = n1+n2;
    for (int i = 0; i < n1+n2; ++i) {
        std::rotate(s1.rbegin(), s1.rbegin()+1, s1.rend());
        assert(s1.front() == '0' || s1.back() == '0');
        int len = 0;
        for (int i = 0; i < (int)s1.size(); ++i) {
            if ((s1[i]-'0')+(s2[i]-'0') > 3) {
                len = n1+n2+1;
                break;
            }
            if (s1[i] > '0' || s2[i] > '0') {
                len++;
            }
        }
        answ = std::min(answ, len);
    }
    printf("%d", answ);
    return 0;
}