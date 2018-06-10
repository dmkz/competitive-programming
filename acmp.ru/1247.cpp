#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>

int count(const std::string& s) {
    static bool buf[256];
    buf['a'] = buf['e'] = buf['i'] = buf['o'] = buf['u'] = true;
    int answ = 0;
    for (auto c : s) {
        answ += buf[c];
    }
    return answ;
}

int main() {
    int n; scanf("%d", &n);
    std::vector<std::string> arr;
    for (int i = 0; i < n; ++i) {
        char buf[101]; 
        scanf("%100s", buf);
        arr.push_back(buf);        
    }
    std::sort(arr.begin(), arr.end(), [](const std::string& a, const std::string& b) {
        int ca = count(a), cb = count(b);
        return ca > cb || (ca == cb && a < b);
    });
    for (const auto& s : arr) {
        printf("%s\n", s.c_str());
    }
    return 0;
}