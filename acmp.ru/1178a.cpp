#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

struct Container { 
// Контейнер, поддерживающий операции:
// - Удаление элемента по индексу pos за корень
// - Вставка элемента по значению за корень

    std::vector<std::vector<int>> items;
    
    const int GSIZE = 128;
    
    Container() : items(1, std::vector<int>()) { }
    
    // Вставка значения - возврат количества элементов <= val
    int insert(int val) {
        int answ = 0;
        bool flag = false;
        for (auto group = items.begin(); group != items.end(); ++group) {
            if (group->empty() || std::next(group) == items.end() || val <= group->back()) {
                // Вставка
                auto it = std::upper_bound(group->begin(), group->end(), val);
                answ += int(it - group->begin());
                group->insert(it, val);
                if ((int)group->size() == 2 * GSIZE) {
                    auto temp = std::vector<int>(group->begin()+GSIZE, group->end());
                    group->resize(GSIZE);
                    items.insert(group+1, temp);
                }
                break;
            }
            answ += group->size();
        }
        return answ;
    }
    // Получение значения i-го по счету элемента (нумерация с нуля)
    int get(int pos, bool remove = true) {
        int answ = -1;
        for (auto group = items.begin(); group != items.end(); group++) {
            if (pos >= (int)group->size()) {
                pos -= (int)group->size();
            } else {
                answ = *(group->begin() + pos);
                if (remove) {
                    group->erase(group->begin() + pos);
                    if (group->empty() && items.size() > 1u) {
                        items.erase(group);
                    } else {
                        auto next = std::next(group);
                        if (next != items.end() && int(next->size() + group->size()) <= GSIZE) {
                            group->insert(group->end(), next->begin(), next->end());
                            items.erase(next);
                            break;
                        }
                        if (group != items.begin()) {
                            auto prev = std::prev(group);
                            if (int(prev->size() + group->size()) <= GSIZE) {
                                prev->insert(prev->end(), group->begin(), group->end());
                                items.erase(group);
                            }
                            break;
                        }
                    }
                    
                }
                break;
            }
        }
        assert(answ != -1);
        return answ;
    }
    
};

int main() {
    Container cont;
    int q;
    scanf("%d", &q);
    while (q--) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            // Добавление
            int value; scanf("%d", &value);
            value = 100001-value;
            printf("%d ", cont.insert(value));
        } else {
            assert(type == 2);
            int pos; 
            scanf("%d", &pos);
            cont.get(pos);
        }
    }
    return 0;
}
