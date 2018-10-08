/*
    Problem: 706D. Vasiliy's Multiset
    
    Solution: trie, xor, O(n*log(MAX))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <cassert>

struct Node {

    int count;

    Node* link[2];
    
    Node(int cnt = 0, Node* left = 0, Node* right = 0) : count(cnt) {
        link[0] = left;
        link[1] = right;
    }
};

struct Trie {

    Node* root;
    
    Trie() { 
        root = new Node();
    }

    void insert(int x) {
        Node* curr = root;
        for (int i = 30; i >= 0; --i) {
            if (curr->link[0] == 0) { curr->link[0] = new Node(); }
            if (curr->link[1] == 0) { curr->link[1] = new Node(); }
            curr = curr->link[(x >> i) & 1];
            curr->count++;
        }
    }
    
    void remove(int x) {
        Node* curr = root;
        for (int i = 30; i >= 0; --i) {
            curr = curr->link[(x >> i) & 1];
            curr->count--;
        }
    }
    
    int maxXor(int x) {
        Node* curr = root;
        int answ = 0;
        for (int i = 30; i >= 0; --i) {
            if ((x >> i) & 1) {
                if (curr->link[0]->count > 0) {
                    curr = curr->link[0];
                    answ |= (1 << i);
                } else {
                    assert(curr->link[1]->count > 0);
                    curr = curr->link[1];
                }
            } else {
                if (curr->link[1]->count > 0) {
                    answ |= (1 << i);
                    curr = curr->link[1];
                } else {
                    assert(curr->link[0]->count > 0);
                    curr = curr->link[0];
                }
            }
        }
        return answ;
    }
};

int main() {
    Trie trie;
    trie.insert(0);
    int n; scanf("%d", &n);
    while (n--) {
        char t; int x;
        scanf(" %c %d", &t, &x);
        if (t == '+') trie.insert(x);
        if (t == '-') trie.remove(x);
        if (t == '?') printf("%d\n", trie.maxXor(x));
    }
    return 0;
}