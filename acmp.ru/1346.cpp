#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

int main() {
    std::string s; std::cin >> s;
    const int n = (int)s.size();
    if (n <= 4) {
        std::cout << s;
        return 0;
    }
    
    std::vector<std::vector<std::string>> min(n, std::vector<std::string>(n));
    for (int len = 1; len <= 4; ++len) {
        for (int i = 0; i+len-1 < n; ++i) {
            min[i][i+len-1] = s.substr(i, len);
        }
    }
    
    for (int len = 5; len <= n; ++len) {
        for (int l1 = 0; l1+len-1 < n; ++l1) {
            const int r2 = l1+len-1;
            min[l1][r2] = s.substr(l1, len);
            for (int r1 = l1; r1 < r2; ++r1) {
                auto temp = s.substr(l1, r1-l1+1);
                const int len2 = r1-l1+1;
                if (len % len2 == 0) {
                    bool flag = true;
                    for (int i = l1; i+len2-1 <= r2; i += len2) {
                        if (s.substr(i, len2) != temp) {
                            flag = false;
                            break;
                        }
                    }
                    if (flag) {
                        temp = std::to_string(len / len2) +"("+min[l1][r1]+")";
                        if (temp.size() < min[l1][r2].size()) {
                            min[l1][r2] = temp;
                        }
                    }
                }
            }
            for (int r1 = l1; r1 < r2; ++r1) {
                if (min[l1][r1].size()+min[r1+1][r2].size() < min[l1][r2].size()) {
                    min[l1][r2] = min[l1][r1] + min[r1+1][r2];
                }
            }
        }
    }
    printf("%s", min[0][n-1].c_str());
    return 0;
}