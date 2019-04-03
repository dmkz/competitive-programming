/*
    Задача: 612. Подстрока
    
    Решение: конструктив, динамическое программирование, двумерное дп, O(n^2)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
bool can_remove(char fi, char se) {
    return std::tolower(fi) == std::tolower(se) && fi != se;
}
std::string split(std::string s) {
    std::string ret;
    for (auto it : s) {
        if (ret.empty()) {
            ret.push_back(it);
        } else if (can_remove(ret.back(), it)) {
            ret.pop_back();
        } else {
            ret.push_back(it);
        }
    }
    return ret;
}

struct Record {
    int len, i, j;
};

bool operator<(const Record& a, const Record& b) {
    return a.len < b.len || (a.len == b.len && (a.i < b.i || (a.i == b.i && a.j < b.j)));
}

bool operator>(const Record& a, const Record& b) {
    return b < a;
}

Record max_substr(std::string s, std::string t) {
    s = "$" + s;
    t = "^" + t;
    vvi mxTill(isz(s), vi(isz(t)));
    Record best{0,1,1};
    for (int i = 1; i < isz(s); ++i) {
        for (int j = 1; j < isz(t); ++j) {
            if (s[i] == t[j]) { mxTill[i][j] = mxTill[i-1][j-1] + 1; }
            best = std::max(best, Record{mxTill[i][j], i-mxTill[i][j]+1, j-mxTill[i][j]+1});
        }
    }
    return best;
}
char opposite(char c) {
    return char('A' <= c && c <= 'Z' ? c - 'A' + 'a' : c - 'a' + 'A');
}
std::string solve(std::string s, std::string t) {
    s = split(s);
    auto t1 = split(t);
    auto best = max_substr(s,t1);
    best.i--, best.j--;
    for (int i = isz(t1)-1; i >= best.j + best.len; --i) {
        t.push_back(opposite(t1[i]));
    }
    for (int i = 0; i < best.j; ++i) {
        t.insert(t.begin(), opposite(t1[i]));
    }
    return s.substr(0, best.i) + t + s.substr(best.i+best.len);
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::string s, t;
    std::cin >> s >> t;
    std::cout << solve(s, t) << std::endl;
    return 0;
}