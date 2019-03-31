/*
    Задача: 709. Булева алгебра
    
    Решение: рекурсия, разбор выражений, РБНФ, O(q * len(s))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define isz(s) (int)(s).size()

std::string remove_spaces(std::string s) {
    std::string ret;
    for (auto it : s) {
        if (std::isspace(it)) { continue; }
        ret.push_back(it);
    }
    return ret;
}

namespace Solution {

    std::string s;
    int pos = 0;
    std::vector<bool> var(256);
    
    void init(std::string s_) {
        s = s_, pos = 0;
        var.assign(256, false);
    }
    
    void set(std::string s_) {
        auto p = s_.find('=');
        assert(p != std::string::npos);
        auto v = s_.substr(0,p);
        s_ = s_.substr(p+1);
        assert(v.size() == 1u);
        assert(s_ == "TRUE" || s_ == "FALSE");
        var[v[0]] = (s_ == "TRUE");
    }
    
    bool calc() {
        assert('A' <= s[pos] && s[pos] <= 'Z');
        std::string op;
        while (pos < isz(s) && 'A' <= s[pos] && s[pos] <= 'Z') {
            op.push_back(s[pos++]);
        }
        if (op == "NOT") {
            assert(s[pos++]=='(');
            bool res = calc();
            assert(s[pos++]==')');
            return !res;
        }
        if (op == "AND" || op == "OR") {
            assert(s[pos++]=='(');
            bool fi = calc();
            assert(s[pos++]==',');
            bool se = calc();
            assert(s[pos++]==')');
            return op == "AND" ? fi && se : fi || se;
        }
        assert(isz(op) == 1);
        return var[op[0]];
    }
    
    std::string solve() {
        pos = 0;
        bool res = calc();
        return res ? "TRUE" : "FALSE";
    }
    
}

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    std::string s;
    std::getline(std::cin, s);
    Solution::init(remove_spaces(s));
    int q, n; std::cin >> q >> n;
    std::getline(std::cin, s);
    s = remove_spaces(s);
    assert(s.empty());
    while (q--) {
        for (int i = 0; i < n; ++i) {
            std::getline(std::cin, s);
            Solution::set(remove_spaces(s));
        }
        std::cout << Solution::solve() << "\n";
    }
    return 0;
}