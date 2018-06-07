/*
    Решение префиксным деревом: Memory Limit. В узлах массив. Переход за O(1)
*/

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <cassert>

struct Node {
    int count;
    
    Node* next[26];    
    
    Node() : count(0) { 
        for (int i = 0; i < 26; ++i) {
            next[i] = nullptr;
        }
    }
};

struct Tree {
    Node* head;
    
    std::vector<int> sum;
    
    Tree() { 
        head = new Node();
    }
    
    void insert(const std::string & s) {
        while (sum.size() < s.size()) {
            sum.push_back(0);
        }
        
        Node* cur = head;
        for (int i = 0; i < (int)s.size(); ++i) {
            const int c = s[i]-'a';
            assert(0 <= c && c < 26);
            if (cur->next[c] == nullptr) {
                cur->next[c] = new Node();
                sum[i]++;
            }
            cur = cur->next[c];
            cur->count++;
        }
    }
    
    void remove(const std::string& s) {
        std::vector<Node*> path;
        path.reserve(s.size());
        Node* curr = head;
        for (int i = 0; i < (int)s.size(); ++i) {
            path.push_back(curr);
            const int c = s[i]-'a';
            assert(0 <= c && c < 26);
            curr = curr->next[c];
            assert(curr != nullptr && curr->count > 0);
            curr->count--;
            if (curr->count == 0) {
                sum[i]--;
            }
        }
        for (int i = (int)s.size()-1; i >= 0; --i) {
            const int c = s[i]-'a';
            assert(0 <= c && c < 26);
            auto curr = path[i];
            auto next = curr->next[c];
            assert(next != nullptr);
            if (next->count == 0) {
                delete next;
                curr->next[c] = nullptr;
            } else {
                break;
            }
        }
    }
    
    int get(int length) const {
        return sum[length-1];
    }
};

int main() {
    Tree t;
    int nQ; scanf("%d", &nQ);
    static char buf[1+1000000];
    while (nQ--) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%1000000s", buf);
            t.insert(buf);
        } else if (type == 2) {
            scanf("%1000000s", buf);
            t.remove(buf);
        } else {
            assert(type == 3);
            int len; scanf("%d", &len);
            printf("%d\n", t.get(len));
        }
    }
    return 0;
}