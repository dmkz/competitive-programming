/*
    Problem: 141A. Amusing Joke
    Solution: implementation, sorting, strings
*/
#include <iostream>
#include <string>
#include <vector>
int main() {
    std::vector<int> need(256, 0);
    std::string s; std::cin >> s;
    for (auto& it : s) need[it]++;
    std::cin >> s;
    for (auto& it : s) need[it]++;
    std::cin >> s;
    for (auto& it : s) need[it]--;
    for (auto& it : need) {
        if (it != 0) {
            std::cout << "NO";
            return 0;
        }
    }
    std::cout << "YES";
    return 0;
}