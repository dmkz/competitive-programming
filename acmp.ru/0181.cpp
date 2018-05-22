#pragma GCC diagnostic ignored "-Wunused-result"
#include <stdio.h>
#include <bits/stdc++.h>

int main() {
    
    std::string alp = "NSWEUD";
    
    std::vector<std::vector<int>> coeff(6, std::vector<int>(6, 0));
    for (int i = 0; i < 6; ++i) {
        char buf[101] = {}; 
        scanf("%100[^\n]", buf);
        char c;
        scanf("%c", &c);
        assert(c == '\n');
        std::string s(buf);
        for (auto& it : s) {
            int pos = int(std::find(alp.begin(), alp.end(), it)-alp.begin());
            coeff[i][pos]++;
        }
        //scanf("\n");
    }
    char c = '?'; int level;
    scanf(" %c %d", &c, &level);
    
    std::vector<std::vector<int>> count(level+1, std::vector<int>(6, -1));
    std::function<int(int, int)> get = [&](const int level, const int pos) {
        if (level == 1) {
            return 1;
        }
        if (count[level][pos] == -1) {
            int answ = 1;
            for (int i = 0; i < 6; ++i) {
                answ += coeff[pos][i] * get(level-1, i);
            }
            count[level][pos] = answ;
        }
        return count[level][pos];
    };
    printf("%d\n", get(level, alp.find(c)));
    return 0;
}