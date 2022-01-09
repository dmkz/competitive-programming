#include <bits/stdc++.h>
// для каждого элемента будем хранить следующий за ним элемент: next
// для каждого блока будем хранить его начало (самый левый элемент): begin
// конец (самый правый элемент): end
// количество элементов: size
// представителя: parent
std::vector<int> parent, size, next, begin, end;
void init(int n) {
    // инициализация всего нужного:
    size = parent = next = begin = end = std::vector<int>(1+n);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        next[i] = 0;
        size[i] = 1;
        begin[i] = i;
        end[i] = i;
    }
}

int getParent(int u) {
    // запрос представителя с сжатием путей
    if (parent[u] == u) return u;
    parent[u] = getParent(parent[u]);
    return parent[u];
}

void connect(int u, int v) {
    // соединяем: к большому блоку добавляем маленький блок:
    u = getParent(u);
    v = getParent(v);
    assert(u != v);
    // соединяем кубини на границе блоков:
    next[end[u]] = begin[v];
    // запоминаем новое начало и новый конец общего блока:
    int newBegin = begin[u]; // начало левого блока
    int newEnd   = end[v];   // конец правого блока
    // теперь u - корень бОльшего дерева, по сравнению с v
    // подвешиваем меньшее дерево к большему
    parent[v] = u;
    size[u] += size[v];
    begin[u] = newBegin;
    end[u]   = newEnd;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) {
        // соединяем всё:
        int n; std::cin >> n;
        init(n);
        for (int i = 0; i < n-1; i++) {
            int u,v; std::cin >> u >> v;
            connect(u,v);
        }
        // теперь, начиная от начала общего блока, выводим перестановку:
        int curr = begin[getParent(1)];
        while (curr != 0) {
            std::cout << curr << ' ';
            curr = next[curr];
        }
        std::cout << '\n';
    }
    return 0;
}