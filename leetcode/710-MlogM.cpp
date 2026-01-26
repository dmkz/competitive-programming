// random, swap, sort, unordered_map, O(M*log(M))

#include <bits/stdc++.h>
using namespace std;

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
    Solution(int n, vector<int>& blacklist) : last(n-1) {
        // будем обменивать местами очередное заблокированное число
        // с последним числом на отрезке - с числом last
        // так мы уменьшаем длину отрезка на 1 и оставляем его непрерывным
        // [0, last] -> [0, x-1] U [x+1, last] -> [0, last-1]
        // ВАЖНО: числа необходимо обрабатывать в порядке убывания,
        // чтобы избежать циклов
        sort(blacklist.begin(), blacklist.end());
        for (int i = (int)blacklist.size()-1; i >= 0; i--) {
            int x = blacklist[i];
            // элемент x теперь забанен
            // надо найти, где он
            if (x != last)
                // вырезать элемент x из отрезка [0, last]
                index[x] = getIndex(last);
            last--;
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
