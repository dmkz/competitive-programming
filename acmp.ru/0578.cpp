#include <iostream>
#include <algorithm>
#include <cassert>

int main() {
    int n; std::cin >> n;
    std::string s;
    do {
        s.push_back(n % 3 + '0');
        n /= 3;
    } while (n > 0);
    std::reverse(s.begin(), s.end());    
    bool flag = true;
    while (flag) { 
        flag = false;
        for (int i = 0; i+1 < (int)s.size(); ++i) {
            if (s[i+1] != '0') {
                continue;
            }
            if (s[i] > '0' && s[i+1] == '0') {
                s[i]--;
                s[i+1] = '3';
                flag = true;
            }
        }
    }
    int pos = 0;
    while (s[pos] == '0') ++pos;
    assert(pos < (int)s.size() && s[pos] != '0');
    std::cout << s.substr(pos);
    return 0;
}