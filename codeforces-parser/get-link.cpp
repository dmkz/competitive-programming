#include <bits/stdc++.h>
#include "cf-common.hpp"
using namespace std;
int main(int argc_, char *argv_[]) {
    //for (int i = 0;
    auto arguments = getArguments(argc_, argv_);
    std::string s;
    for (int i = 1; i < isz(arguments); i++) {
        s += arguments[i];
    }
    while (s.size() && isspace(s.back()))
        s.pop_back();
    //cerr << "s='" << s << "'" << std::endl;
    cout << s;
    return 0;
}