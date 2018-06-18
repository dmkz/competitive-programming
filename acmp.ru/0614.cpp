/*
    Двумерное динамическое программирование
    
    Фиксируем для текущей позиции ближайшую к ней открывающую и ближайшую к ней закрывающую скобку
    
    count[pos][balance] = количество непустых правильных скобочных подпоследовательностей на полуинтервале [pos, n) с балансом balance 
    
    Динамика справа-налево. Переход:
    
        count[pos][balance] = (balance ? 0 : 1) + count[rOpen][balance+1] + count[rClos][balance-1]
        
    Ответом будет являться count[rOpen][1]+1
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

struct UInt {
    static const int POW10 = (int)1e9;
    static const int WIDTH = 9;
    
    std::vector<int> digits;
    
    UInt(int number = 0) : digits(1, number) { }
    
    UInt& operator +=(const UInt& other) {
        const int s1 = this->digits.size();
        const int s2 = other.digits.size();
        int carry = 0;
        for (int i = 0; i < s1 || i < s2 || carry; ++i) {
            if (i >= s1) {
                digits.push_back(0);
            }
            carry += digits[i] + (i < s2 ? other.digits[i] : 0);
            digits[i] = carry % POW10;
            carry /= POW10;
        }
        return normalize();
    }
    
    UInt& normalize() {
        while ((int)digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
        return *this;
    }
};

std::ostream& operator<<(std::ostream& os, const UInt& num) {
    os << num.digits.back();
    for (int i = (int)num.digits.size()-2; i >= 0; --i) {
        os << std::setw(UInt::WIDTH) << std::setfill('0') << num.digits[i];
    }
    return os << std::setfill(' ');
}

int main() {
    std::string s; 
    std::cin >> s;
    const int n = s.size();
    
    std::vector<std::vector<UInt>> count(n+1, std::vector<UInt>(1+n));
    
    int rOpen = n, rClos = n;
    for (int pos = n-1; pos >= 0; --pos) {
        count[pos][0] = 1;
        count[pos][0] += count[rOpen][1];
        for (int balance = 1; balance < n; ++balance) {
            count[pos][balance] += count[rOpen][balance+1];
            count[pos][balance] += count[rClos][balance-1];
        }
        if (s[pos] == ')') {
            rClos = pos;
        } else {
            rOpen = pos;
        }
    }
    
    auto answ = count[rOpen][1];
    std::cout << (answ += 1);
    
    return 0;
}