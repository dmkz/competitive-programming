#include <iostream>
#include <vector>
#include <string>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> s(n); 
    for (auto& it : s) {
        std::cin >> it;
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (s[i].size() > s[j].size()) {
                s[i].swap(s[j]);
            }
            if ((int)s[j].find(s[i]) == -1) {
                std::cout << "NO";
                return 0;
            }
        }
    }
    std::cout << "YES\n";
    for (auto& it : s) {
        std::cout << it << '\n';
    }
    return 0;
}