/*
    Задача: 1083. Sqrt-декомпозиция
    
    Решение: Segment Tree, ленивое проталкивание, O(n + q * log(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>
#include <string>

typedef long long ll;

const int INF = (int)1e9+1;
const int UNDEF = -1;

/*
    Структура узла дерева отрезков: 
    - `value` - значение, которое должно быть присвоено всему отрезку (UNDEF - не определено)
    - `extra` - значение, которое должно быть прибавлено к каждому элементу отрезка
    - `sum` - сумма на отрезке
    - `min` - минимум на отрезке
    
    Соглашения:
    1)  Если value != UNDEF: 
            a) extra = 0
            б) сумма вычисляется как value * len
            в) минимум вычисляется как value
    2)  Если extra != 0:
            a) сумма вычисляется как sum + len * extra
            б) минимум вычисляется как min + extra
        
*/

struct Node {
    
    int value, extra; ll sum; int min;
    
    Node(int value_ = UNDEF, int extra_ = 0, ll sum_ = 0, int min_ = 0) 
        : value(value_), extra(extra_), sum(sum_), min(min_) { }

};

struct SegmentTree {

    int size;
    
    std::vector<Node> data;
    
    // Конструктор от массива:
    SegmentTree(const std::vector<int>& arr) : size((int)arr.size()) {
        int pow = 1;
        while (pow < size) pow *= 2;
        data.resize(2*pow);
        build(0,0,size-1,arr);
    }
    
    // Пересчет значений для текущего элемента от его поддеревьев:
    void modify(int v, int l, int r, int m) {
        assert(data[v].value == UNDEF && data[v].extra == 0);
        data[v].sum = sum(2*v+1, l, m, l, m) + sum(2*v+2, m+1, r, m+1, r);
        data[v].min = std::min(min(2*v+1, l, m, l, m), min(2*v+2, m+1, r, m+1, r));
    }
    
    // Построение дерева:
    void build(int v, int l, int r, const std::vector<int>& arr) {
        if (l == r) { // лист
            data[v] = Node{arr[l], 0, arr[l], arr[l]};
        } else {
            int m = (l + r) >> 1;
            build(2*v+1,   l, m, arr);
            build(2*v+2, m+1, r, arr);
            modify(v, l, r, m);
        }
    }
    
    // Протакливание изменений от корня к детям:
    void push(int v, int l, int r, int m) {
        // Если отрезок - лист, то ничего проталкивать не нужно:
        if (l == r) return;
        // Если всему отрезку было присвоено какое-то значение:
        if (data[v].value != UNDEF) {
            assert(data[v].extra == 0);
            update(2*v+1,   l, m,   l, m, data[v].value);
            update(2*v+2, m+1, r, m+1, r, data[v].value);
            data[v].value = UNDEF;
        }
        // Если ко всему отрезку было прибавлено какое-то значение:
        if (data[v].extra != 0) {
            add(2*v+1,   l, m,   l, m, data[v].extra);
            add(2*v+2, m+1, r, m+1, r, data[v].extra);
            data[v].extra = 0;
        }
    }
    
    // Запрос присвоения на отрезке:
    void update(int v, int l, int r, int ql, int qr, int x) {
        if (qr < l || ql > r) return;
        ql = std::max(ql, l);
        qr = std::min(qr, r);
        if (ql == l && qr == r) { // отрезок целиком
            data[v] = Node{x, 0, x * ll(qr-ql+1), x};
        } else {
            int m = (l+r) >> 1;
            push(v, l, r, m);
            update(2*v+1,   l, m, ql, qr, x);
            update(2*v+2, m+1, r, ql, qr, x);
            modify(v, l, r, m);
        }
    }
    
