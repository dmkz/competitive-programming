/*
    Задача: 1407. Производная
    
    Решение: разбор выражений, строки, O(|s|*log(|s|))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <map>
#include <string>
#include <cassert>

typedef long long ll;

namespace Solution {

    int p; std::string data; std::map<ll,ll> coeff;

    bool input() {
        p = 0; coeff.clear();
        std::getline(std::cin, data);
        return !!(std::cin);
    }
    
    bool getTerm() {
        if (p == (int)data.size()) {
            return false;
        }
        assert(data[p] == '+' || data[p] == '-' || data[p] == 'x' || ('0' <= data[p] && data[p] <= '9'));
        bool positive = !(data[p] == '-');
        p += (data[p] == '+' || data[p] == '-');
        assert(p < (int)data.size());
        assert(('0' <= data[p] && data[p] <= '9') || (data[p] == 'x'));
        ll c = ((data[p] == 'x') ? (1) : (0));
        while ('0' <= data[p] && data[p] <= '9') {
            (c *= 10) += (data[p] - '0'); ++p;
        }
        assert(p == (int)data.size() || data[p] == 'x' || data[p] == '+' || data[p] == '-');
        if (!positive) { c = -c; }
        if (p == (int)data.size() || data[p] == '+' || data[p] == '-') {
            coeff[0] += c;
            return true;
        }
        ++p;
        assert(p == (int)data.size() || data[p] == '^' || data[p] == '+' || data[p] == '-');
        if (p == (int)data.size() || data[p] == '+' || data[p] == '-') {
            coeff[1] += c;
            return true;
        }
        ++p;
        ll power = 0;
        assert(p < (int)data.size() && '0' <= data[p] && data[p] <= '9');
        while (p < (int)data.size() && '0' <= data[p] && data[p] <= '9') {
            (power *= 10) += (data[p] - '0'); ++p;
        }
        assert(p == (int)data.size() || data[p] == '+' || data[p] == '-');
        assert(power >= 0);
        coeff[power] += c;
        return true;
    }
    
    std::string solve() {
        { // normalize input string
            std::string alp = "-+^0123456789x";
            std::string temp = data;
            data.clear();
            for (auto &it : temp) { 
                if (alp.find(it) != std::string::npos) {
                    if (data.empty()) {
                        data.push_back(it);
                        continue;
                    }
                    if (it == '+' && data.back() == '+') {
                        continue;
                    }
                    data.push_back(it);
                }
            }
            for (int i = 0; i+1 < (int)data.size(); ++i) {
                assert(!(data[i] == '+' && data[i+1] == '+'));
                assert(!((data[i] == '+' || data[i] == '-') && (data[i+1] == '+' || data[i+1] == '-')));
            }
        }
        while (getTerm()) {}
        for (auto &it : coeff) {
            auto pair = it;
            coeff[pair.first] -= pair.second;
            coeff[pair.first-1] += pair.first * pair.second;
        }
        std::string answer;
        for (auto it = coeff.rbegin(); it != coeff.rend(); it++) {
            if (it->second == 0 || it->first < 0) { continue; }
            ll c = it->second;
            ll p = it->first;
            answer.push_back(c > 0 ? '+' : '-');
            if (c < 0) { c = -c; }
            if (c != 1 || (c == 1 && p == 0)) {
                answer += std::to_string(c);
            }
            if (p != 0) {
                answer += "x";
            }
            if (p <= 1) {
                continue;
            }
            answer += "^" + std::to_string(p);
        }
        if (answer.empty()) { answer = "0"; }
        if (answer[0] == '+') { answer.erase(0, 1); }
        return answer;
    }
}

int main() {
    while (Solution::input()) { std::cout << Solution::solve() << std::endl; }
    return 0;
}