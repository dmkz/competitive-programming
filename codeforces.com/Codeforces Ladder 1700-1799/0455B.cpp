/*
    Problem: 455B. A Lot of Games
    
    Solution: prefix tree, strings, game theory, O(|a|*|s|)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>

#define isz(x) (int)(x).size()

struct Node {
    bool canLose, canWin;
    Node *next[26];
    Node() {
        canLose = canWin = false;
        for (int i = 0; i < 26; i++) { next[i] = 0; }
    }
};

void insert(Node* node, const std::string& s, int p) {
    if (p == isz(s)) {
        return;
    }
    int id = s[p]-'a';
    if (node->next[id] == 0) {
        node->next[id] = new Node();
    }
    insert(node->next[id], s, p+1);
}

bool dfsCanWin(Node* curr) {
    curr->canWin = false;
    for (int id = 0; id < 26; id++) {
        if (curr->next[id] != 0) {
            curr->canWin = curr->canWin || !dfsCanWin(curr->next[id]);
        }
    }
    return curr->canWin;
}

bool dfsCanLose(Node * curr) {
    curr->canLose = false;
    bool was = false;
    for (int id = 0; id < 26; id++) {
        if (curr->next[id] != 0) {
            was = true;
            curr->canLose = curr->canLose || !dfsCanLose(curr->next[id]);
        }
    }
    if (!was) {
        curr->canLose = true;
    }
    return curr->canLose;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n, k; std::cin >> n >> k; ) {
        Node *root = new Node();
        while (n--) {
            std::string s; std::cin >> s;
            insert(root, s, 0);
        }
        bool canLose = dfsCanLose(root);
        bool canWin = dfsCanWin(root);
        if (canWin) {
            if (canLose) {
                std::cout << "First\n";
            } else {
                std::cout << (k % 2 == 1 ? "First\n" : "Second\n");
            }
        } else {
            std::cout << "Second\n";
        }
    }
    return 0;
}