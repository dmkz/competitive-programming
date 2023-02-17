// g++ -O3 -Wall -Wextra -pedantic process-rating.cpp -o process-rating.exe
#include <bits/stdc++.h>
#include "cf-common.hpp"

#define watch(x) debug && std::cerr << #x << " = '" << x << "'" << std::endl;

const bool debug = false;

#include "submission.hpp"

int main(int argc, char **argv) {
    setlocale(LC_ALL, "Ru-ru");
    assert(argc == 2);
    std::ifstream fs(argv[1]);
    std::string s;
    std::vector<Submission> stat;
    while(std::getline(fs, s)) {
        stat.push_back(Submission().from_string(s));
    }
    std::map<std::string, std::set<int>> solved;
    for (auto &s : stat) {
        if (s.verdict == "OK") {
            solved[s.nickname].insert(s.problemId);
        }
    }
    std::vector<std::pair<int,std::string>> best;
    for (auto &[nick,set] : solved)
        best.emplace_back(isz(set), nick);
    std::sort(all(best), std::greater<>());
    best.resize(10);
    for (auto &[cnt, nick] : best) {
        std::cout << cnt << ' ' << nick << std::endl;
    }
    return 0;
}