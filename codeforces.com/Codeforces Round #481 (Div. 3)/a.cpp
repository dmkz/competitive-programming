#include <bits/stdc++.h>

int main() {
    std::map<int, int> pos;
    int n; std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int value; 
        std::cin >> value;
        pos[value] = i;
    }
    n = (int)pos.size();
    std::vector<std::pair<int, int>> answer;
    for (auto& it : pos) {
        answer.push_back({it.second, it.first});
    }
    std::sort(answer.begin(), answer.end());
    std::cout << n << std::endl;
    for (auto& it : answer) {
        std::cout << it.second << " ";
    }
    std::cout << std::endl;
    return 0;
}