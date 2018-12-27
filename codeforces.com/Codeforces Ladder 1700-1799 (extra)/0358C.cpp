/*
    Problem: 358C. Dima and Containers
    
    Solution: sorting, stack, queue, deque, O(n * log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

typedef std::vector<int> vi;
typedef std::vector<std::string> vs;

struct Pair {
    int value, id;
};

bool operator<(const Pair& a, const Pair& b) {
    return a.value < b.value || (a.value == b.value && a.id < b.id);
}

vs solve(vi arr) {
    arr.push_back(0);
    vs answ(arr.size());
    std::vector<Pair> tmp;
    int prev = -1;
    for (int id = 0; id < (int)arr.size(); ++id) {
        if (arr[id] == 0) {
            tmp.clear();
            for (int i = id-1; i > prev; --i) {
                tmp.push_back(Pair{arr[i], i});
            }
            std::sort(tmp.begin(), tmp.end());
            std::vector<std::string> tmpStr;
            if (!tmp.empty()) {
                answ[tmp.back().id] = "pushStack";
                tmpStr.push_back("popStack");
                tmp.pop_back();
            }
            if (!tmp.empty()) {
                answ[tmp.back().id] = "pushQueue";
                tmpStr.push_back("popQueue");
                tmp.pop_back();
            }
            if (!tmp.empty()) {
                answ[tmp.back().id] = "pushBack";
                tmpStr.push_back("popBack");
                tmp.pop_back();
            }
            while (!tmp.empty()) {
                answ[tmp.back().id] = "pushFront";
                tmp.pop_back();
            }
            prev = id;
            auto &ret = answ[id];
            ret = std::to_string(tmpStr.size());
            for (auto it : tmpStr) {
                ret += " " + it;
            }
        }
    }
    return answ;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        vi arr(n); 
        for (auto &it : arr) { std::cin >> it; }
        vs answ = solve(arr);
        for (int i = 0; i < n; ++i) {
            const auto& it = answ[i];
            std::cout << it << '\n';
        }
        std::cout << std::endl;
    }
    return 0;
}