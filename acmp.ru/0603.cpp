/*
    "Поиск": поиск подстроки в тексте, O(n*m)
*/

#include <stdio.h>
#include <string>
#include <cassert>
#include <vector>

int main() {
    char buf[2001] = {}, c;
    scanf("%100[^\n]%c", buf, &c); 
    assert(c == '\n');
    
    std::string s(buf);
    
    int pos = 0;
    while (scanf("%c", &c) != EOF) {
        buf[pos++] = c;
    }
    buf[pos] = '\0';
    
    std::string t(buf);
    
    std::vector<int> finded;
    for (pos = (int)t.size() - 1; pos >= 0; --pos) {
        int i = 0, j = pos;
        bool flag = true;
        while (i < (int)s.size() && j < (int)t.size()) {
            if ((int)std::isspace(s[i]) ^ (int)std::isspace(t[j])) {
                flag = false;
                break;
            }
            while (i < (int)s.size() && std::isspace(s[i])) ++i;
            while (j < (int)t.size() && std::isspace(t[j])) ++j;
            if (i == (int)s.size()) break;
            if (j == (int)t.size()) { flag = false; break; }
            if (std::tolower(s[i]) != std::tolower(t[j])) { 
                flag = false; break; 
            }
            ++i, ++j;
        }
        if (flag) {
            finded.push_back(pos);
        }
    }
    
    for (auto& it : finded) {
        t.insert(t.begin()+it, '@');
    }
    
    printf("%s", t.c_str());
    
    return 0;
}