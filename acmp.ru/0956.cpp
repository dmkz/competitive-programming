/*
    Задача: 965. Юный гитарист
    
    Решение: перебор, реализация, строки, O(6 * n^6)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <vector>

const std::vector<std::string> fi = {"A" , "Bb", "B" , "C" , "C#", "D" , "D#", "E" , "F" , "F#", "G" , "G#"};
const std::vector<std::string> se = {"A" , "A#", "B" , "C" , "Db", "D" , "Eb", "E" , "F" , "Gb", "G" , "Ab"};

#define all(x) (x).begin(), (x).end()
#define find(x, t) int(std::find(all(x), (t)) - (x).begin())

int getId(const std::string s) {
    int pos = (int)std::min(find(fi, s), find(se, s));
    return pos;
}

std::vector<int> getAccord(std::string s) {
    {
        int id = getId(s);
        if (id != 12) {
            return std::vector<int>{id, (id+4)%12, (id+7)%12};
        }
    }
    if (s.back() == 'm') {
        s.pop_back();
        int id = getId(s);
        assert(id != 12);
        return std::vector<int>{id, (id+3)%12, (id+7)%12};
    }
    if (s.back() == '7') {
        s.pop_back();
        if (s.back() == 'm') {
            s.pop_back();
            int id = getId(s);
            assert(id != 12);
            return std::vector<int>{id, (id+3)%12, (id+7)%12, (id+10)%12};
        }
        int id = getId(s);
        assert(id != 12);
        return std::vector<int>{id, (id+4)%12, (id+7)%12, (id+10) % 12};
    }
    assert(false);
    return std::vector<int>{};
}

int main() {
    int n;
    while (std::cin >> n) {
        std::vector<int> initial(6);
        for (int i = 0; i < 6; ++i) {
            std::string s; std::cin >> s;
            initial[i] = getId(s);
        }
        std::string s; std::cin >> s;
        auto need = getAccord(s);
        std::sort(need.begin(), need.end());
        assert(std::unique(need.begin(), need.end()) == need.end());
        n++;
        int limit = (int)std::pow(n, 6), answ = 0;
        for (int mask = 0; mask < limit; ++mask) {
            std::vector<int> tmp(6);
            for (int i = 0, v = mask; i < 6; ++i) {
                tmp[i] = (initial[i] + (v % n)) % 12;
                v /= n;
            }
            std::sort(tmp.begin(), tmp.end());
            tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());
            answ += (tmp == need);
        }
        std::cout << answ << std::endl;
    }
    return 0;
}