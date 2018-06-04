#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

bool operator<(const std::string& s, const std::string& t) {
    const int size = (int)std::max(s.size(), t.size());
    for (int i = 0; i < size; ++i) {
        int d1 = i < size-(int)s.size() ? 0 : s[i-(size-(int)s.size())]-'0';
        int d2 = i < size-(int)t.size() ? 0 : t[i-(size-(int)t.size())]-'0';
        if (d1 > d2) {
            return false;
        }
        if (d1 < d2) {
            return true;
        }
    }
    return false;
}

bool operator>(const std::string& s, const std::string& t) {
    return t < s;
}

std::string max_shift(std::string s) {
    std::string answ = "?";
    for (int i = 0; i < (int)s.size(); ++i) {
        std::rotate(s.begin(), s.begin()+1, s.end());
        if (s[0] == '0') {
            continue;
        }
        if (answ == "?" || s > answ) {
            answ = s;
        }
    }
    assert(answ != "?");
    return answ;
}

std::string min_shift(std::string s) {
    std::string answ = "?";
    for (int i = 0; i < (int)s.size(); ++i) {
        std::rotate(s.begin(), s.begin()+1, s.end());
        if (s[0] == '0') {
            continue;
        }
        if (answ == "?" || s < answ) {
            answ = s;
        }
    }
    assert(answ != "?");
    return answ;
}

std::string& operator-=(std::string& a, std::string b) {
    assert(!(a < b));
    b = std::string(a.size()-b.size(), '0') + b;
    int rem = 0;
    for (int i = (int)b.size()-1; i >= 0; --i) {
        int digit = a[i] - b[i] - rem;
        if (digit < 0) {
            digit += 10;
            rem = 1;
        } else {
            rem = 0;
        }
        a[i] = digit+'0';
    }
    assert(rem == 0);
    return a;
}

std::string& normalize(std::string& a) {
    int pos = 0;
    while (pos < (int)a.size()-1 && a[pos] == '0') {
        ++pos;
    }
    assert(a[pos] != '0' || (pos == (int)a.size()-1));
    return a = a.substr(pos);
}

int main() {
    std::string a, b;
    std::cin >> a >> b;
    a = max_shift(a);
    b = min_shift(b);
    
    int sign = 1;    
    assert(a[0] != '0');
    assert(b[0] != '0');
    
    if (!(a < b)) {
        a -= b;
    } else {
        b -= a;
        sign = -1;
        a = b;
    }
    normalize(a);
    a = (sign == -1 ? "-" : "") + a;
    assert(a != "-0");
    std::cout << a;
    return 0;
}