#include <bits/stdc++.h>
#include "cf-common.hpp"
using namespace std;
int main(int argc_, char *argv_[]) {
    auto argv = getArguments(argc_, argv_);
    assert(argc_ == 3);
    // argv[1] == what
    // argv[2] == where
    std::string s = fileToString(argv[2]);
    cout << (s.find(argv[1]) != s.npos);
    return 0;
}