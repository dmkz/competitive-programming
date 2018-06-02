#include <iostream>
#include <map>
#include <algorithm>

int main() {
    int n, k; std::cin >> n >> k;
    std::map<int, int> pos;
    for (int i = 1; i <= n; ++i) {
        int number; 
        std::cin >> number;
        pos[number] = i;
    }
    if ((int)pos.size() < k) {
        std::cout << "NO"; return 0;
    }
    std::cout << "YES\n";
    auto it = pos.begin();
    while (k--) {
        std::cout << it->second << ' ';
        it = std::next(it);
    }
    return 0;
}