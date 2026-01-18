// random, swap, unordered_map, O(1)

#include <bits/stdc++.h>
#define isz(x) (int)(x).size()

const int zero = [](){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    return 0;
}();

using pii = std::pair<int,int>;

std::mt19937 gen;

class Solution {
    int numRows, numCols, zeros{};
    std::unordered_map<int, int> index;
public:
    Solution(int m, int n) : numRows(m), numCols(n), zeros(n * m) { }
    
    int getIndex(int x) {
        auto it = index.insert({x, x}).first;
        return it->second;
    }
    
    std::vector<int> indexToPoint(int x) const {
        int row = x / numCols;
        int col = x - row * numCols;
        return {row, col};
    }
    
    std::vector<int> flip() {
        int last = zeros - 1;
        int x = std::uniform_int_distribution<int>(0, last)(gen);
        int result = getIndex(x);
        if (x != last)
            index[x] = getIndex(last);
        zeros--;
        return indexToPoint(result);
    }
    
    void reset() {
        zeros = numRows * numCols;
        index.clear();
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(m, n);
 * vector<int> param_1 = obj->flip();
 * obj->reset();
 */

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec) {
    os << '{';
    for (int i = 0; i < isz(vec); i++) {
        if (i > 0) os << ',';
        os << vec[i];
    }
    return os << '}';
}

main() {
    Solution solution(3, 1);
    std::cout << solution.flip() << std::endl;
    std::cout << solution.flip() << std::endl;
    std::cout << solution.flip() << std::endl;
    solution.reset();
    std::cout << solution.flip() << std::endl;
}
