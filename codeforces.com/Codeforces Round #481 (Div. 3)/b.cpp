#include <bits/stdc++.h>

int main() {
    int n; std::cin >> n;
    std::string s; std::cin >> s;
    s += '?';
    int answer = 0;
    for (int i = 0; i < n;) {
        int j = i;
        while (s[j] == 'x') ++j;
        answer += std::max(j - i - 2, 0);
        i = j+1;
    }
    std::cout << answer << std::endl;
    return 0;
}