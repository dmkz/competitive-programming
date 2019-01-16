/*
    Problem: 7268 - A granite of science
    
    Solution: probability theory, expected value, O(N * M)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <vector>

typedef long double ld;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<ld> vd;
typedef std::vector<vd> vvd;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int nCurses, nFirstDays, nDays = 0;
    while (std::cin >> nCurses >> nFirstDays) {
        vvi difficulty(1+nCurses);
        for (int id = 1; id <= nCurses; ++id) {
            auto &diff = difficulty[id];
            int nLessons = 0;
            std::cin >> nLessons;
            diff.resize(nLessons);
            for (auto &it : diff) { std::cin >> it; }
            nDays = std::max(nDays, nFirstDays + nLessons-1);
        }
        vvd expected_value(1+nCurses, vd(nDays)), expected_square(1+nCurses, vd(nDays));
        for (int id = 1; id <= nCurses; ++id) {
            const auto &diff = difficulty[id];
            vd addToSquares(nDays+1), addToValues(nDays+1);
            for (int ls = 0; ls < (int)diff.size(); ++ls) {
                const int beginDay = ls;
                const int afterDay = beginDay + nFirstDays;
                addToValues[beginDay] += ld(diff[ls]) / nFirstDays;
                addToValues[afterDay] -= ld(diff[ls]) / nFirstDays;
                addToSquares[beginDay] += ld(diff[ls]) * ld(diff[ls]) / nFirstDays;
                addToSquares[afterDay] -= ld(diff[ls]) * ld(diff[ls])/ nFirstDays;
            }
            ld balance = 0;
            for (int day = 0; day < nDays; ++day) {
                balance += addToSquares[day];
                expected_square[id][day] = balance;
            }
            balance = 0;
            for (int day = 0; day < nDays; ++day) {
                balance += addToValues[day];
                expected_value[id][day] = balance;
            }
        }
        ld answ = 0;
        for (int day = 0; day < nDays; ++day) {
            for (int id = 1; id <= nCurses; ++id) { 
                answ += expected_square[id][day];
            }
            ld sum = 0;
            for (int id = 1; id <= nCurses; ++id) { 
                sum += expected_value[id][day]; 
            }
            for (int id = 1; id <= nCurses; ++id) { 
                answ += expected_value[id][day] * (sum - expected_value[id][day]); 
            }
        }
        //printf("%0.9Lf\n", answ);
        std::cout << std::fixed << std::setprecision(7);
        std::cout << answ << std::endl;
    }
    return 0;
}