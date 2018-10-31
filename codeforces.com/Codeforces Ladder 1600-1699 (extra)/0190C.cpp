/*
    Problem: 190C. STL
    
    Solution: strings, dfs, recursive descent parser, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

struct Solver {

    bool wasError;

    std::string answ;
    
    int pos;
    
    Solver(const std::vector<std::string>& arr) {
        wasError = false;
        pos = 0;
        get_type(arr);
        if (pos != (int)arr.size()) { wasError = true; }
        if (wasError) { answ = "Error occurred"; }
    }
    
    void get_type(const std::vector<std::string>& arr) {
        if (wasError) {
            return;
        }
        if (pos == (int)arr.size()) {
            wasError = true;
            return;
        }
        if (arr[pos] == "pair") {
            answ += "pair";
            answ += "<";
            pos++;
            get_type(arr);
            answ += ",";
            get_type(arr);
            answ += ">";
        } else if (arr[pos] == "int") {
            answ += "int";
            pos++;
        } else {
            wasError = true;
        }
    }
};

int main() {
    int n; std::cin >> n;
    std::vector<std::string> arr;
    std::string word;
    while (std::cin >> word) {
        arr.push_back(word);
    }
    std::cout << Solver(arr).answ << std::endl;
    return 0;
}