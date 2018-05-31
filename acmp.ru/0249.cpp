#include <iostream>
#include <vector>
#include <algorithm>

bool correct(char l, char r) {
    return (l == '(' && r == ')') || (l == '[' && r == ']') || (l == '{' && r == '}');
}

int main() {
    std::string s; std::cin >> s;
    const int n = (int)s.size();
    std::vector<std::vector<int>> min(n, std::vector<int>(n)); // min[left][right]
    // min[i][i] = 1;
    // min[i][i+1] = 0 if "()" of "[]" of "{}", else 2
    
    for (int i = 0; i < n; ++i) {
        min[i][i] = 1;
    }
    
    for (int i = 0; i+1 < n; ++i) {
        auto sub = s.substr(i, 2);
        min[i][i+1] = correct(s[i], s[i+1]) ? 0 : 2;
    }
    
    for (int len = 3; len <= n; ++len) {
        for (int pos = 0; pos+len-1 < n; ++pos) {
            const int l1 = pos, r2 = pos+len-1;
            // Вариант S = '(' + C + ')':
            min[l1][r2] = min[l1+1][r2-1] + (correct(s[l1], s[r2]) ? 0 : 2);
            // Варианты S = S1 + S2:
            for (int r1 = l1; r1 < r2; ++r1) {
                const int l2 = r1+1;
                min[l1][r2] = std::min(min[l1][r2], min[l1][r1]+min[l2][r2]);
            }
        }
    }
    std::cout << min[0][n-1];
    return 0;
}