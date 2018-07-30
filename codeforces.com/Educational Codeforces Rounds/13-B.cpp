/*
    Problem: 678B. The Same Calendar
    
    Solution: calendar, implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>

typedef long long ll;

std::vector<int> days_per_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct Record {
    int year, month, day, id;
    
    Record next() const {
        Record ret = *this;
        (ret.id += 1) %= 7;
        ret.day++;
        int need_to_add = month == 1 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
        if (ret.day == days_per_month[month] + need_to_add) {
            ret.day = 0;
            ret.month++;
            if (ret.month >= 12) {
                ret.month = 0;
                ret.year++;
            }
        }
        return ret;
    }
};


int main() {
    int year; std::cin >> year;
    Record cur{year, 0, 0, 0};
    std::vector<std::string> arr;
    while (true) {
        if (cur.year - year >= (int)arr.size()) {
            if (arr.size() > 1u && arr.back() == arr.front()) {
                std::cout << cur.year - 1 << std::endl;
                return 0;
            }
            arr.push_back("");
        }
        arr[cur.year - year].push_back(char('0'+cur.id));
        cur = cur.next();
    } 
    return 0;
}