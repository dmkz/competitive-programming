#include <iostream>
#include <functional>
#include <string>
#include <vector>

int count(const std::string& s) {
    if (s == "Bull") return 50;
    if (s[0] == 'D') {
        return 2 * count(s.substr(1));
    }
    if (s[0] == 'T') {
        return 3 * count(s.substr(1));
    }
    return std::stoi(s);
}

int main() {
    std::vector<std::string> steps{"25", "Bull"};
    for (int i = 1; i <= 20; ++i) {
        auto s = std::to_string(i);
        steps.push_back(s);
        steps.push_back("D"+s);
        steps.push_back("T"+s);
    }
    
    std::vector<std::vector<std::string>> answer;
    
    std::function<void(int,int,int,std::vector<std::string>&)> go = 
    [&](int n, int cur, int need, std::vector<std::string>& temp) {
        if ((int)temp.size() >= n || cur >= need) { 
            if (cur == need && (temp.back()[0] == 'D' || temp.back()[0] == 'B')) {
                answer.push_back(temp);
            }
            return;
        }
        for (auto& s : steps) {
            if (cur+count(s) <= need) {
                temp.push_back(s);
                go(n, cur+count(s), need, temp);
                temp.pop_back();
            }
        }
    };
    int cost; std::cin >> cost;
    std::vector<std::string> temp;
    go(3, 0, cost, temp);
    std::cout << answer.size() << "\n";
    for (auto& row : answer) {
        for (auto &it : row) {
            std::cout << it << ' ';
        }
        std::cout << '\n';
    }
    
    return 0;
}