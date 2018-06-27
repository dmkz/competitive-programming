/*
    "Удаление": дерево отрезков, O(n*log(n))
*/

#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>

struct SegmentTree {
    
    int size;
    
    std::vector<int> data;
    
    void build(int v, int l, int r, const std::vector<bool>& array) {
        if (l == r) {
            data[v] = array[l];
        } else {
            int m = (l + r) / 2;
            build(2*v+1,   l, m, array);
            build(2*v+2, m+1, r, array);
            data[v] = data[2*v+1] + data[2*v+2];
        }
    }
    
    void set(int v, int l, int r, int p, int a) {
        if (l == r) {
            data[v] = a;
        } else {
            int m = (l + r) / 2;
            if (p <= m) {
                set(2*v+1,   l, m, p, a);
            } else {
                set(2*v+2, m+1, r, p, a);
            }
            data[v] = data[2*v+1] + data[2*v+2];
        }
    }
    
    void set(int pos, int value) {
        set(0, 0, size-1, pos, value);
    }
    
    int get(int sum) const {
        // Найти самый левый r, такой что сумма на отрезке [0, r] равна sum.
        int v = 0, l = 0, r = size-1;
        while (l < r) {
            if (data[2*v+1] >= sum) {
                v = 2*v+1;
                r = (l+r) / 2;
            } else {
                sum -= data[2*v+1];
                v = 2*v+2;
                l = (l+r) / 2 + 1;
            }
        }
        return r;
    }
    
    SegmentTree(const std::vector<bool>& array) {
        size = (int)array.size();
        int pow = 1;
        while (pow < size) pow *= 2;
        assert(pow >= size);
        data.resize(2*pow);
        build(0, 0, size-1, array);
    }
};

int main() {
    double t = clock();
    
    int n, k, q;
    scanf("%d %d %d", &n, &k, &q);
    
    std::vector<int> answer(1+n, 0);
    
    SegmentTree st(std::vector<bool>(1+n,true));
    
    st.set(0,0);
    // Моделирование удаления элементов за O(n log(n))
    while (n >= k) {
        int sum = k, erased = 0, limit = n / k;
        while (erased < limit) {
            int number = st.get(sum);
            st.set(number, 0);
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