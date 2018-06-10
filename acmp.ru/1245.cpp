#include <iostream>
#include <string>
#include <vector>
#include <cassert>

int main() {
    std::string a, b;
    std::getline(std::cin, a);
    std::getline(std::cin, b);
    while (a.back() == 10 || a.back() == 13) a.pop_back();
    while (b.back() == 10 || b.back() == 13) b.pop_back();
    assert(a.size() == b.size());
    std::vector<int> to(256, -1), from(256, -1);
    bool flag = true;
    for (int i = 0; flag && i < (int)a.size(); ++i) {
        const char c1 = a[i], c2 = b[i];
        if (to[c1] == -1) {
            if (from[c2] != -1) {
                flag = false;
            } else {
                to[c1] = c2;
                from[c2] = c1;
            }
        } else {
            if (from[c2] == -1) {
                flag = false;
            } else {
                if (to[c1] != c2 || c1 != from[c2]) {
                    flag = false;
                }
            }
        }
    }
    printf(flag ? "YES" : "NO");
    return 0;
}