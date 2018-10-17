/*
    Problem: 359D. Pair of Numbers
    
    Solution: sparse table, binary search, O(n * log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>

int gcd(int a, int b) {
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

struct Node {
    int min, gcd;
    
    Node(int min_ = 0, int gcd_ = 0) : min(min_), gcd(gcd_) { }
};

inline Node combine(const Node& a, const Node& b) {
    return Node(std::min(a.min, b.min), ::gcd(a.gcd, b.gcd));
}

struct SparseTable {

    int size;

    std::vector<int> log2;

    std::vector<std::vector<Node>> data;

    SparseTable(const std::vector<int>& arr) : size((int)arr.size()) {
        log2.resize(1+size);
        for (int i = 2; i <= size; ++i) {
            log2[i] = log2[i/2] + 1;
        }
        data.assign(log2[size]+1, std::vector<Node>(size, Node()));
        for (int i = 0; i < size; ++i) {
            data[0][i] = Node(arr[i], arr[i]);
        }
        for (int p = 1; p <= log2[size]; ++p) {
            for (int i = 0; i + (1 << p) - 1 < size; ++i) {
                data[p][i] = combine(data[p-1][i], data[p-1][i + (1 << (p-1))]);
            }
        }
    }
    
    Node get(int l, int r) {
        int len = r - l + 1;
        int log = log2[len];
        // pos + (1 << log) - 1 == r
        return combine(data[log][l], data[log][r-(1 << log)+1]);
    }
};

std::vector<int> solve(SparseTable& st, const int len) {
    std::vector<int> answ;
    for (int i = 0; i + len - 1 < st.size; ++i) {
        Node ret = st.get(i, i+len-1);
        if (ret.min == ret.gcd) {
            answ.push_back(i+1);
        }
    }
    return answ;
}

int main() {
    // Input:
    int n; scanf("%d", &n);
    std::vector<int> arr(n);
    for (auto& it : arr) scanf("%d", &it);
    // Binary search:
    SparseTable st(arr);
    int low = 0, high = n+1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (solve(st, mid).empty()) {
            high = mid;
        } else {
            low = mid;
        }
    }
    // Output:
    assert(low >= 1);
    auto answ = solve(st, low);
    printf("%d %d\n", (int)answ.size(), low-1);
    for (auto& it : answ) printf("%d ", it);
    printf("\n");
    return 0;
}