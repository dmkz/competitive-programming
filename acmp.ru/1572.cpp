#include <stdio.h>
#include <vector>
#include <string>
#include <cmath>

int sum(const std::string& s) {
    int answ = 0;
    for (auto c : s) {
        answ += c - '0';
    }
    return answ;
}

int same(const std::string& a, const std::string& b) {
    int answ = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        answ += (a[i] == '1' && '1' == b[i]);
    }
    return answ;
}

int main() {
    std::vector<std::string> mask = {
        "110101011", "001100010", "100100101", 
        "101010100", "010110010", "110010011",
        "001011011", "101001000", "110111011", "110110100"
    };
    
    char buf[100000+1];
    scanf("%100000s", buf);
    std::string a(buf);
    scanf("%100000s", buf);
    std::string b(buf);
    
    int sum_a = 0;
    for (auto it : a) {
        sum_a += sum(mask[it-'0']);
    }
    
    int sum_b = 0;
    for (auto it : b) {
        sum_b += sum(mask[it-'0']);
    }
    
    int same = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        same += ::same(mask[a[i]-'0'], mask[b[i]-'0']);
    }
    
    printf("%d", std::min(sum_a, sum_b) - same + std::abs(sum_a-sum_b));
    return 0;
}