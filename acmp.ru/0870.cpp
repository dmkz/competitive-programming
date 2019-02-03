/*
    Задача: 870. URL Validator
    
    Решение: разбор выражений, синтаксический парсер, строки, O(n)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <cassert>
#include <vector>

std::string solve(const std::string& s) {
    int p = 0;
    auto isDomain = [&](const std::string& t) {
        if (t.size() < 2u || t.size() > 3u) { return false; }
        for (auto it : t) {
            if (!(('A' <= it && it <= 'Z') || ('a' <= it && it <= 'z'))) {
                return false;
            }
        }
        return true;
    };
    auto isIp = [&](const std::vector<std::string>& v) {
        if (v.size() != 4u) { return false; }
        for (const auto& it : v) {
            if (it.size() > 1u && it.front() == '0') { return false; }
            for (auto jt : it) {
                if (jt < '0' || jt > '9') {  return false; }
            }
            if (it.size() == 0u || it.size() > 3u || std::stoi(it) < 0 || std::stoi(it) > 255) {
                return false;
            }
        }
        return true;
    };
    auto readWord = [&]() {
        std::string ret;
        while (p < (int)s.size() && (
            ('0' <= s[p] && s[p] <= '9') ||
            ('a' <= s[p] && s[p] <= 'z') ||
            ('A' <= s[p] && s[p] <= 'Z') ||
            (s[p] == '_'))) 
        {
            ret.push_back(s[p++]);
        }
        return ret;
    };
    auto readHost = [&](){
        std::vector<std::string> words;
        if (p < (int)s.size() && s[p] == '.') { return false; }
        while (!(p == (int)s.size() || s[p] == ':' || s[p] == '/')) {
            if (s[p] == '.') { ++p; }
            auto word = readWord();
            if (word.empty()) { return false; }
            words.push_back(word);
        }
        if (words.size() == 1u) { return true; }
        return ((words.size() > 0u && isDomain(words.back())) || isIp(words));
    };
    if (!readHost()) { return "NO"; }
    if (!(p == (int)s.size() || s[p] == ':' || s[p] == '/')) {
        return "NO";
    }
    auto readPort = [&]() {
        if (p == (int)s.size() || s[p] != ':') {
            return true;
        }
        assert(s[p] == ':');
        ++p;
        std::string it;
        while (p < (int)s.size() && '0' <= s[p] && s[p] <= '9') {
            it.push_back(s[p++]);
        }
        if (it.size() > 1u && it.front() == '0') {
            return false;
        }
        for (auto jt : it) {
            if (jt < '0' || jt > '9') {
                return false;
            }
        }
        if (it.size() == 0u || it.size() > 5u || std::stoi(it) < 0 || std::stoi(it) > 65535) {
            return false;
        }
        return true;
    };
    if (!readPort()) { return "NO"; }
    auto readPath = [&]() {
        if (p == (int)s.size() || s[p] != '/') {
            return true;
        }
        assert(s[p] == '/');
        while (p < (int)s.size() && s[p] == '/') {
            ++p;
            auto word = readWord();
            if (word.empty()) { return true; }
        }
        while (p < (int)s.size() && s[p] == '.') {
            ++p;
            auto word = readWord();
            if (word.empty()) { return false; }
        }
        return true;
    };
    if (!readPath()) { return "NO"; }
    return p == (int)s.size() ? "YES" : "NO";
}

int main() {
    std::string s;
    while (std::getline(std::cin, s)) {
        if (s.size() >= 7u && s.substr(0,7) == "http://") {
            s.erase(0, 7);
        }
        std::cout << solve(s) << "\n";
    }
    return 0;
}