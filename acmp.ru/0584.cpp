/*
    Задача: 584. Спираль - 2
    
    Решение: динамическое программирование, рекурсия, конструктив, O(n+m)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>

const int UP = 1, DOWN = 3, LEFT = 0, RIGHT = 2;

struct Solution {
    std::vector<std::string> answ;
    Solution(const int nR, const int nC) {
        solve(nR,nC);
        rotr();
        move(1);
    }
    void move(int cnt) {
        if (!answ.empty() && answ.back()[0] == 'f') {
            int tmp;
            sscanf(answ.back().c_str(), "%*s %d", &tmp);
            cnt += tmp;
            answ.pop_back();
        }
        answ.push_back("f " + std::to_string(cnt));
    }
    void rotr() {
        assert(answ.size() > 0u);
        if (answ.back() == "l") {
            answ.pop_back();
            return;
        }
        answ.push_back("r");
    }
    void rotl() {
        assert(answ.size() > 0u);
        if (answ.back() == "r") {
            answ.pop_back();
            return;
        }
        answ.push_back("l");
    }
    void solve(int nR, int nC) {
        assert(nC > 0);
        if (nR == 0) {
            rotr();
            move(nC);
            rotr();
            return;
        }
        move(nR);
        rotr();
        if (nC == 2) {
            move(2);
            rotr();
            move(1);
            rotr();
            move(1);
            rotl();
            if (nR-1 > 0) {
                move(nR-1);
            }
        } else if (nC > 2) {
            move(2);
            solve(nC - 2, nR);
            move(1);
            rotl();
            if (nR-1 > 0) {
                move(nR-1);
            }
        } else {
            assert(nC == 1);
            move(1);
            rotr();
            move(nR);
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    int nR, nC; std::cin >> nR >> nC;
    Solution solution(nR,nC);
    std::cout << solution.answ.size() << "\n";
    for (auto &it : solution.answ) {
        std::cout << it << '\n';
    }
    return 0;
}