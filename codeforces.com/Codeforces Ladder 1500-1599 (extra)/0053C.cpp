/*
    Problem: 53C. Little Frog
    
    Solution: deque, constructive, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <deque>

int main() {
    int n; std::cin >> n;
    std::deque<int> order;
    for (int i = 1; i <= n; ++i) order.push_back(i);
    while (!order.empty()) {
        std::cout << order.front() << ' ';
        order.pop_front();
        if (!order.empty()) {
            std::cout << order.back() << ' ';
            order.pop_back();
        }
    }
    return 0;
}