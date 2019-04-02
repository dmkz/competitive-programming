/*
    Задача: 710. Булева алгебра - 2
    
    Решение: рекурсия, строки, разбор выражений, РБНФ, O(q*len(s))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
namespace Solution {
    int p;
    std::string s;
    std::vector<bool> value(256);
    void init(std::string s_) {
        s = s_;
        p = 0;
    }
    void set(std::string s_) {
        auto f = s_.find('=');
        auto var = s_.substr(0,f);
        auto val = s_.substr(f+1);
        assert(var.size() == 1u);
        assert(val == "FALSE" || val == "TRUE");
        value[var[0]] = (val == "TRUE");
    }
    bool calc() {
        assert(p < isz(s) && 'A' <= s[p] && s[p] <= 'Z');
        std::string op;
        while (p < isz(s) && 'A' <= s[p] && s[p] <= 'Z') { op.push_back(s[p++]); }
        if (isz(op) == 1) {
            return value[op[0]];
        }
        if (op == "NOT") {
            assert(s[p++] == '(');
            bool ret = calc();
            assert(s[p++] == ')');
            return !ret;
        }
        assert(op == "AND" || op == "OR");
        assert(s[p++] == '(');
        bool ret = calc();
        while (s[p] == ',') {
            p++;
            bool temp = calc();
            ret = (op == "AND" ? ret && temp : ret || temp);
        }
        assert(s[p++] == ')');
        return ret;
    }
    bool solve() {
        p = 0;
        return calc();
    }
}

std::string& remove_spaces(std::string& s) {
    s.erase(std::remove_if(all(s), [&](char c) { return std::isspace(c); }), s.end());
    return s;
}

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    std::string s;
    std::getline(std::cin, s);
    Solution::init(remove_spaces(s));
    std::getline(std::cin, s);
    std::stringstream ss(s);
    int q, n; ss >> q >> n;
    while (q--) {
        for (int i = 0; i < n; ++i) {
            std::getline(std::cin, s);
            Solution::set(remove_spaces(s));
        }
        std::cout << (Solution::solve() ? "TRUE\n" : "FALSE\n");
    }
    return 0;
}