/*
    Problem: 342B. Xenia and Spies
    
    Solution: strings, greedy, implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

struct Triple {
    int time, left, right;
};

int main() {
    int n, m, s, f;
    while (std::cin >> n >> m >> s >> f) {
        std::vector<Triple> triples(m);
        for (auto& t : triples) {
            std::cin >> t.time >> t.left >> t.right;
        }
        int tPos = 0, curr = s, time = 1;
        std::string answ;
        while (f != curr) {
            if (tPos == m || triples[tPos].time > time) {
                if (f < curr) {
                    answ += "L";
                    curr--;
                } else {
                    answ += "R";
                    curr++;
                }
                ++time;
                continue;
            }
            assert(triples[tPos].time == time);
            int next = f < curr ? curr-1 : curr+1;
            if (
                (triples[tPos].left <= curr && curr <= triples[tPos].right) ||
                (triples[tPos].left <= next && next <= triples[tPos].right)
            ) {
                answ += "X";
            } else {
                if (f < curr) {
                    answ += "L";
                    curr--;
                } else {
                    answ += "R";
                    curr++;
                }
            }
            ++time;
            tPos++;
        }
        std::cout << answ << std::endl;
    }
    return 0;
}