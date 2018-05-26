#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>

struct SqrtDecomposition {
    std::vector<int> arr, sum;
    
    const int GSIZE = 256;
    
    SqrtDecomposition(int size = 0, int element = 0) {
        arr.assign(size, element);
        sum.assign((size+GSIZE-1)/GSIZE, 0);
        for (int g = 0; g < (int)sum.size(); ++g) {
            const int begin = g * GSIZE;
            const int after = std::min(begin+GSIZE, size);
            for (int i = begin; i < after; ++i) {
                sum[g] += arr[i];
            }
        }
    }
    
    void set(int pos, int value) {
        sum[pos/GSIZE] += (value-arr[pos]);
        arr[pos] = value;
    }
    
    int get(int l, int r) {
        const int gl = l / GSIZE;
        const int gr = r / GSIZE;
        if (gl == gr) {
            int s = 0;
            for (int i = l; i <= r; ++i) {
                s += arr[i];
            }
            return s;
        } else {
            int s = 0;
            for (int i = l, after = (gl+1)*GSIZE; i < after; ++i) {
                s += arr[i];
            }
            for (int g = gl + 1; g < gr; ++g) {
                s += sum[g];
            }
            for (int i = gr*GSIZE; i <= r; ++i) {
                s += arr[i];
            }
            return s;
        }
    }
};

struct Container { 
// Эффективно (за корень) удаляет i-ый элемент в отсортированного множестве
// Все значения ожидаются от 1 до MAX_VALUE
    std::vector<std::vector<int>> items;
    const int GSIZE = 256;
    
    Container(int MAX_VALUE) {
        items.resize((MAX_VALUE + GSIZE-1) / GSIZE);
    }
    
    void insert(int val) { // Вставка значения
        assert(val >= 1);
        const int g = (val-1) / GSIZE;
        auto it = std::upper_bound(items[g].begin(), items[g].end(), val);
        items[g].insert(it, val);
    }
    // Получение значения i-го по счету элемента (нумерация с нуля)
    int get(int pos, bool remove = true) {
        int answ = -1;
        for (auto& it : items) {
            if (pos >= (int)it.size()) {
                pos -= (int)it.size();
            } else {
                answ = *(it.begin() + pos);
                if (remove) {
                    it.erase(it.begin() + pos);
                }
                break;
            }
        }
        assert(answ != -1);
        return answ;
    }
};

int main() {    
    SqrtDecomposition sd(1+100000, 0);
    Container cont(100000);
    int q;
    scanf("%d", &q);
    while (q--) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            // Добавление
            int value; scanf("%d", &value);
            value = 100001-value;
            printf("%d ", sd.get(0, value));
            sd.set(value, 1);
            cont.insert(value);
        } else {
            assert(type == 2);
            int pos; 
            scanf("%d", &pos);
            int value = cont.get(pos);
            sd.set(value, 0);
        }
    }
    return 0;
}