/*
    Problem: 496C. Removing Columns
    Solution: constructive, implementation
*/
#include <iostream>
#include <string>
#include <vector>

int greater(std::string& a, std::string& b) {
    for (int i = 0; i < (int)a.size(); ++i) {
        if (a[i] < b[i]) return (int)a.size();
        if (a[i] > b[i]) return i;
    }
    return (int)a.size();
}

int main() {
    int nRows, nCols;
    std::cin >> nRows >> nCols;
    
    std::vector<std::string> arr(nRows);
    for (auto& it : arr) std::cin >> it;
    int answ = 0;
    while (nCols > 0) {
        int min = nCols;
        for (int i = 0; i+1 < nRows; ++i) {
            min = std::min(min, greater(arr[i], arr[i+1]));
        }
        if (min == nCols) break;
        for (auto& it : arr) {
            it.erase(it.begin()+min);
        }
        --nCols,++answ;
    }
    std::cout << answ;
    
    return 0;
}