    // Запрос прибавления на отрезке:
    void add(int v, int l, int r, int ql, int qr, int x) {
        if (qr < l || ql > r) return;
        ql = std::max(ql, l);
        qr = std::min(qr, r);
        if (ql == l && qr == r) { // Если было присвоение на отрезке
            if (data[v].value != UNDEF) {
                assert(data[v].extra == 0);
                data[v].value += x;
            } else {
                data[v].extra += x;
            }
        } else {
            int m = (l+r) >> 1;
            push(v, l, r, m);
            add(2*v+1,   l, m, ql, qr, x);
            add(2*v+2, m+1, r, ql, qr, x);
            modify(v, l, r, m);
        }
    }
    
    // Запрос получения одного элемента:
    int get(int v, int l, int r, int p) {
        assert(l <= p && p <= r);
        if (data[v].value != UNDEF) {
            assert(data[v].extra == 0);
            return data[v].value;
        } else {
            int m = (l+r) >> 1, ret;
            push(v, l, r, m);
            if (p <= m) {
                ret = get(2*v+1,   l, m, p);
            } else {
                ret = get(2*v+2, m+1, r, p);
            }
            modify(v, l, r, m);
            return ret;
        }
    }
    
    // Запрос получения суммы на отрезке:
    ll sum(int v, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return 0;
        ql = std::max(l, ql);
        qr = std::min(r, qr);
        if (ql == l && qr == r) {
            if (data[v].value != UNDEF) {
                assert(data[v].extra == 0);
                return ll(qr-ql+1) * data[v].value;
            } else {
                return data[v].sum + data[v].extra * ll(qr-ql+1);
            }
        } else {
            int m = (l + r) >> 1;
            push(v, l, r, m);
            ll ret = sum(2*v+1, l, m, ql, qr) + sum(2*v+2, m+1, r, ql, qr);
            modify(v, l, r, m);
            return ret;
        }
    }
    
    // Запрос получения минимума на отрезке:
    int min(int v, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return INF;
        ql = std::max(l, ql);
        qr = std::min(r, qr);
        if (ql == l && qr == r) {
            if (data[v].value != UNDEF) {
                assert(data[v].extra == 0);
                return data[v].value;
            } else {
                return data[v].min + data[v].extra;
            }
        } else {
            int m = (l + r) >> 1;
            push(v, l, r, m);
            int ret = std::min(min(2*v+1, l, m, ql, qr), min(2*v+2, m+1, r, ql, qr));
            modify(v, l, r, m);
            return ret;
        }
    }
    
    // Более удобные внешние запросы:
    void update(int left, int right, int x) {
        update(0, 0, size-1, left, right, x);
    }
    
    void add(int left, int right, int x) {
        add(0, 0, size-1, left, right, x);
    }
    
    int get(int pos) {
        return get(0, 0, size-1, pos);
    }
    
    ll sum(int left, int right) {
        return sum(0, 0, size-1, left, right);
    }
    
    int min(int left, int right) {
        return min(0, 0, size-1, left, right);
    }
};


int main() {
    int n; scanf("%d", &n);
    std::vector<int> arr(n);
    for (auto& it : arr) scanf("%d", &it);
    SegmentTree st(arr);
    int q; scanf("%d", &q);
    while (q--) {
        char buf[7]; scanf("%6s", buf);
        std::string op(buf);
        if (op == "get") {
            int pos; scanf("%d", &pos);
            printf("%d\n", st.get(pos-1));
        } else if (op == "update") {
            int l, r, x; scanf("%d %d %d", &l, &r, &x);
            st.update(l-1, r-1, x);
        } else if (op == "add") {
            int l, r, x; scanf("%d %d %d", &l, &r, &x);
            st.add(l-1, r-1, x);
        } else if (op == "rsq") {
            int l, r; scanf("%d %d", &l, &r);
            printf("%I64d\n", st.sum(l-1, r-1));
        } else if (op == "rmq") {
            int l, r; scanf("%d %d", &l, &r);
            printf("%d\n", st.min(l-1,r-1));
        }
    }
    return 0;
}