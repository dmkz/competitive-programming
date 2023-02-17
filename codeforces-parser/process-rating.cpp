// g++ -O3 -Wall -Wextra -pedantic process-rating.cpp -o process-rating.exe
#include <bits/stdc++.h>
#include "cf-common.hpp"

#define watch(x) debug && std::cerr << #x << " = '" << x << "'" << std::endl;

const bool debug = false;

#include "submission.hpp"

int main(int argc, char **argv) {
    setlocale(LC_ALL, "Ru-ru");
    //assert(argc == 3);
    std::ifstream fs(argv[1]);
    const int limit = std::atoi(argv[2]);
    bool only_users = false;
    std::string from = "Jan/01/1970 00:00";
    std::string to = "Jan/01/3000 00:00";
    
    if (argc >= 4 && argv[3] == std::string("only_users")) {
        only_users = true;
    }
    if (argc >= 5) from = argv[4]; // "Feb/15/2023 19:19"
    if (argc >= 6) to = argv[5]; // "Feb/15/2023 19:19"
    std::string s;
    std::vector<Submission> stat;
    while(std::getline(fs, s)) {
        stat.push_back(Submission().from_string(s));
    }
    std::map<std::string, std::set<int>> solved;
    const auto L = date2number(from);
    const auto R = date2number(to);
    for (auto &s : stat) {
        if (auto t = date2number(s.when);
            s.verdict == "OK" && L <= t && t <= R)
        {
            solved[s.nickname].insert(s.problemId);
        }
    }
    std::vector<std::pair<int,std::string>> best;
    for (auto &[nick,set] : solved)
        best.emplace_back(isz(set), nick);
    std::sort(all(best), std::greater<>());
    best.resize(std::min(isz(best),limit));
    for (auto &[cnt, nick] : best) {
        if (only_users) {
            std::cout << nick << '\n';
        } else {
            std::cout << cnt << ' ' << nick << std::endl;
        }
    }
    return 0;
}