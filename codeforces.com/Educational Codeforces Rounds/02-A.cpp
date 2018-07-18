/*
    Problem: 600A. Extract Numbers

    Solution: strings analysis, integer conversion, implementation, O(n)
*/

#include <stdio.h>
#include <vector>
#include <string>

bool is_int(std::string s) {
    if (s == "") return false;
    if (s == "0") return true;
    if (!('1'<=s[0] && s[0] <= '9')) return false;
    for (auto c : s) {
        if (!('0' <= c && c <= '9')) return false;
    }
    return true;
}

int main() {
    std::vector<char> buffer(100000+1);
    scanf("%100000[^\n]", &buffer[0]);
    std::string s(&buffer[0]);
    for (auto & c : s) {
        if (c == ';') c = ',';
    }
    s.push_back(',');
    
    std::vector<std::string> words;
    int prev = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] == ',') {
            words.push_back(s.substr(prev, i-prev));
            prev = i+1;
        }
    }
    
    std::string ints, other;
    for (auto & w : words) {
        if (is_int(w)) {
            ints.insert(ints.end(), w.begin(), w.end());
            ints.push_back(',');
        } else {
            other.insert(other.end(), w.begin(), w.end());
            other.push_back(',');
        }
    }
        
    if (ints == "") {
        printf("-\n");
    } else {
        ints.pop_back();
        printf("\"%s\"\n", ints.c_str());
    }
    
    if (other == "") {
        printf("-");
    } else {
        other.pop_back();
        printf("\"%s\"", other.c_str());
    }
    
    return 0;
}