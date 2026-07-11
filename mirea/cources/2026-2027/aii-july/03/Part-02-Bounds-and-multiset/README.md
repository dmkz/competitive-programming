## 7. `std::multiset` и его отличия от `std::set`

`std::multiset` очень похож на `std::set`, но между ними есть одно принципиальное различие:

- `set` хранит только **различные** значения;
- `multiset` хранит **все** значения, в том числе одинаковые.

Например, такой код:

```cpp
multiset<int> ms;
ms.insert(5);
ms.insert(5);
ms.insert(5);
```

оставит в контейнере три копии числа `5`.

Как и `set`, `multiset` хранит элементы в отсортированном порядке и поддерживает `insert`, `erase`, `find`, `count`, `lower_bound`, `upper_bound`.

<details>
<summary><strong>Пример: чем <code>multiset</code> отличается от <code>set</code></strong></summary>

```cpp
#include <iostream>
#include <set>
#include <vector>
using namespace std;

void print(const string &name, const auto &a) {
    cout << name << " = {";
    int i = 0;
    for (int x : a) {
        if (i > 0) cout << ',';
        cout << x;
        i++;
    }
    cout << "}" << '\n';
}

int main() {
    vector<int> a = {5, 2, 5, 7, 5, 2};

    set<int> s;    
    multiset<int> ms;
    for (int x : a) {
        s.insert(x);
        ms.insert(x);
    }

    // set оставляет только различные значения.
    // multiset хранит все копии одинаковых значений.
    print("set", s);
    print("multiset", ms);
    cout << "set.size() = " << s.size() << '\n';
    cout << "multiset.size() = " << ms.size() << '\n';
    cout << "multiset.count(5) = " << ms.count(5) << '\n';

    // erase(value) удаляет все копии значения.
    ms.erase(5);
    print("after ms.erase(5)", ms);

    // Восстановим multiset и удалим только одну копию через итератор.
    ms = {5, 2, 5, 7, 5, 2};
    auto it = ms.find(5);
    if (it != ms.end()) {
        ms.erase(it);
    }
    print("after erase(it)", ms);
}
```

Вывод программы:

```text
set = {2,5,7}
multiset = {2,2,5,5,5,7}
set.size() = 3
multiset.size() = 6
multiset.count(5) = 3
after ms.erase(5) = {2,2,7}
after erase(it) = {2,2,5,5,7}
```

Файл примера: [C++](examples/example-01.cpp).

</details>

> [!WARNING]
> `ms.count(x)` у `multiset` может работать линейно по числу копий `x`. Если в задаче часто нужны именно частоты, иногда удобнее хранить их отдельно, например в `map<int, int>` (увидим в следующей главе).

> [!WARNING]
> `ms.erase(x)` удаляет **все** вхождения `x`.
> `ms.erase(it)` удаляет **ровно одну** копию по итератору.

Если нужно удалить только одно вхождение `x`, обычно сначала получают итератор через

```cpp
auto it = ms.find(x);
```

а затем, если такой элемент нашёлся, вызывают `ms.erase(it)`.

---

## 8. Продвинутые операции: `lower_bound` и `upper_bound`

Теперь обсудим две очень важные операции ordered-контейнеров:

- `lower_bound(x)` — первый элемент, который **не меньше** `x`;
- `upper_bound(x)` — первый элемент, который **строго больше** `x`.

Пусть есть контейнер

```cpp
set<int> s = {2, 5, 8, 10};
```

Тогда:

- `s.lower_bound(6)` укажет на `8`;
- `s.upper_bound(8)` укажет на `10`.

А если есть

```cpp
multiset<int> ms = {2, 5, 5, 5, 8, 10};
```

то:

- `ms.lower_bound(5)` укажет на **первую** пятёрку;
- `ms.upper_bound(5)` укажет на `8`, то есть на первый элемент после блока пятёрок.

Именно поэтому через `lower_bound` и `upper_bound` удобно искать соседей и выделять диапазон одинаковых элементов.

Типичные примеры:

1. Минимальный элемент $\ge x$:

   ```cpp
   auto it = s.lower_bound(x);
   if (it != s.end()) {
       cout << *it << '\n';
   }
   ```

