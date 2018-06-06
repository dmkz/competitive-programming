#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <sstream>

typedef unsigned long long ull;
typedef long long ll;

struct UInt {
    std::vector<int> digits;
    static const int BASE = (int)1e9;
    static const int WIDTH = 9;
    
    UInt (const int value) : digits(1, value) { }    
    
    std::string to_string() const {
        std::stringstream os;
        os << digits.back();
        for (int i = (int)digits.size()-2; i >= 0; --i) {
            os << std::setw(UInt::WIDTH) << std::setfill('0') << digits[i];
        }
        return os.str();
    }
    
    UInt& normalize() {
        while (digits.size() > 1u && digits.back() == 0) {
            digits.pop_back();
        }
        return *this;
    }
    
    UInt& operator*= (const int value) {
        ll carry = 0;
        for (int i = 0; carry || i < (int)digits.size(); ++i) {
            if (i >= (int)digits.size()) {
                digits.push_back(0);
            }
            carry = carry + ll(digits[i]) * value;
            digits[i] = carry % BASE;
            carry /= BASE;
        }
        return *this;
    }
    
    std::string set_of_digits() const {
        auto s = to_string();
        std::sort(s.begin(), s.end());
        s.erase(std::unique(s.begin(), s.end()), s.end());
        return s;
    }
    
};

std::ostream& operator<<(std::ostream& os, const UInt& num) {
    return os << num.to_string();
}

int solve(std::string need) {
    //std::sort(need.begin(), need.end());
    UInt pow = 1;
    int answ = -1;
    for (int i = 0; i <= 300; ++i) {
        auto s = pow.set_of_digits();
        bool flag = true;
        for (auto c : need) {
            if (int(s.find(c)) == -1) {
                flag = false;
                break;
            }
        }
        if (flag) {
            answ = i;
            break;
        }
        pow *= 2;
    }
    return answ;
}

int main() {
    int nQ; scanf("%d", &nQ);
    while (nQ--) {
        char buf[11]; scanf("%10s", buf);
        printf("%d\n", solve(buf));
    }
    return 0;
}