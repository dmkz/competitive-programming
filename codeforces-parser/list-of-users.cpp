// g++ -O3 -Wall -Wextra -pedantic list-of-users.cpp -o list-of-users.exe
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
    std::set<std::string> users;
    for (auto &s : stat) {
        users.insert(s.nickname);
    }
    for (auto it : users) {
        std::cout << it << '\n';
    }
    return 0;
}