/*
    Задача: 380. Площадь прямоугольников
    
    Решение: Segment Tree, сканирующая прямая, сжатие координат, ленивое проталкивание, O(n log(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

/*
    Для начала сожмем координаты по OY, будем обрабатывать события по OX в порядке увеличения координаты.
    
    Имеем события: 
    
        1) увеличить все значения на отрезке [y1, y2] на 1 в момент времени `x`
        2) уменьшить все значения на отрезке [y1, y2] на 1 в момент времени `x`
        3) посчитать количество ненулевых ячеек, которые были на отрезке [x1, x2]
        
    Таким образом, количество ненулевых ячеек от x_min до x_max и будет площадью объединения прямоугольников.
    
    Для того, чтобы посчитать количество ненулевых ячеек, посчитаем количество нулевых, и вычтем их из остальных.
    
    Для этого можно использовать sqrt-декомпозицию, или дерево отрезков. Нужно хранить (минимум, его количество).
    
    Значения в ячейках не могут стать меньше, чем 0.
    
    Авторское решение использует дерево отрезков, должно заходить за время O(n log(n)).
    
    Решение прокомментировано и содержит лишние проверки, потому что автор "плавает" в деревьях отрезков.
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <ctime>
#include <cstdlib>

/*
    Структура узла в дереве отрезков:
    - `value` - значение, которое нужно присвоить всем элементам отрезка
    - `extra` - величина, которую нужно добавить всем элементам отрезка
    - `size`  - количество элементов на отрезке (не равно длине отрезка), не изменяется
    - `min`   - значение минимального элемента на отрезке
    - `cnt`   - количество минимальных элементов на отрезке
    
    Соглашения:
    1) Если value != UNDEF: (в данной задаче только у листьев)
        a) extra = 0
        б) минимальный элемент равен value
        в) количество минимумов равно size
    2) Если extra != 0:
        б) минимальный элемент вычисляется как min + extra
        в) его акнуальное количество в переменной cnt
*/

typedef long long ll;
const int INF   = (int)1e9+1;
const int UNDEF = -1;

struct Node {
    int value, extra, size, min, cnt;
    
    Node(int value_ = UNDEF, int extra_ = 0, int size_ = 0, int min_ = INF, int cnt_ = 0)
        : value(value_), extra(extra_), size(size_), min(min_), cnt(cnt_) { }
};

// Пересчет текущего минимума и его количества относительно другого значения:
inline void remin(int& min, int& cnt, int value, int count) {
    if (min == value) {
        cnt += count;
    } else if (min > value) {
        min = value;
        cnt = count;
    }
}

struct SegmentTree {
    
    int size;
    
    std::vector<Node> data;
    
    // Конструктор от массивов из элементов на отрезках и длин отрезков:
    SegmentTree(const std::vector<int>& arr, const std::vector<int>& sizes) {
        size = (int)arr.size();
        int pow = 1;
        while (pow < size) pow *= 2;
        data.resize(2*pow);
        build(0, 0, size-1, arr, sizes);
    }

    // Пересчет значения в узле от значения в поддеревьях:
    void modify(int v, int l, int r, int m) {
        assert(data[v].value == UNDEF && data[v].extra == 0);
        data[v].size = data[2*v+1].size + data[2*v+2].size;
        data[v].min = INF; data[v].cnt = 0;
        getmin(2*v+1,   l, m,   l, m, data[v].min, data[v].cnt);
        getmin(2*v+2, m+1, r, m+1, r, data[v].min, data[v].cnt);
    }
    
    // Проталкивание изменения от дерева в поддеревья:
    void push(int v, int l, int r, int m) {
        // Если лист, то ничего проталкивать не нужно:
        if (l == r) return;
        assert(data[v].value == UNDEF);
        // Иначе если есть изменения, которые следует передать:
        if (data[v].extra != 0) {
            add(2*v+1,   l, m,   l, m, data[v].extra);
            add(2*v+2, m+1, r, m+1, r, data[v].extra);
            data[v].extra = 0;
        }
    }
    
    // Построение дерева рекурсивно:
    void build(int v, int l, int r, const std::vector<int>& arr, const std::vector<int>& sizes) {
        if (l == r) { // лист
            data[v] = Node(arr[l], 0, sizes[l], arr[l], sizes[l]);
        } else {
            int m = (l + r) >> 1;
            build(2*v+1,   l, m, arr, sizes);
            build(2*v+2, m+1, r, arr, sizes);
            modify(v, l, r, m);
        }
    }
    
