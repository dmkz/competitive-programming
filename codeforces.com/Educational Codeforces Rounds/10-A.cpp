/*
    Problem: 652A. Gabriel and Caterpillar
    
    Solution: implementation, O(MAX)
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>

typedef long long ll;

int main() {
    ll start, finish, inc, dec; 
    std::cin >> start >> finish >> inc >> dec;
    dec *= -1;
    
    int h = 14;
    ll cur = start;
    int day = 0;
    bool is_day = true;
    while (day < 1000000) {
        h++;
        if (h >= 24) {
            h -= 24;
            day++;
        }
        cur += is_day ? inc : dec;
        if (cur >= finish) {
            break;
        }
        if (h == 10) {
            is_day = true;
        }
        if (h == 22) {
            is_day = false;
        }
    }
    if (day == 1000000) {
        std::cout << "-1" << std::endl;
    } else {
        std::cout << day << std::endl;
    }
    
    return 0;
}