#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::string s; std::cin >> s;
    const int n = (int)s.size();
    if (n == 0) {
        return 0;
    }
    std::vector<std::vector<std::string>> min(n, std::vector<std::string>(n));
    
    for (int i = 0; i < n; ++i) {
        if (s[i] == '[' || s[i] == ']') {
            min[i][i] = "[]";
        }
        if (s[i] == '(' || s[i] == ')') {
            min[i][i] = "()";
        }
    }
    for (int i = 0; i+1 < n; ++i) {
        const int j = i+1;
        if (s[i] == '[' && s[j] == ']') {
            min[i][j] = "[]";
        } else if (s[i] == '(' && s[j] == ')') {
            min[i][j] = "()";
        } else {
            min[i][j] = min[i][i]+min[j][j];
        }
    }
    
    for (int len = 3; len <= n; ++len) {
        for (int pos = 0; pos+len-1 < n; ++pos) {
            const int i1 = pos, j2 = pos+len-1;
            if ((s[i1] == '[' && s[j2] == ']') || (s[i1] == '(' && s[j2] == ')')) {
                min[i1][j2] = s[i1]+min[i1+1][j2-1] + s[j2];
            } else {
                min[i1][j2] = min[i1][i1]+min[i1+1][j2-1]+min[j2][j2];
            }
            for (int j1 = i1; j1 < j2; ++j1) {
                const int i2 = j1+1;
                if (min[i1][j1].size()+min[i2][j2].size() < min[i1][j2].size()) {
                    min[i1][j2] = min[i1][j1]+min[i2][j2];
                }
            }
        }
    }
    printf("%s", min[0][n-1].c_str());
    return 0;
}