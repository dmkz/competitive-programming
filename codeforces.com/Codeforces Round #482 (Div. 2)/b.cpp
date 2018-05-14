#include <bits/stdc++.h>

int solve(int changes, const std::string& s) {
    std::vector<int> count(256, 0);
    for (auto& it : s) {
        count[it]++;
    }
    
    int max = *std::max_element(count.begin(), count.end());
    
    if (max == (int)s.size() && changes == 1) {
        return max-1;
    }
    
    return std::min((int)s.size(), max + changes);
}


int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0); std::cout.tie(0);
    
    int changes; 
    std::cin >> changes;
    
    std::string a, b, c;
    std::cin >> a >> b >> c;
    
    int res1 = solve(changes, a);
    int res2 = solve(changes, b);
    int res3 = solve(changes, c);
    
    std::map<int, int> count;
    
    count[res1]++;
    count[res2]++;
    count[res3]++;
    
    auto max = std::max({res1, res2, res3});
    
    if (count[max] >= 2) {
        std::cout << "Draw";
        return 0;
    }
    
    std::map<int, std::string> user;
    
    user[res1] = "Kuro";
    user[res2] = "Shiro";
    user[res3] = "Katie";
    
    std::cout << user[max];
    
    return 0;
}