#include <iostream>
#include <string>
#include <cassert>
#include <vector>

void assert_tle(bool eq) {
    if (!eq) while (true);
}

int main() {
    // [число][x]^(степень)
    std::string s;
    std::getline(std::cin, s);
    assert_tle(s.size() >= 1u);
    while (s.back() == 13 || s.back() == 10) {
        s.pop_back();
        assert_tle(!s.empty());
    }
    std::string temp;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (i == (int)s.size()-1) {
            temp.push_back(s[i]);
            break;
        }
        if (s[i] == '+' && s[i+1] == '+') {
            temp.push_back('+'); ++i;
        } else if (s[i] == '+' && s[i+1] == '-') {
            temp.push_back('-'); ++i;
        } else if (s[i] == '-' && s[i+1] == '+') {
            temp.push_back('-'); ++i;
        } else if (s[i] == '-' && s[i+1] == '-') {
            temp.push_back('-'); ++i;
        } else {
            temp.push_back(s[i]);
        }
    }
    s = temp;
    for (int i = 0; i+1 < (int)s.size(); ++i) {
        if ((s[i] == '+' || s[i] == '-') && (s[i+1] == '+' || s[i+1] == '-')) {
            while (true);
            assert(s[i] == '+' && s[i+1] == '-');
        }
    }
    if (s[0] != '-') {
        assert_tle(s[0] != '+');
        s = '+' + s;
    }
    s.push_back('?');
    assert_tle(s.size() > 2u);
    std::vector<int> x(1+10000);
    for (int p = 0; p < (int)s.size(); ) {
        if (s[p] == '?') {
            break;
        }
        assert_tle(s[p] == '+' || s[p] == '-');        
        bool positive = (s[p] == '+');
        int coeff = 0, degree = 0, j = p+1;
        while ('0' <= s[j] && s[j] <= '9') {
            (coeff *= 10) += (s[j] - '0');
            ++j;
        }
        if (j == p+1) {
            assert_tle(!((s[j-1] == '+' || s[j-1] == '-') && (s[j]=='+' || s[j] == '-')));
            assert(s[j] != '-' && s[j] != '+');
            assert_tle(s[j] == 'x');
            ++j;
            coeff = positive ? 1 : -1;
            degree = 1;
        } else if (s[j] == 'x') {
            degree = 1;
            ++j;
            coeff = positive ? coeff : -coeff;
        } else {
            degree = 0;
            coeff = positive ? coeff : -coeff;
        }
        p = j;
        if (s[p] == '^') {
            degree = 0;
            j = p+1;
            while ('0' <= s[j] && s[j] <= '9') {
                (degree *= 10) += (s[j] - '0');
                ++j;
            }
            p = j;
        }
        if (degree > 0) {
            x[degree-1] += degree * coeff;
            //std::cout << "to degree " << degree-1 << " add " << degree * coeff << std::endl;
        }
    }
    
    std::string answ;
    for (int d = 10000; d >= 0; --d) {
        if (x[d] == 0) {
            continue;
        }
        std::string temp = (x[d] > 0 ? "+" : "--");
        x[d] = std::abs(x[d]);
        if (x[d] != 1 || d == 0) {
            temp += std::to_string(x[d]);
        }
        //std::cout << temp << std::endl;
        if (d > 0) {
            temp += 'x';
            if (d > 1) {
                temp += '^' + std::to_string(d);
            }
        }
        answ += temp;
    }
    if (answ.empty()) {
        answ = "0";
    }
    if (answ[0] == '+') {
        answ = answ.substr(1);
    }
    std::cout << answ;
    return 0;
}