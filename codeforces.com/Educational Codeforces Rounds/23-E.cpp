/*
    Problem: 817E. Choosing The Commander
    
    Solution: trie, prefix tree, bits, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>

struct Node {

    int cnt, vl, vr;
    
    Node(int cnt_ = 0, int vl_ = -1, int vr_ = -1) : cnt(cnt_), vl(vl_), vr(vr_) { }
};

struct Tree {

    std::vector<Node> data;
    
    Tree() {
        data.push_back(Node());
    }
    
    void push(int v) {
        assert(0 <= v && v < (int)data.size());
        if (data[v].vl == -1 || data[v].vr == -1) {
            data.push_back(Node());
            data.push_back(Node());
            data[v].vl = (int)data.size()-2;
            data[v].vr = (int)data.size()-1;
        }
    }
    
    void insert(int p) {
        int curr = 0;
        for (int bit = 30; bit >= 0; --bit) {
            push(curr);
            curr = ((p >> bit) & 1) ? data[curr].vr : data[curr].vl;
            assert(curr != -1);
            data[curr].cnt++;
        }
    }

    void remove(int p) {
        int curr = 0;
        for (int bit = 30; bit >= 0; --bit) {
            push(curr);
            curr = ((p >> bit) & 1) ? data[curr].vr : data[curr].vl;
            assert(curr != -1);
            data[curr].cnt--;
        }
    }
    
    int query(int p, int l) {
        int curr = 0, answ = 0;
        for (int bit = 30; bit >= 0; --bit) {
            push(curr);
            if ((l >> bit) & 1) {
                int skip = ((p >> bit) & 1) ? data[curr].vr : data[curr].vl;
                int move = ((p >> bit) & 1) ? data[curr].vl : data[curr].vr;
                answ += data[skip].cnt;
                curr = move;
            } else {
                int move = ((p >> bit) & 1) ? data[curr].vr : data[curr].vl;
                curr = move;
            }
            if (data[curr].cnt == 0) break;
        }
        return answ;
    }
};

int main() {
    int n; scanf("%d", &n);
    Tree tree;
    while (n--) {
        int t, p; scanf("%d %d", &t, &p);
        if (t == 1) {
            tree.insert(p);
        } else if (t == 2) {
            tree.remove(p);
        } else {
            int l; scanf("%d", &l);
            printf("%d\n", tree.query(p, l));
        }
    }
    return 0;
}