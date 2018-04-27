#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
#include <map>
#include <vector>

std::string get_template(std::string s) {
    int count = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        if ('a' <= s[i] && s[i] <= 'a'+count) {
            continue;
        }
        for (int j = i+1; j < (int)s.size(); ++j) {
            if (s[j] == s[i]) {
                s[j] = 'a' + count;
            }
        }
        s[i] = 'a' + count;
        ++count;
    }
    return s;
}

std::map<std::string, int> templates;

void prepare() {
    templates["aa"] = 2;
    templates["aba"] = 2;
    templates["aab"] = templates["abb"] = 2;
    templates["aaa"] = 3;
    templates["abac"] = templates["abcb"] = 2;
    templates["abab"] = 3;
    templates["aabb"] = 3;
    templates["abba"] = 4;
    templates["abbb"] = templates["abaa"] = templates["aaba"] =  templates["aaab"] = 3;
    templates["aaaa"] = 5;
}

int count(std::string s) {
    s = get_template(s);
    auto it = templates.find(s);
    return (it == templates.end()) ? (0) : (it->second);
}

int main() {
    prepare();
    
    std::string number; 
    std::cin >> number;
    
    const int n = (int)number.size();
    std::vector<int> bestScore(1+n, 0);
    std::vector<std::string> bestNumber(1+n);
    
    for (int i = 1; i <= n; ++i) {
        for (int len = 2; len <= 4; ++len) {
            if (i - len >= 2 || i-len == 0) {
                int temp = bestScore[i-len] + count(number.substr(i-len, len));
                if (temp > bestScore[i]) {
                    bestScore[i] = temp;
                    bestNumber[i] = bestNumber[i-len] + "-" + number.substr(i-len, len);
                }
            }
        }
    }
    if (bestNumber[n][0] == '-') {
        bestNumber[n] = bestNumber[n].substr(1);
    }
    std::cout << bestNumber[n] << std::endl << bestScore[n] << std::endl;
    return 0;
}