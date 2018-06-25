#include <stdio.h>
#include <iostream>
#include <vector>

void rec(int base, std::vector<int>& digits, std::vector<int>& count, std::vector<int>& answ) {
    if (!answ.empty()) return;
    if ((int)digits.size() == base) {
        if (digits.back() != count[0]) {
            return;
        }
        for (int i = 0; i < (int)digits.size()-1; ++i) {
            if (digits[i] != count[i+1]) {
                return;
            }   
        }
        answ = digits;
        return;
    }
    for (int digit = (int)digits.empty(); digit < base; ++digit) {
        if (answ.empty()) {
            digits.push_back(digit);
            count[digit]++;
            rec(base, digits, count, answ);
            count[digit]--;
            digits.pop_back();
        }
    }
}

void precalc(int s, int t) {
    for (int base = s; base <= t; ++base) {
        std::vector<int> count(base), digits, answ;
        rec(base, digits, count, answ);
        std::cout << "base = " << base << ":";
        if (answ.empty()) answ.push_back(-1);
        for (auto& it : answ) {
            std::cout << ' ' << it;
        }
        std::cout << std::endl;
    }
    std::exit(0);
}

std::vector<int> solve(int base) {
    std::vector<int> answ;
    if (base == 2 || base == 3 || base == 6) {
        answ.push_back(-1);
        return answ;
    }
    if (base == 4) {
        return {2,1,0,1};
    }
    if (base == 5) {
        return {1,2,0,0,2};
    }
    answ.assign(base, 0);
    answ.back() = base-4;
    answ[base-5]++;
    answ[0] = 2;
    answ[1] = 1;
    return answ;
}

int main() {
    //precalc(2, 10);
    int base; scanf("%d", &base);
    for (auto it : solve(base)) {
        printf("%d\n", it);
    }
    return 0;
}