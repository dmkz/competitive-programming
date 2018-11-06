/*
    Problem: 350A. Strange Addition
    
    Solution: math, number theory, constructive, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

typedef std::vector<int> vi;

vi solve(vi arr) {
    if (arr.size() == 1u) {
        return arr;
    }
    int v000 = -1, v001 = -1, v010 = -1, v011 = -1, v100 = -1;
    for (auto& it : arr) {
        auto s = std::to_string(it);
        while (s.size() < 3u) {
            s.insert(s.begin(), '0');
        }
        for (int i = 0; i < 3; ++i) {
            if (s[i] != '0') {
                s[i] = '1';
            }
        }
        if (s == "000") {v000 = it;}
        if (s == "001") {v001 = it;}
        if (s == "010") {v010 = it;}
        if (s == "011") {v011 = it;}
        if (s == "100") {v100 = it;}
    }
    vi answ;
    if (v000 != -1) {
        answ.push_back(v000);
    }
    if (v100 != -1) {
        answ.push_back(v100);
    }
    if (v001 != -1 && v010 != -1) {
        answ.push_back(v001);
        answ.push_back(v010);
    } else if (v001 != -1 && (v000 != -1 || v100 != -1)) {
        answ.push_back(v001);
    } else if (v010 != -1 && (v000 != -1 || v100 != -1)) {
        answ.push_back(v010);
    } else if (v011 != -1) {
        answ.push_back(v011);
    }
    if (answ.empty()) {
        answ.push_back(arr[0]);
    }
    return answ;
}

int main() {
    int n;
    while (std::cin >> n) {
        vi arr(n);
        for (auto& it : arr) {
            std::cin >> it;
        }
        vi answ = solve(arr);
        std::cout << answ.size() << "\n";
        for (auto& it : answ) {
            std::cout << it << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}