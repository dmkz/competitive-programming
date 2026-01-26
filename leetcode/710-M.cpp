// random, swap, unordered_map, O(M)

#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(),(x).end()

const int zero = [](){
    ios::sync_with_stdio(false);
    cin.tie(0);
    return 0;
}();

mt19937 gen{124};

class Solution {
    int last;
    unordered_map<int, int> index;
    
    int getIndex(int i) const {
        auto it = index.find(i);
        if (it != index.end())
            return it->second;
        return i;
    }
    
public:
    Solution(int n, vector<int>& blacklist) {
        const int end = n - (int)blacklist.size();
        last = end-1;
        int firstToSwap = end;
        unordered_set<int> black(all(blacklist));
        for (auto x : blacklist) {
            // элемент x теперь забанен
            if (x >= end) // ничего не нужно, элемент будет удалён сам
                continue;
            // обменяем с первым незабаненным
            while (black.count(firstToSwap))
                firstToSwap++;
            index[x] = firstToSwap++;
        }
    }
    
    int pick() {
        return getIndex(uniform_int_distribution<int>(0, last)(gen));
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(n, blacklist);
 * int param_1 = obj->pick();
 */
 
main() {
    vector<int> blacklist{0, 3};
    Solution *solution = new Solution(4, blacklist);
    cout << solution->pick() << endl; // return 0, any integer from [0,1,4,6] should be ok. Note that for every call of pick,
                     // 0, 1, 4, and 6 must be equally likely to be returned (i.e., with probability 1/4).
    cout << solution->pick() << endl; // return 4
    cout << solution->pick() << endl; // return 1
    cout << solution->pick() << endl; // return 6
    cout << solution->pick() << endl; // return 1
    cout << solution->pick() << endl; // return 0
    cout << solution->pick() << endl; // return 4
}
