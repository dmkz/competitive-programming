/*
    Problem: 494A. Treasure
    
    Solution: strings, greedy, bracket sequences, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
typedef std::vector<int> vi;

vi solve(std::string s) {
    int cnt = 0, nOp = 0, nCl = 0;
    for (auto it : s) { 
        cnt += (it == '#'); 
        nOp += (it == '(');
        nCl += (it == ')');
    }
    vi answ;
    for (int i = 0; i < isz(s); ++i) {
        if (s[i] == '#') {
            assert(cnt > 0);
            if (cnt > 1) {
                s[i] = ')';
                answ.push_back(1);
                nCl++;
                --cnt;
                continue;
            }
            assert(cnt == 1);
            if (nOp - nCl <= 0) {
                return vi{-1};
            }
            answ.push_back(nOp - nCl);
            s = s.substr(0,i) + std::string(nOp-nCl,')') + s.substr(i+1);
            --cnt;
        }
    }
    int bal = 0;
    for (int i = 0; i < isz(s); ++i) {
        bal += (s[i] == '(' ? +1 : -1);
        if (bal < 0) { return vi{-1}; }
    }
    return bal == 0 ? answ : vi{-1};
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    for (auto &it : vec) { os << it << '\n'; }
    return os;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (std::string s; std::cin >> s; std::cout << std::endl) {
        std::cout << solve(s) << std::endl;
    }
    return 0;
}