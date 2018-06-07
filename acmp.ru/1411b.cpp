/*
    Решение префиксным деревом: Memory Limit. В узлах хранится map. Переход за O(log(размер алфавита))
*/

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <cassert>

struct Node {
    int count;
    std::map<char, Node*> next;
    
    Node() : count(0) { }
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
            const char c = s[i];
            if (cur->next.find(c) == cur->next.end()) {
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
        Node* cur = head;
        for (int i = 0; i < (int)s.size(); ++i) {
            path.push_back(cur);
            const char c = s[i];
            auto next = cur->next.find(c);
            assert(next != cur->next.end());
            cur = next->second;
            assert(cur->count > 0);
            cur->count--;
            if (cur->count == 0) {
                sum[i]--;
            }
        }
        for (int i = (int)s.size()-1; i >= 0; --i) {
            const char c = s[i];
            auto cur = path[i];
            auto it = cur->next.find(c);
            assert(it != cur->next.end());
            if (it->second->count == 0) {
                delete it->second;
                cur->next.erase(it);
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