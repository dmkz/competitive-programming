/*
    Problem: 214B. Hometask
    
    Solution: strings, number theory, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

std::string get_string(std::vector<int> cnt, int nErase, int e1, int e2, int e3) {
    bool flag = true;
    while (flag && nErase > 0) {
        flag = false;
        if (cnt[e1] > 0) {
            cnt[e1]--;
            nErase--;
            flag = true;
            continue;
        }
        if (cnt[e2] > 0) {
            cnt[e2]--;
            nErase--;
            flag = true;
            continue;
        }
        if (cnt[e3] > 0) {
            cnt[e3]--;
            nErase--;
            flag = true;
            continue;
        }
    }
    if (nErase > 0 || cnt[0] == 0) { return ""; }
    std::string answ;
    for (int d = 9; d >= 0; --d) {
        answ += std::string(cnt[d], char('0' + d));
    }
    return answ;
}

std::string solve(int sum, std::vector<int> cnt) {
    std::string res;
    if (sum % 3 == 0) {
        res = get_string(cnt, 0, 0, 0, 0);
    } else if (sum % 3 == 1) {
        std::string s1 = get_string(cnt, 1, 1, 4, 7);
        std::string s2 = get_string(cnt, 2, 2, 5, 8);
        if (s1.size() < s2.size()) { s1.swap(s2); }
        s2.insert(0, std::string(s1.size()-s2.size(), '0'));
        res = std::max(s1, s2);
    } else if (sum % 3 == 2) {
        std::string s1 = get_string(cnt, 2, 1, 4, 7);
        std::string s2 = get_string(cnt, 1, 2, 5, 8);
        if (s1.size() < s2.size()) { s1.swap(s2); }
        s2.insert(0, std::string(s1.size()-s2.size(), '0'));
        res = std::max(s1, s2);
    }
    if (res == "") return "-1";
    std::reverse(res.begin(), res.end());
    while (res.size() > 1u && res.back() == '0') res.pop_back();
    std::reverse(res.begin(), res.end());
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    while (std::cin >> n) {
        int sum = 0;
        std::vector<int> cnt(10, 0);
        for (int i = 0, v; i < n; ++i) {
            std::cin >> v;
            cnt[v]++;
            sum += v;
        }
        std::cout << solve(sum, cnt) << std::endl;
    }
    return 0;
}