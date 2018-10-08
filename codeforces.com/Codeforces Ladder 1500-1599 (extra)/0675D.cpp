/*
    Problem: 675D. Tree Construction
    
    Solution: SegmentTree, sorting, dfs, trees, constructive, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

struct Node { int value, pos; };

Node combine(const Node& n1, const Node& n2) {
    return n1.value < n2.value ? n1 : n2;
}

struct SegmentTree {

    int size;
    
    std::vector<Node> data;
    
    SegmentTree(const std::vector<Node>& arr) {
        size = (int)arr.size();
        int pow = 1;
        while (pow < size) pow *= 2;
        data.resize(2*pow);
        build(0, 0, size-1, arr);
    }

    void build(int v, int l, int r, const std::vector<Node>& arr) {
        if (l == r) {
            data[v] = Node{arr[l].pos, l};
        } else {
            int m = (l+r) / 2;
            build(2*v+1,  l,m,arr);
            build(2*v+2,m+1,r,arr);
            data[v] = combine(data[2*v+1], data[2*v+2]);
        }
    }
    
    Node get(int v, int l, int r, int ql, int qr) {
        if (l == ql && r == qr) {
            return data[v];
        } else {
            int m = (l+r)/2;
            if (qr <= m) {
                return get(2*v+1,l,m,ql,qr);
            } else if (ql > m) {
                return get(2*v+2,m+1,r,ql,qr);
            } else {
                return combine(get(2*v+1,l,m,ql,m),get(2*v+2,m+1,r,m+1,qr));
            }
        }
    }
    
    int get(int l, int r) {
        return get(0, 0, size-1, l, r).pos;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    // Input:
    int n; std::cin >> n;
    std::vector<Node> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i].value; arr[i].pos = i;
    }
    // Sorting values with positions:
    std::stable_sort(arr.begin(), arr.end(), [&](const Node& a, const Node& b){
        return a.value < b.value;
    });
    // Build segment tree over positions:
    SegmentTree st(arr);
    // DFS:
    std::vector<int> from(n, -1);
    std::function<void(int,int,int)> visit = [&](const int left, const int right, const int root) {
        if (left > right) return;
        auto it = st.get(left,right); // position of min element
        from[arr[it].pos] = arr[root].value;
        visit(left,it-1,it);
        visit(it+1,right,it);
    };
    visit(0, n-1, 0); // Run DFS from all array
    // Output:
    for (int i = 1; i < n; ++i) {
        std::cout << from[i] << ' ';
    }
    return 0;
}