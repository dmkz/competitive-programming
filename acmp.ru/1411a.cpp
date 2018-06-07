/*
    Решение префиксным деревом. Accepted (1 сек, 39 МБ). В ячейке хранится вектор из пар. Переход за O(размер алфавита).
*/

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <cassert>
#include <memory>

struct Node {
    int count;
    
    std::vector<std::pair<char, std::unique_ptr<Node>>> next;
    
    Node() : count(0) { }
    
    std::vector<std::pair<char, std::unique_ptr<Node>>>::iterator find(char c) {
        auto it = next.begin();
        while (it != next.end()) {
            if (it->first == c) {
                break;
            }
            it++;
        }
        return it;
    }
};

struct Tree {
    std::unique_ptr<Node> head;
    
    std::vector<int> sum;
    
    Tree() { 
        head = std::unique_ptr<Node>(new Node());
    }
    
    void insert(const std::string & s) {
        while (sum.size() < s.size()) {
            sum.push_back(0);
        }
        
        auto curr = head.get();
        for (int i = 0; i < (int)s.size(); ++i) {
            const int c = s[i];
            auto next = curr->find(c);
            if (next == curr->next.end()) {
                curr->next.push_back(std::make_pair(c, std::unique_ptr<Node>(new Node)));
                next = std::prev(curr->next.end());
                sum[i]++;
            }
            curr = next->second.get();
            curr->count++;
        }
    }
    
    void remove(const std::string& s) {
        auto curr = head.get();
        for (int i = 0; i < (int)s.size(); ++i) {
            const char c = s[i];
            auto next = curr->find(c);
            assert(next != curr->next.end());
            assert(next->second->count > 0);
            if (--(next->second->count) == 0) {
                next->second = nullptr;
                std::swap(curr->next.back(), *next);
                curr->next.pop_back();
                for (int j = i; j < (int)s.size(); ++j) {
                    sum[j]--;
                }
                break;
            }
            curr = next->second.get();
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