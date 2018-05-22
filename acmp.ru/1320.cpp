#include <iostream>
#include <vector>
#include <string>

int numberOf(std::string s, std::string sub) {
    int count = 0;
    int pos = 0;
    while (pos != -1) {
        pos = (int)s.find(sub, pos);
        if (pos != -1) {
            pos++;
            count++;
        }
    }
    return count;
}

int main() {
    std::vector<std::string> full(1+45);
    full[1] = "A";
    full[2] = "B";
    for (int i = 3; i <= 10; ++i) {
        full[i] = full[i-1] + full[i-2];
    }
    int number;
    std::string s;
    std::cin >> number >> s;
    
    if (number <= 10) {
        std::cout << numberOf(full[number], s) << std::endl;
        return 0;
    }
    
    std::vector<int> count(1+45);
    for (int i = 1; i <= 10; ++i) {
        count[i] = numberOf(full[i], s);
    }
    
    std::vector<std::string> begin(1+45), end(1+45);
    begin[10] = full[10];
    end[10] = full[10];
    begin[9] = full[9];
    end[9] = full[9];
    for (int curr = 11; curr <= number; ++curr) {
        begin[curr] = begin[curr-1].substr(0, 25);
        end[curr] = end[curr-2].substr((int)end[curr-2].size()-25, 25);
        count[curr] = count[curr-1] + count[curr-2];
        std::string mid = end[curr-1] + begin[curr-2];
        int len1 = end[curr-1].size();
        int len2 = begin[curr-2].size();
        for (int pos = 0; pos < len1 && pos+(int)s.size()-1 < len1+len2; ++pos) {
            if (pos+(int)s.size()-1 >= len1 && mid.substr(pos, (int)s.size()) == s) {
                count[curr]++;
            }
        }
    }
    std::cout << count[number] << std::endl;
    return 0;
}