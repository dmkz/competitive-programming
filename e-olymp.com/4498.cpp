/*
    Задача: 4498. Возвращение блудного попугая
    
    Решение: Персистентное дерево отрезков, O((n+q)*log(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

typedef long long ll;

struct Info { // Структура для хранения информации об отрезке
    ll sum, pref, suff, max; // сумма элементов, максимальная сумма на префиксе, на суффиксе и на отрезке соответственно.
};

// Функция комбинирования двух структур:
Info combine(const Info& a, const Info& b) {
    Info c{a.sum + b.sum, a.pref, b.suff, a.sum + b.sum};
    c.pref = std::max(c.pref, a.sum + b.pref);
    c.suff = std::max(c.suff, a.suff + b.sum);
    c.max = std::max({a.suff + b.pref, c.sum, c.pref, c.suff, a.max, b.max});
    return c;
}

struct Node { // Структура под узел дерева отрезков
    int vl, vr;
    
    Info info;
};

struct SegmentTree {
    
    const int size;            // Размер исходного массива, над которым построено дерево отрезков
    
    std::vector<int> version;  // Массив различных версий дерева отрезков. Хранит корни дерева для соответствующей версии.
    
    std::vector<Node> data;    // Массив узлов дерева отрезков
    
    void build(int v, int l, int r, const std::vector<int>& arr) {
        if (l == r) {
            // Построение листа:
            auto& curr = data[v];
            curr.vl = curr.vr = -1;
            curr.info = Info{arr[l], arr[l], arr[l], arr[l]};
        } else {
            int m = (l + r) / 2;
            // Построение левого поддерева:
            int vl = data[v].vl = data.size();
            data.push_back(Node{});
            build(vl,   l, m, arr);
            // Построение правого поддерева:
            int vr = data[v].vr = data.size();
            data.push_back(Node{});
            build(vr, m+1, r, arr);
            // Объединение информации от поддеревьев:
            data[v].info = combine(data[vl].info, data[vr].info);
        }
    }
    
    // Изменение отдельного элемента для выбранной версии:
    void set(int v, int l, int r, int pos, int value) {
        if (l == r) {
            data[v].info = Info{value,value,value,value};
        } else {
            int m = (l + r) / 2, vl = data[v].vl, vr = data[v].vr;
            if (pos <= m) { // Меняем левое поддерево:
                data.push_back(data[vl]);
                vl = data[v].vl = (int)data.size()-1;
                set(vl,   l, m, pos, value);
            } else { // Меняем правое поддерево:
                data.push_back(data[vr]);
                vr = data[v].vr = (int)data.size()-1;
                set(vr, m+1, r, pos, value);
            }
            // Комбинируем ответы:
            data[v].info = combine(data[vl].info, data[vr].info);
        }
    }
    
    // Изменение отдельного элемента с добавлением новой версии:
    void set(int pos, int value) {
        // Добавляем новую версию дерева:
        data.push_back(data[version.back()]);
        version.push_back((int)data.size()-1);
        // Вызываем рекурсивную процедуру добавления пути в дереве:
        set(version.back(), 0, size-1, pos, value);
    }
    
    // Запрос к выбранной версии:
    Info get(int v, int l, int r, int ql, int qr) {
        if (l == ql && r == qr) {
            return data[v].info;
        } else {
            int m = (l + r) / 2, vl = data[v].vl, vr = data[v].vr;
            if (qr <= m) {       // Запрос лежит целиком в левом поддереве
                return get(vl,   l, m, ql, qr);
            } else if (ql > m) { // Запрос лежит целиком в правом поддереве
                return get(vr, m+1, r, ql, qr);
            } else {             // Разбиваем запрос на два, комбинируя ответы:
                return combine(get(vl, l, m, ql, m), get(vr, m+1, r, m+1, qr));
            }
        }
    }
    
    // Запрос с выбором версии:
    ll get(int idVersion, int left, int right) {
        // Вызываем запрос для нужной версии:
        return get(version[idVersion], 0, size-1, left, right).max;
    }
    
    SegmentTree(const std::vector<int>& arr) : size((int)arr.size()){
        // Изначальная версия - нулевая. Строим изначальную версию на массиве arr:
        version.push_back(0);
        data.push_back(Node{});
        build(0, 0, size-1, arr);
    }
    
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int nItems, nDays;
    std::cin >> nItems >> nDays;
    
    std::vector<int> arr(nItems);
    for (auto& it : arr) {
        std::cin >> it;
    }
    
    // Строим дерево отрезков:
    SegmentTree st(arr);
    
    // Заводим массив контроля версий под конец каждого дня:
    std::vector<int> version(1+nDays, -1);
    version[0] = 0;
    
    // Читаем запросы на изменение и добавляем новые версии дерева отрезков:
    int nSetQueries;
    std::cin >> nSetQueries;
    
    while (nSetQueries--) {
        int day, pos, value; 
        std::cin >> day >> pos >> value;
        version[day] = (int)st.version.size();
        st.set(pos-1, value);
    }
    
    // В промежуточные дни ссылаемся на версии предыдущих дней:
    for (int i = 1; i <= nDays; ++i) {
        if (version[i] == -1) {
            version[i] = version[i-1];
        }
    }
    
    // Обрабатываем запросы:
    int nGetQueries; ll answ = 0;
    std::cin >> nGetQueries;
    for (int i = 1; i <= nGetQueries; ++i) {
        int l, r; std::cin >> l >> r;
        int day = (i + answ) % nDays + 1;
        answ = 0;
        std::cout << (answ = std::max(answ, st.get(version[day], l-1, r-1))) << '\n';
    }
    return 0;
}