2. Минимальный элемент $\gt x$:

   ```cpp
   auto it = s.upper_bound(x);
   if (it != s.end()) {
       cout << *it << '\n';
   }
   ```

3. Максимальный элемент $\lt x$:

   ```cpp
   auto it = s.lower_bound(x);
   if (it != s.begin()) {
       --it;
       cout << *it << '\n';
   }
   ```

Последний шаблон ищет предыдущий элемент. Здесь надо быть аккуратным: если `it == s.begin()`, то элемента слева нет.

Для `set` и `multiset` нужно вызывать именно **методы контейнера**:

```cpp
s.lower_bound(x);
s.upper_bound(x);
```

а не алгоритмы из `<algorithm>`:

```cpp
lower_bound(s.begin(), s.end(), x);   // так писать не надо
upper_bound(s.begin(), s.end(), x);   // так тоже не надо
```

Потому что:

- `s.lower_bound(x)` работает за $O(\log n)$;
- `lower_bound(s.begin(), s.end(), x)` на `set` может деградировать до $O(n)$.

> [!IMPORTANT]
> Для `set` и `multiset` используем `container.lower_bound(...)` и `container.upper_bound(...)`, а не алгоритмы по итераторам.

Полный файл примера: [C++](examples/example-02.cpp).

---

## 9. У `set` и `multiset` нет индексации!

У `vector` можно было получить индекс элемента через разность итераторов:

```cpp
int pos = it - a.begin();
```

Для `set` и `multiset` так делать нельзя:

```cpp
auto it = s.find(x);
// int pos = it - s.begin();   // так писать нельзя
```

Итераторы `set` и `multiset` не являются итераторами произвольного доступа, а элементы в памяти не лежат последовательно. По этой же причине эти контейнеры не умеют обращаться к $k$-му элементу по индексу.

> [!TIP]
> Если в задаче нужны индекс элемента или $k$-й по порядку элемент, используйте другую структуру, например ordered set из GNU PBDS:
> https://codeforces.com/blog/entry/11080

> [!WARNING]
> У `ordered_set` из GNU PBDS тоже нельзя вычитать итераторы.
> Конструкции вида `it - s.begin()` и `it2 - it1` для него не работают.

> [!WARNING]
> `std::distance(it1, it2)` для `ordered_set` использовать не рекомендуется.
> Она компилируется, но не заменяет операции порядковой статистики и может работать линейно.
> Для индекса элемента и количества чисел в диапазоне используйте `order_of_key(...)` и `find_by_order(...)`.

<details>
<summary><strong>Пример: ordered_set из GNU PBDS</strong></summary>

```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
#include <iostream>
using namespace std;
using namespace __gnu_pbds;

template<typename T, typename Comp = std::less<T>>
using ordered_set = tree<T, null_type, Comp, rb_tree_tag, tree_order_statistics_node_update>;

void print(const string &name, const auto &a) {
    cout << name << " = {";
    int i = 0;
    for (int x : a) {
        if (i > 0) cout << ',';
        cout << x;
        i++;
    }
    cout << "}" << '\n';
}

int main() {
    ordered_set<int> s;

    // Вставка.
    s.insert(10);
    s.insert(3);
    s.insert(7);
    s.insert(15);
    s.insert(7);
    print("after insert", s);

    // find_by_order(i) возвращает итератор на i-й элемент.
    for (int i = 0; i < (int)s.size(); i++) {
        cout << "s[" << i << "] = " << *s.find_by_order(i) << '\n';
    }

    // Удаление.
    s.erase(10);
    print("after erase(10)", s);

    // Для int количество элементов на отрезке [L, R]
    // равно order_of_key(R + 1) - order_of_key(L).
    int L = 4;
    int R = 15;
    int cnt = s.order_of_key(R + 1) - s.order_of_key(L);
    cout << "count in [4, 15] = " << cnt << '\n';
}
```

Вывод программы:

```text
after insert = {3,7,10,15}
s[0] = 3
s[1] = 7
s[2] = 10
s[3] = 15
after erase(10) = {3,7,15}
count in [4, 15] = 2
```

Файл примера: [C++](examples/example-03.cpp).

</details>