    // Получение минимального элемента на отрезке и его количества
    // предполагается, что изначально min = INF, cnt = 0
    void getmin(int v, int l, int r, int ql, int qr, int& min, int& cnt) {
        if (qr < l || r < ql) return;
        ql = std::max(ql, l);
        qr = std::min(qr, r);
        if (l == ql && r == qr) { // Весь отрезок входит в запрос:
            if (data[v].value != UNDEF) {
                assert(data[v].extra == 0);
                remin(min, cnt, data[v].value, data[v].size);
            } else {
                remin(min, cnt, data[v].min + data[v].extra, data[v].cnt);
            }
        } else { // Отправляем запросы в поддеревья:
            int m = (l + r) >> 1;
            push(v, l, r, m);
            getmin(2*v+1,   l, m, ql, qr, min, cnt);
            getmin(2*v+2, m+1, r, ql, qr, min, cnt);
            modify(v, l, r, m);
        }
    }
    
    // Прибавление значения на отрезке:
    void add(int v, int l, int r, int ql, int qr, int x) {
        if (qr < l || r < ql) return;
        ql = std::max(ql, l);
        qr = std::min(qr, r);
        if (l == ql && r == qr) { // Весь отрезок входит в запрос:
            if (data[v].value != UNDEF) {
                assert(data[v].extra == 0);
                data[v].value += x;
            } else {
                data[v].extra += x;
            }
        } else {
            int m = (l + r) >> 1;
            push(v, l, r, m);
            add(2*v+1,   l, m, ql, qr, x);
            add(2*v+2, m+1, r, ql, qr, x);
            modify(v, l, r, m);
        }
    }
    
    // Более удобные функции под внешние запросы:
    void add(int left, int right, int value) {
        add(0, 0, size-1, left, right, value);
    }
    
    void getmin(int left, int right, int& min, int& cnt) {
        min = INF, cnt = 0;
        getmin(0, 0, size-1, left, right, min, cnt);
    }
};

struct Event { // Структура под событие arr[left...right] += value в момент времени time
    int time, left, right, value;
};

inline bool operator<(const Event& a, const Event& b) {
    if (a.time < b.time) return true;
    if (a.time > b.time) return false;
    if (a.value < b.value) return true;
    if (a.value > b.value) return false;
    return a.left < b.left || (a.left == b.left && a.right < b.right);
}

int main() {
    double time = (double)clock();
    // Чтение входных данных:
    int n; scanf("%d", &n);
    std::vector<Event> events;
    std::vector<int> coord;
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        if (x2 < x1) std::swap(x1, x2);
        if (y2 < y1) std::swap(y1, y2);
        --y2; --x2;
        if (x2 < x1 || y2 < y1) continue;
        assert(x1 <= x2);
        assert(y1 <= y2);
        events.push_back(Event{  x1, y1, y2,  1});
        events.push_back(Event{x2+1, y1, y2, -1});
        coord.push_back(y1);
        coord.push_back(y2);
    }
    // Сжатие координат:
    std::stable_sort(coord.begin(), coord.end());
    coord.erase(std::unique(coord.begin(), coord.end()), coord.end());
    std::vector<int> arr, size;
    for (int i = 0; i < (int)coord.size(); ++i) {
        if (i > 0 && coord[i] - coord[i-1] > 1) {
            arr.push_back(coord[i-1]+1);
            size.push_back(coord[i] - coord[i-1]-1);
        }
        arr.push_back(coord[i]);
        size.push_back(1);
    }
    // Сортировка событий:
    std::sort(events.begin(), events.end());
    for (auto& e : events) {
        e.left  = int(std::lower_bound(arr.begin(), arr.end(),  e.left) - arr.begin());
        e.right = int(std::lower_bound(arr.begin(), arr.end(), e.right) - arr.begin());
    }
    // Создание дерева отрезков и обработка запросов:
    const int MAX = (int)size.size()-1;
    const int CNT = std::accumulate(size.begin(), size.end(), 0);
    SegmentTree st(std::vector<int>(MAX+1,0), size);
    int last = events.front().time-1; ll answ = 0;
    for (auto& e : events) {
        if (e.time > last) {
            int min, cnt;
            st.getmin(0, MAX, min, cnt);
            int notZeros = CNT - (min == 0 ? cnt : 0);
            answ += std::max(0, e.time - last) * 1LL * notZeros;
            last = e.time;
        }
        st.add(e.left, e.right, e.value);
    }
    std::cout << answ << "\n";
    fprintf(stderr, "time = %0.3fs\n", ((double)clock() - time) / CLOCKS_PER_SEC);
    return 0;
}