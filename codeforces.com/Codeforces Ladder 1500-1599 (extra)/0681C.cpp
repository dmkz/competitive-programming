/*
    Problem: 681C. Heap Operations
    
    Solution: heap, data structures, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>

const int UNDEF = (int)1e9+1;

struct Pair {

    std::string command; int value;
    
    Pair(const std::string& s, int val = UNDEF) : command(s), value(val) { }    
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    std::vector<Pair> answ;
    std::priority_queue<int, std::vector<int>, std::greater<int>> queue;
    int n; std::cin >> n;
    while (n--) {
        std::string command; std::cin >> command;
        if (command == "insert") {
            int x; std::cin >> x; queue.push(x);
            answ.push_back(Pair("insert", x));
        } else if (command == "removeMin") {
            if (queue.empty()) {
                answ.push_back(Pair("insert", 1));
                queue.push(1);
            }
            answ.push_back(Pair("removeMin", UNDEF));
            queue.pop();
        } else if (command == "getMin") {
            int x; std::cin >> x;
            while (!queue.empty() && queue.top() < x) {
                answ.push_back(Pair("removeMin", UNDEF));
                queue.pop();
            }
            if (queue.empty() || queue.top() > x) {
                answ.push_back(Pair("insert", x));
                queue.push(x);
            }
            answ.push_back(Pair("getMin", x));
        }
    }
    std::cout << (int)answ.size() << "\n";
    for (auto& p : answ) {
        std::cout << p.command;
        if (p.value != UNDEF) {
            std::cout << " " << p.value;
        }
        std::cout << "\n";
    }
    return 0;
}