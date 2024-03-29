#include <vector>
#include <iostream>
#include <iomanip>
 
struct Number {
     
    static const int POW10 = (int) 1e9;
    static const int WIDTH = 9;
     
    std::vector<int> digits;
     
    Number (int num = 0) : digits(1, num) { };
     
    Number (const std::vector<int> & digits) : digits(digits) { };
     
    Number & operator += (const Number & other) {
        int carry = 0;
        for (int i = 0; i < (int) this->digits.size() || i < (int) other.digits.size() || carry; ++i) {
            int d1 = i < (int) this->digits.size() ? this->digits[i] : 0;
            int d2 = i < (int) other.digits.size() ? other.digits[i] : 0;
            carry += d1 + d2;
            int digit = carry % POW10;
            carry /= POW10;
            if (i < (int) this->digits.size()) {
                this->digits[i] = digit;
            } else {
                this->digits.push_back(digit);
            }
        }
        return *this;
    }
     
    Number & operator *= (const int val) {
        long long carry = 0;
        for (int i = 0; i < (int) this->digits.size() || carry; ++i) {
            int d1 = i < (int) this->digits.size() ? digits[i] : 0;
            carry += (long long) d1 * val;
            int digit = carry % POW10;
            carry /= POW10;
            if (i < (int) this->digits.size()) {
                digits[i] = digit;
            } else {
                digits.push_back(digit);
            }
        }
        return *this;
    }
     
    void div (const int divisor, int & rem) {
        long long carry = 0;
        for (int i = (int)digits.size()-1; i >= 0; --i) {
            carry = carry * POW10 + digits[i];
            digits[i] = carry / divisor;
            carry %= divisor;
        }
        rem = (int) carry;
        while (digits.back() == 0)
            digits.pop_back();
    }
     
    Number & operator /= (const int divisor) {
        int rem;
        div(divisor, rem);
        return *this;
    }
};
 
 
std::ostream & operator << (std::ostream & os, const Number & num) {
    os << num.digits.back();
    for (int i = (int) num.digits.size() - 2; i >= 0; --i)
        os << std::setw(Number::WIDTH) << std::setfill('0') << num.digits[i];
    return os;
}
 
Number operator / (const Number & left, const int right) {
    Number temp = left;
    int rem;
    temp.div(right, rem);
    return temp;
}
 
int operator % (const Number & left, const int right) {
    Number temp = left;
    int rem;
    temp.div(right, rem);
    return rem;
}
 
Number operator + (const Number & left, const Number & right) {
    Number temp = left;
    return temp += right;
}
 
Number operator * (const Number & left, const int right) {
    Number temp = left;
    return temp *= right;
}
 
Number operator * (const int left, const Number & right) {
    return right * left;
}
 
bool divisibleByPower2 (Number num, int n) {
    while (n--) {
        if (num % 2 == 0) {
            num /= 2;
        } else {
            return false;
        }
    }
    return true;
}
 
int main() {
//  freopen("input.txt", "rt", stdin);
//  freopen("output.txt", "wt", stdout);
     
    int n;
    scanf("%d", &n);
     
    Number curr(2);
    Number pow(1);
     
    for (int i = 2; i <= n; ++i) {
        pow *= 10;
        Number cand1 = curr + pow;
        Number cand2 = curr + 2 * pow;
         
        if (divisibleByPower2(cand1, i)) {
            curr = cand1;
        } else if (divisibleByPower2(cand2, i)) {
            curr = cand2;
        } else {
            throw 1;
        }
    }
     
    std::cout << curr;
     
     
    return 0;
}