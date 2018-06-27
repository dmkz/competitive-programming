/*
    "Удаление": дерево Фенвика, O(n*log(n))
*/

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>

int log2(int n) {
    int pow = 0;
    while ((1 << (pow+1)) <= n) {
        ++pow;
    }
    return pow;
}

struct Fenwick {
    
    const int size, pow2;
    
    std::vector<int> data;
    
    Fenwick(const std::vector<bool>& a) 
        : size((int)a.size())
        , pow2(1 << log2(size))
    {
        data.resize(size);
        for (int i = 0; i < (int)a.size(); i++) {
            inc(i, a[i]);
        }
    }

    // Сумма на отрезке [0, r]:
    int sum(int r) const {
        int result = 0;
        for (; r >= 0; r = (r & (r+1)) - 1) {
            result += data[r];
        }
        return result;
    }

    // Изменение элемента в позиции p на величину delta:
    void inc(int p, int delta) {
        for (; p < size; p = (p | (p+1))) {
            data[p] += delta;
        }
    }

    // Сумма на отрезке [l, r]:
    int sum (int l, int r) const {
        return sum(r) - sum(l-1);
    }
    
    // Нижняя граница для суммы s: sum[0]+...+sum[p-1] > s >= sum[0]+...+sum[p]
    int lower_bound(int s) const {
        int pos = 0;
        for (int p = pow2; p >= 1; p /= 2) {
            if (pos + p - 1 < size && data[pos + p - 1] < s) {
                s -= data[pos + p - 1];
                pos += p;
            }
        }
        return pos;
    }  
};

int main() {
    double t = clock();
    
    int n, k, q;
    scanf("%d %d %d", &n, &k, &q);
    
    std::vector<int> answer(1+n, 0);
    
    Fenwick fw(std::vector<bool>(1+n, true));
    
    fw.inc(0, -1);

    // Моделирование удаления элементов за O(n log(n))
    while (n >= k) { 
        int sum = k, erased = 0, limit = n / k;
        while (erased < limit) {
            int number = fw.lower_bound(sum);
            fw.inc(number, -1);
            answer[number] = (int)answer.size() - n + erased;
            sum += k - 1;
            ++erased;
        }
        n -= erased;
    }
    
    // Ответ на запросы:
    while (q--) {
        int item;
        scanf("%d", &item);
        printf("%d\n", answer[item]);
    }
    
    fprintf(stderr, "time = %0.3fs\n", (clock() - t) / CLOCKS_PER_SEC);
    
    return 0;
}