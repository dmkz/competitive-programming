/*
    Задача: 737. ДНК
    
    Решение: сортировка, бинарный поиск, два указателя, перебор, O(n^2*log(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int get_id(char c) {
    switch(c) {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
    }
    assert(false);
    return -1;
}

struct Record {
    int len, p1, p2;
};

bool operator<(const Record& a, const Record& b) {
    return a.len < b.len || (a.len == b.len && (a.p1 < b.p1 || (a.p1 == b.p1 && a.p2 < b.p2)));
}
bool operator>(const Record& a, const Record& b) {
    return b < a;
}
bool operator!=(const Record& a, const Record& b) {
    return b < a || a < b;
}
bool operator==(const Record& a, const Record& b) {
    return !(b == a);
}
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (std::string s, t; std::cin >> s >> t; ) {
        const int n = (int)s.size();
        const int m = (int)t.size();
        Record best{0,0,0};
        for (int len = 1; len <= std::min(n,m); ++len) {
            vvi fi;
            vi curr(5);
            for (int i = 0; i < len; ++i) {
                curr[get_id(s[i])]++;
            }
            fi.push_back(curr);
            for (int i = len; i < n; ++i) {
                curr.back()++;
                curr[get_id(s[i-len])]--;
                curr[get_id(s[i])]++;
                fi.push_back(curr);
            }
            std::sort(all(fi));
            curr.assign(5,0);
            for (int i = 0; i < len; ++i) {
                curr[get_id(t[i])]++;
            }
            auto equal = [](const vi& a, const vi& b, int begin, int after) {
                for (int i = begin; i < after; ++i) {
                    if (a[i] != b[i]) { return false; }
                }
                return true;
            };
            int p1 = -1, p2 = -1;
            auto search = [&]() {
                int save = curr.back();
                curr.back() = 0;
                auto it = std::lower_bound(all(fi), curr);
                curr.back() = save;
                if (it == fi.end() || !equal(*it, curr, 0, 4)) {
                    return false;
                }
                p1 = it->at(4);
                p2 = save;
                return true;
            };
            search();
            for (int i = len; i < m; ++i) {
                curr.back()++;
                curr[get_id(t[i-len])]--;
                curr[get_id(t[i])]++;
                search();
            }
            if (p1 == -1 || p2 == -1) { continue; }
            best = std::max(best, Record{len,p1,p2});
            
        }
        std::cout << best.len << std::endl;
        if (best.len != 0) {
            std::cout << best.p1+1 << ' ' << best.p2+1 << std::endl;
        }
    }
    return 0;
}