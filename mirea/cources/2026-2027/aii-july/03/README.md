<!-- Этот файл собран автоматически из README.md внутри Part-01-Ordered-set, Part-02-Bounds-and-multiset, Part-03-Map-and-frequencies и Part-04-Hashing-and-pitfalls. -->
<!-- Для обновления запустите: python build-readme.py -->

# Лекция 3. set, multiset, map и хеш-таблицы

## 1. Что такое `set`?

`std::set` в C++ хранит **уникальные** элементы в **отсортированном порядке**.

Это сразу даёт два важных свойства:

- можно быстро проверять, есть ли элемент в множестве;
- можно быстро находить минимальный, максимальный и ближайшие по порядку элементы.

Про `set` полезно думать не как про «магический контейнер», а как про структуру для задач такого вида:

- хранить множество различных значений;
- быстро добавлять и удалять значения;
- быстро проверять наличие значения;
- уметь находить первый элемент не меньше `x`;
- уметь брать минимум и максимум среди текущих значений.

Элементы хранятся в самобалансирующемся двоичном дереве поиска (в красно-чёрном дереве). Это даёт асимптотику $O(\log (n))$ почти на все операции.

---

## 2. Базовые операции с `set` в C++

Создание множества:

```cpp
set<int> s;
```

Основные операции:

```cpp
s.insert(x); // добавить x
s.erase(x);  // удалить x, если он есть
s.size();    // размер множества
s.empty();   // пусто ли множество
s.find(x);   // найти x (либо не найти :)
s.count(x);  // посчитать x (0 или 1)
```

Метод `find(x)` возвращает итератор на найденный элемент, либо итератор на end, если элемент не найден.

Проверка наличия через `find`:

```cpp
if (s.find(x) != s.end()) {
    // элемент найден
}
```

Та же проверка через `count`:

```cpp
if (s.count(x) > 0) {
    // элемент найден
}
```

<details>
<summary><strong>Пример: вставка, поиск и удаление элементов</strong></summary>

```cpp
#include <iostream>
#include <vector>
#include <set>
using namespace std;

void print(const string &name, const auto &s) {
    cout << name << " = {";
    int i = 0;
    for (const auto &item : s) {
        if (i > 0) cout << ',';
        cout << item;
        i++;
    }
    cout << '}' << endl;
}

int main() {
    vector<int> a = {6, 1, 1, 7, 7, 5, 4, 4, 2};

    // вставка элементов в set:
    set<int> s;
    for (int i = 0; i < a.size(); i++)
        s.insert(a[i]);

    // количество уникальных элементов:
    cout << s.size() << '\n';

    // вывод элементов на экран:
    print("s", s);

    // поиск и удаление элементов:
    for (int i = 0; i < a.size(); i++) {
        cout << "Delete " << a[i] << ": ";
        auto iter = s.find(a[i]);
        if (iter == s.end()) {
            cout << "fail";
        } else {
            cout << "ok";
            s.erase(iter);
        }
        print(", s", s);
    }

    return 0;
}
```

Вывод программы:

```text
6
s = {1,2,4,5,6,7}
Delete 6: ok, s = {1,2,4,5,7}
Delete 1: ok, s = {2,4,5,7}
Delete 1: fail, s = {2,4,5,7}
Delete 7: ok, s = {2,4,5}
Delete 7: fail, s = {2,4,5}
Delete 5: ok, s = {2,4}
Delete 4: ok, s = {2}
Delete 4: fail, s = {2}
Delete 2: ok, s = {}
```

Файл примера: [C++](Part-01-Ordered-set/examples/example-01.cpp).

</details>

> [!NOTE]
> Элементы в `set` автоматически хранятся в отсортированном порядке. Поэтому в примере после вставки чисел из массива множество печатается как `s = {1,2,4,5,6,7}`, хотя сами числа шли в другом порядке.

> [!IMPORTANT]
> Дубликаты в `set` не хранятся. Повторные вставки `1`, `7` и `4` из примера не создают новые копии элементов, поэтому размер множества равен `6`, а не `9`.

> [!NOTE]
> Удалять элемент можно не только по итератору, но и по значению: `s.erase(x);`. Это безопасно: если элемента `x` в множестве нет, контейнер просто не изменится.

---

## 3. Минимум и максимум

Так как `set` хранит элементы по возрастанию, то:

- `*s.begin()` – минимальный элемент;
- `*prev(s.end())` – максимальный элемент;
- `*s.rbegin()` – тоже максимальный элемент.

Часто в олимпиадном коде пишут и так:

```cpp
*(--s.end())
```

Это тот же максимум. Такой трюк полезно знать, потому что он регулярно встречается в чужих решениях. Но `*prev(s.end())` или `*s.rbegin()` проще читать.

> [!NOTE]
> Эти обращения работают за $O(1)$. Контейнер умеет сразу получить `begin()`, `end()` и `rbegin()`, а `prev(s.end())` делает ровно один шаг назад от `end()`.

> [!WARNING]
> Нельзя брать минимум или максимум у пустого множества.
> Перед обращением к `begin()` или `prev(end())` нужно понимать, что множество не пусто.

---

## 4. `set` по убыванию

Если нужен порядок не по возрастанию, а по убыванию, можно, по аналогии с тем, как мы уже делали сортировку по убыванию, передать другой компаратор как шаблонный параметр:

```cpp
set<int, greater<int>> s;
```

Теперь:

- `*s.begin()` – максимум;
- `*prev(s.end())` – минимум.

Рекомендуется к использованию, если нужно держать элементы в порядке убывания.

<details>
<summary><strong>Пример: вставка, поиск и удаление элементов в <code>set</code> по убыванию</strong></summary>

```cpp
#include <functional>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

void print(const string &name, const auto &s) {
    cout << name << " = {";
    int i = 0;
    for (const auto &item : s) {
        if (i > 0) cout << ',';
        cout << item;
        i++;
    }
    cout << '}' << endl;
}

int main() {
    vector<int> a = {6, 1, 1, 7, 7, 5, 4, 4, 2};

    // вставка элементов в set с обратным порядком:
    set<int, greater<int>> s;
    for (int i = 0; i < a.size(); i++)
        s.insert(a[i]);

    // количество уникальных элементов:
    cout << s.size() << '\n';

    // вывод элементов на экран:
    print("s", s);

    // поиск и удаление элементов:
    for (int i = 0; i < a.size(); i++) {
        cout << "Delete " << a[i] << ": ";
        auto iter = s.find(a[i]);
        if (iter == s.end()) {
            cout << "fail";
        } else {
            cout << "ok";
            s.erase(iter);
        }
        print(", s", s);
    }

    return 0;
}
```

Вывод программы:

```text
6
s = {7,6,5,4,2,1}
Delete 6: ok, s = {7,5,4,2,1}
Delete 1: ok, s = {7,5,4,2}
Delete 1: fail, s = {7,5,4,2}
Delete 7: ok, s = {5,4,2}
Delete 7: fail, s = {5,4,2}
Delete 5: ok, s = {4,2}
Delete 4: ok, s = {2}
Delete 4: fail, s = {2}
Delete 2: ok, s = {}
```

Файл примера: [C++](Part-01-Ordered-set/examples/example-02.cpp).

</details>

---

## 5. А это есть в Python?

Самобалансирующихся деревьев поиска нет в стандартном Python. Структуры `dict` и `set` – это другое, они появятся в следующих главах.

Если вы участвуете в онлайн-контестах, где разрешено использовать заранее заготовленный код, и не хотите пересаживаться на C++, то можно скопировать и вставить свой шаблон `ordered set`.

Ниже – пример компактной олимпиадной реализации декартова дерева с хранением размеров поддеревьев. Поддерживаемые операции:

- `insert(x)` – добавить `x`, вернуть `True`, если элемент добавился, и `False`, если он уже был в множестве.
- `erase(x)` – удалить `x`, вернуть `True`, если элемент был удалён, и `False`, если его не было.
- `count(x)` – вернуть `1`, если элемент есть, и `0`, если его нет.
- `find(x)` – вернуть позицию элемента в отсортированном порядке или `None`, если элемента нет.
- `size()` или `len(s)` – размер множества.
- `empty()` – проверить, пусто ли множество.
- `lower_bound(x)` – первый элемент, не меньший `x`, или `None`, если такого элемента нет.
- `upper_bound(x)` – первый элемент, строго больший `x`, или `None`, если такого элемента нет.
- `find_by_order(k)` – $k$-й элемент в отсортированном порядке, нумерация с нуля.
- `order_of_key(x)` – количество элементов, строго меньших `x`.
- `s[k]` – короткий аналог `find_by_order(k)`.

<details>
<summary><strong>Python3: компактная реализация ordered set на treap</strong></summary>

```python
from random import randint


class OrderedSet:
    class _Node:
        __slots__ = ("key", "prior", "left", "right", "size")

        def __init__(self, key):
            self.key = key
            self.prior = randint(1, 1 << 30)
            self.left = None
            self.right = None
            self.size = 1

    def __init__(self, values=()):
        self.root = None
        for x in values:
            self.insert(x)

    @staticmethod
    def _size(node):
        return 0 if node is None else node.size

    @classmethod
    def _pull(cls, node):
        if node is not None:
            node.size = 1 + cls._size(node.left) + cls._size(node.right)
        return node

    @classmethod
    def _split(cls, node, x):
        if node is None:
            return None, None
        if node.key < x:
            left_part, right_part = cls._split(node.right, x)
            node.right = left_part
            return cls._pull(node), right_part
        left_part, right_part = cls._split(node.left, x)
        node.left = right_part
        return left_part, cls._pull(node)

    @classmethod
    def _merge(cls, left, right):
        if left is None:
            return right
        if right is None:
            return left
        if left.prior > right.prior:
            left.right = cls._merge(left.right, right)
            return cls._pull(left)
        right.left = cls._merge(left, right.left)
        return cls._pull(right)

    @classmethod
    def _erase(cls, node, x):
        if node is None:
            return None, False
        if x < node.key:
            node.left, erased = cls._erase(node.left, x)
            return cls._pull(node), erased
        if x > node.key:
            node.right, erased = cls._erase(node.right, x)
            return cls._pull(node), erased
        return cls._merge(node.left, node.right), True

    def __contains__(self, x):
        node = self.root
        while node is not None:
            if x < node.key:
                node = node.left
            elif x > node.key:
                node = node.right
            else:
                return True
        return False

    def __len__(self):
        return self._size(self.root)

    def __bool__(self):
        return self.root is not None

    def __iter__(self):
        stack = []
        node = self.root
        while stack or node is not None:
            while node is not None:
                stack.append(node)
                node = node.left
            node = stack.pop()
            yield node.key
            node = node.right

    def size(self):
        return len(self)

    def empty(self):
        return len(self) == 0

    def count(self, x):
        return 1 if x in self else 0

    def find(self, x):
        node = self.root
        answer = 0
        while node is not None:
            if x < node.key:
                node = node.left
            elif x > node.key:
                answer += self._size(node.left) + 1
                node = node.right
            else:
                return answer + self._size(node.left)
        return None

    def insert(self, x):
        if x in self:
            return False
        left, right = self._split(self.root, x)
        self.root = self._merge(self._merge(left, self._Node(x)), right)
        return True

    def erase(self, x):
        self.root, erased = self._erase(self.root, x)
        return erased

    def lower_bound(self, x):
        node = self.root
        answer = None
        while node is not None:
            if node.key >= x:
                answer = node.key
                node = node.left
            else:
                node = node.right
        return answer

    def upper_bound(self, x):
        node = self.root
        answer = None
        while node is not None:
            if node.key > x:
                answer = node.key
                node = node.left
            else:
                node = node.right
        return answer

    def find_by_order(self, k):
        if k < 0 or k >= len(self):
            return None
        node = self.root
        while node is not None:
            left_size = self._size(node.left)
            if k < left_size:
                node = node.left
            elif k == left_size:
                return node.key
            else:
                k -= left_size + 1
                node = node.right
        return None

    def order_of_key(self, x):
        node = self.root
        answer = 0
        while node is not None:
            if x <= node.key:
                node = node.left
            else:
                answer += self._size(node.left) + 1
                node = node.right
        return answer

    def __getitem__(self, k):
        value = self.find_by_order(k)
        if value is None:
            raise IndexError("OrderedSet index out of range")
        return value
```

Файл реализации: [Python3](Part-01-Ordered-set/examples/ordered_set_treap.py).

</details>

<details>
<summary><strong>Python3: пример использования</strong></summary>

```python
from ordered_set_treap import OrderedSet


def print_set(name, s):
    print(f"{name} = {{{','.join(map(str, s))}}}")


s = OrderedSet()
for x in [6, 1, 1, 7, 7, 5, 4, 4, 2]:
    s.insert(x)

print_set("s", s)
print("size =", s.size())
print("empty =", s.empty())
print("count(7) =", s.count(7))
print("count(3) =", s.count(3))
print("find(6) =", s.find(6))
print("find(3) =", s.find(3))
print("lower_bound(3) =", s.lower_bound(3))
print("upper_bound(5) =", s.upper_bound(5))
print("find_by_order(0) =", s.find_by_order(0))
print("find_by_order(3) =", s.find_by_order(3))
print("s[4] =", s[4])
print("order_of_key(5) =", s.order_of_key(5))
print("erase(4) =", s.erase(4))
print_set("s", s)
print("erase(4) =", s.erase(4))
print_set("s", s)
print("insert(3) =", s.insert(3))
print("insert(3) =", s.insert(3))
print_set("s", s)
```

Вывод программы:

```text
s = {1,2,4,5,6,7}
size = 6
empty = False
count(7) = 1
count(3) = 0
find(6) = 4
find(3) = None
lower_bound(3) = 4
upper_bound(5) = 6
find_by_order(0) = 1
find_by_order(3) = 5
s[4] = 6
order_of_key(5) = 3
erase(4) = True
s = {1,2,5,6,7}
erase(4) = False
s = {1,2,5,6,7}
insert(3) = True
insert(3) = False
s = {1,2,3,5,6,7}
```

Файл примера: [Python3](Part-01-Ordered-set/examples/example-03.py).

Файл тестов: [Python3](Part-01-Ordered-set/examples/test_ordered_set_treap.py).

</details>

> [!IMPORTANT]
> Если вы планируете участвовать в очных олимпиадах, всё равно рекомендуется уверенно освоить `std::set` в C++.

## 6. `std::multiset` и его отличия от `std::set`

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

Файл примера: [C++](Part-02-Bounds-and-multiset/examples/example-01.cpp).

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

## 7. Продвинутые операции: `lower_bound` и `upper_bound`

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

Полный файл примера: [C++](Part-02-Bounds-and-multiset/examples/example-02.cpp).

---

## 8. У `set` и `multiset` нет индексации!

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

Файл примера: [C++](Part-02-Bounds-and-multiset/examples/example-03.cpp).

</details>

## 9. `std::map` в C++

Контейнер `std::map` хранит пары вида

```text
ключ -> значение
```

и при этом ключи автоматически упорядочены.

На олимпиадах `map` чаще всего используют для:

- подсчёта частот;
- хранения по каждому ключу дополнительной информации: сколько раз встретился ключ, какая сумма значений или весов с ним связана, где было первое или последнее вхождение, какой ответ с ним связан;
- запросов по порядку ключей: минимальный и максимальный ключ, первый ключ `>= x`, первый ключ `> x`, предыдущий и следующий ключ;
- иногда — для сжатия координат.

> [!NOTE]
> `map` полезен и тогда, когда по значению нужно хранить данные, и тогда, когда важен порядок ключей.

---

## 10. Базовые операции с `map`

Создание:

```cpp
map<int, int> mp;
```

Полезные операции:

```cpp
mp[x] = 5;   // записать значение по ключу x
mp[x]++;     // увеличить значение
mp.erase(x); // удалить ключ x
mp.find(x);  // поиск итератор на ключ x
mp.count(x); // 0 или 1
mp.size();   // количество различных ключей
```

Обход парами `(ключ, значение)`:

```cpp
for (auto [key, value] : mp) {
    cout << key << ' ' << value << '\n';
}
```

Пары выводятся в порядке возрастания ключей.

---

## 11. Частоты и количество различных значений

Одна из самых типичных задач на `map` — подсчёт частот.

Пример:

```cpp
map<int, int> cnt;
for (int x : a) {
    cnt[x]++;
}
```

После этого:

- `cnt[x]` — сколько раз встретилось число `x`;
- `cnt.size()` — сколько различных значений было в массиве.

Это хороший момент, чтобы сравнить `set` и `map`:

- `set` хранит только факт присутствия значения;
- `map` хранит по ключу ещё и связанную с ним информацию.

> [!IMPORTANT]
> Если нужна только уникальность, часто достаточно `set`. Если нужна частота или любая другая информация по ключу, обычно уже нужен `map`.

Ниже — простой пример, который показывает запись значения по ключу, увеличение счётчика, поиск, `count`, `erase`, `size` и обход `map`.

<details>
<summary><strong>Пример: базовые операции с <code>map</code></strong></summary>

```cpp
#include <iostream>
#include <map>
#include <vector>
using namespace std;

void print(const string &name, const auto &mp) {
    cout << name << " = {";
    int i = 0;
    for (const auto &[key, value] : mp) {
        if (i > 0) cout << ", ";
        cout << key << ": " << value;
        i++;
    }
    cout << "}" << '\n';
}

int main() {
    vector<int> a = {6, 1, 1, 7, 7, 5, 4, 4, 2};

    // Считаем частоты значений через map
    map<int, int> cnt;
    for (int x : a) {
        cnt[x]++;
    }

    // Количество различных ключей.
    cout << cnt.size() << '\n';

    // Вывод всех пар ключ -> значение.
    print("cnt", cnt);

    // Поиск по ключу.
    for (int x : {7, 3}) {
        cout << "Find " << x << ": ";
        auto it = cnt.find(x);
        if (it == cnt.end()) {
            cout << "fail";
        } else {
            cout << "ok, value = " << it->second;
        }
        cout << ", count = " << cnt.count(x) << '\n';
    }

    // Удаление ключей.
    for (int x : {7, 3, 1, 7}) {
        cout << "Erase " << x << ": ";
        auto it = cnt.find(x);
        if (it == cnt.end()) {
            cout << "fail";
        } else {
            cout << "ok";
            cnt.erase(it);
        }
        print(", cnt", cnt);
    }

    return 0;
}
```

Вывод программы:

```text
6
cnt = {1: 2, 2: 1, 4: 2, 5: 1, 6: 1, 7: 2}
Find 7: ok, value = 2, count = 1
Find 3: fail, count = 0
Erase 7: ok, cnt = {1: 2, 2: 1, 4: 2, 5: 1, 6: 1}
Erase 3: fail, cnt = {1: 2, 2: 1, 4: 2, 5: 1, 6: 1}
Erase 1: ok, cnt = {2: 1, 4: 2, 5: 1, 6: 1}
Erase 7: fail, cnt = {2: 1, 4: 2, 5: 1, 6: 1}
```

Файл примера: [C++](Part-03-Map-and-frequencies/examples/example-01.cpp).

</details>

---

## 12. Очень важная оговорка про `mp[x]`

Выражение

```cpp
mp[x]
```

> [!WARNING]
> Выражение `mp[x]` не просто читает значение по ключу `x`. Если такого ключа ещё не было, он **создаётся автоматически**, а значение инициализируется значением по умолчанию.

Для чисел это обычно `0`, поэтому запись

```cpp
cnt[x]++
```

так удобна в задачах на частоты.

Но для проверки существования ключа это может быть ловушкой. Если написать:

```cpp
if (mp[x]) {
    ...
}
```

то ключ `x` может появиться в `map` просто из-за самой проверки.

> [!IMPORTANT]
> Для проверки существования ключа используйте `find` или `count`, а не `mp[x]`.

Поэтому для проверки существования надо использовать:

```cpp
if (mp.find(x) != mp.end()) {
    ...
}
```

или

```cpp
if (mp.count(x) > 0) {
    ...
}
```

---

## 13. Минимальный и максимальный ключ, `lower_bound` у `map`

Так как `map` упорядочен по ключам, то здесь работают те же идеи, что и у `set`:

- `mp.begin()->first` — минимальный ключ;
- `prev(mp.end())->first` — максимальный ключ;
- `mp.lower_bound(x)` — первый ключ, не меньший `x`;
- `mp.upper_bound(x)` — первый ключ, строго больший `x`.

Это особенно полезно в задачах, где у каждого значения есть дополнительная информация, но ordered-поиск всё равно нужен.

> [!IMPORTANT]
> Для `map` нужно вызывать именно методы контейнера `mp.lower_bound(x)` и `mp.upper_bound(x)`, а не `std::lower_bound` по итераторам.

Как и для `set`, нужно использовать именно методы контейнера:

```cpp
mp.lower_bound(x);
mp.upper_bound(x);
```

а не `std::lower_bound` по итераторам.

Например, можно сгенерировать случайные числа, сгруппировать их по остатку от деления на `10`, а затем через `lower_bound` и `upper_bound` посчитать, сколько чисел попало в диапазон остатков `[3, 7]`.

<details>
<summary><strong>Пример: гистограмма по группам и ordered-запросы у <code>map</code></strong></summary>

```cpp
#include <cstdlib>
#include <iostream>
#include <map>
using namespace std;

int main() {
    srand(12345);
    map<int, int> cnt;
    const int n = 100;

    // Генерируем случайные числа и считаем остатки по модулю 10.
    for (int i = 0; i < n; i++) {
        int x = rand() % 10;
        cnt[x]++;
    }

    // Количество чисел в каждой группе.
    for (auto [key, value] : cnt) {
        cout << key << ": " << value << '\n';
    }

    // Минимальный и максимальный ключ.
    cout << "min key = " << cnt.begin()->first << '\n';
    cout << "max key = " << cnt.rbegin()->first << '\n';

    // Суммируем количества по ключам из диапазона [3, 7].
    int sum = 0;
    auto left = cnt.lower_bound(3);
    auto right = cnt.upper_bound(7);
    for (auto it = left; it != right; ++it) {
        sum += it->second;
    }
    cout << "sum on [3, 7] = " << sum << '\n';
}
```

Один из возможных выводов программы:

```text
0: 16
1: 6
2: 9
3: 6
4: 15
5: 8
6: 9
7: 13
8: 12
9: 6
min key = 0
max key = 9
sum on [3, 7] = 51
```

Файл примера: [C++](Part-03-Map-and-frequencies/examples/example-02.cpp).

</details>

---

## 14. `map` по убыванию

Если хочется хранить ключи по убыванию, можно написать:

```cpp
map<int, int, greater<int>> mp;
```

> [!NOTE]
> Это не самый частый приём в базовых задачах, но полезно знать, что он существует и полностью аналогичен `set<int, greater<int>>`.

---

## 15. Что есть в Python3?

Для задач на частоты и соответствие ключа значению в Python3 главным инструментом будет `dict`, о котором мы узнаем в следующей главе.

> [!TIP]
> Если в Python3 нужно хранить значение по ключу или считать частоты, первая естественная структура данных — `dict`.

## 16. Что такое хеш-таблица

> [!CAUTION]
> Главное, что нужно знать о хеш-таблице: её лучше не использовать, если можно обойтись без неё.
> Несмотря на среднее $O(1)$, худший случай у операций с хеш-таблицей — $O(n)$.
> Все популярные хеш-функции и способы сломать решение анти-хеш тестами давно известны, поэтому программу можно заставить работать за $O(n^2)$.

В предыдущих главах мы в основном работали с ordered-структурами: `set`, `multiset`, `map` из C++.
Они реализованы как самобалансирующиеся двоичные деревья поиска.

У такого подхода есть сильная сторона: ключи всегда хранятся в отсортированном порядке, поэтому доступны `lower_bound`, `upper_bound`, поиск соседей, минимум и максимум.
Цена за это — основные операции работают за $O(\log n)$.

Хеш-таблица устроена по-другому: по ключу вычисляется хеш, и по нему элемент попадает в одну из корзин.
Если порядок не нужен, такой подход обычно даёт среднее $O(1)$ на вставку, удаление и поиск.

> [!IMPORTANT]
> Главное отличие от самобалансирующегося дерева поиска: хеш-таблица не поддерживает порядок ключей.
> Здесь нет `lower_bound`, `upper_bound` и автоматического sorted-обхода.

> [!NOTE]
> В Python3 стандартные `set` и `dict` — это hash-based структуры.
> В C++ их ближайшие аналоги — `std::unordered_set` и `std::unordered_map`.

---

## 17. Python3: `set`

`set` в Python3 — это хеш-таблица для хранения уникальных значений.

Полезные операции:

```python
s = set()      # создание множества
s.add(x)       # добавить x
s.discard(x)   # удалить x, если он есть
x in s         # проверка наличия x
len(s)         # количество элементов
```

Обход:

```python
for x in s:
    print(x)
```

> [!TIP]
> `discard(x)` сработает, даже если элемента `x` в множестве нет.
> Не рекомендуется использовать метод `remove(x)`: в такой ситуации он выбросит исключение.

---

## 18. Python3: `dict`, `defaultdict`, `Counter`

Если по ключу нужно хранить произвольное значение, базовая структура в Python3 — `dict`.

Полезные операции:

```python
mp = {}                       # пустой словарь
mp[key] = value               # записать значение по ключу key
key in mp                     # проверка наличия ключа key
del mp[key]                   # удалить ключ key
len(mp)                       # количество различных ключей
```

> [!WARNING]
> Для обычного `dict` нельзя писать `mp[key] += 1`, если ключ `key` ещё не был добавлен.
> В такой ситуации будет ошибка `KeyError`, поэтому для частот на олимпиадах обычно удобнее `defaultdict(int)` или `Counter`.

Обход всех элементов словаря:

```python
for key, value in mp.items():
    print(key, value)
```

> [!NOTE]
> `dict` в Python3 тоже реализован как хеш-таблица.
> В среднем основные операции работают за $O(1)$.

> [!IMPORTANT]
> `dict` сохраняет порядок вставки.
> Например, если вы добавили ключи в порядке `10`, `3`, `7`, то при обходе `mp.items()` увидите их именно в порядке `10`, `3`, `7`.
> Но это не sorted-порядок по ключу: `dict` не перестроит их в `3`, `7`, `10`, как это делает `map` в C++.

> [!IMPORTANT]
> Для олимпиад удобно держать в голове такие рекомендации:
>
> - `dict` — когда нужен общий контейнер `ключ -> значение`.
> - `defaultdict(int)` — когда нужно считать частоты и хочется писать `cnt[x] += 1`.
> - `Counter` — когда нужно быстро посчитать частоты готового массива, строки или списка.

```python
from collections import defaultdict, Counter

cnt = defaultdict(int)
cnt[x] += 1

freq = Counter(a)
```

> [!WARNING]
> У `defaultdict(int)` обращение `cnt[x]` создаёт новый ключ `x`, если его раньше не было.
> Это удобно для подсчёта, но для проверки существования ключа лучше писать `x in cnt`.

---

## 19. Аналоги в C++: `std::unordered_set` и `std::unordered_map`

В C++ прямые аналоги Python-структур из этой главы — это `std::unordered_set` и `std::unordered_map`.

Базовые операции с `unordered_set`:

```cpp
unordered_set<int> s; // пустое множество
s.insert(x);          // добавить x
s.erase(x);           // удалить x
s.count(x);           // 0 или 1
s.size();             // количество элементов
```

Базовые операции с `unordered_map`:

```cpp
unordered_map<string, int> cnt; // пустой словарь
cnt[key] = value;               // записать значение по ключу key
cnt[key]++;                     // увеличить счётчик или частоту
cnt.erase(key);                 // удалить ключ key
cnt.find(key);                  // итератор на ключ key или cnt.end()
cnt.count(key);                 // 0 или 1
cnt.size();                     // количество различных ключей
```

> [!NOTE]
> Примеры ниже намеренно дублируют друг друга на Python3 и C++.
> Так проще увидеть, какие структуры являются прямыми аналогами.

> [!WARNING]
> `unordered_set` и `unordered_map` не хранят элементы в отсортированном порядке.
> Поэтому здесь нельзя сделать `lower_bound(x)`, `upper_bound(x)`, быстро найти минимальный или максимальный ключ, а также ближайший ключ слева или справа от `x`.

---

## 20. Пример: `set` в Python3 и `unordered_set` в C++

Храним только уникальные слова, быстро проверяем наличие и удаляем элементы.

<details>
<summary><strong>Python3: базовые операции с <code>set</code></strong></summary>

```python
def print_set(name, s):
    print(f"{name} = {{{','.join(s)}}}")


words = ["pear", "apple", "kiwi", "pear", "plum", "apple"]

# В set храним только уникальные слова.
s = set()
for word in words:
    s.add(word)

# Количество различных слов.
print(len(s))

print_set("s", s)

# Проверка принадлежности.
for word in ["pear", "mango"]:
    print(f"Have {word}: {'yes' if word in s else 'no'}")

# Удаление элементов.
for word in ["kiwi", "mango", "apple"]:
    print(f"Delete {word}: ", end="")
    if word in s:
        print("ok", end="")
        s.remove(word)
    else:
        print("fail", end="")
    print_set(", s", s)
```

Один из возможных выводов программы:

```text
4
s = {pear,apple,kiwi,plum}
Have pear: yes
Have mango: no
Delete kiwi: ok, s = {pear,apple,plum}
Delete mango: fail, s = {pear,apple,plum}
Delete apple: ok, s = {pear,plum}
```

Файл примера: [Python3](Part-04-Hashing-and-pitfalls/examples/example-01.py).

</details>

<details>
<summary><strong>C++: аналогичные операции с <code>unordered_set</code></strong></summary>

```cpp
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

void print_set(const string &name, const auto &s) {
    cout << name << " = {";
    bool first = true;
    for (const string &value : s) {
        if (!first) cout << ',';
        cout << value;
        first = false;
    }
    cout << "}" << '\n';
}

int main() {
    vector<string> words = {"pear", "apple", "kiwi", "pear", "plum", "apple"};

    // В unordered_set храним только уникальные слова.
    unordered_set<string> s;
    for (const string &word : words) {
        s.insert(word);
    }

    // Количество различных слов.
    cout << s.size() << '\n';

    print_set("s", s);

    // Проверка принадлежности.
    for (const string &word : vector<string>{"pear", "mango"}) {
        cout << "Have " << word << ": " << (s.count(word) ? "yes" : "no") << '\n';
    }

    // Удаление элементов.
    for (const string &word : vector<string>{"kiwi", "mango", "apple"}) {
        cout << "Delete " << word << ": ";
        auto it = s.find(word);
        if (it == s.end()) {
            cout << "fail";
        } else {
            cout << "ok";
            s.erase(it);
        }
        print_set(", s", s);
    }
}
```

Один из возможных выводов программы:

```text
4
s = {plum,kiwi,apple,pear}
Have pear: yes
Have mango: no
Delete kiwi: ok, s = {plum,apple,pear}
Delete mango: fail, s = {plum,apple,pear}
Delete apple: ok, s = {plum,pear}
```

Файл примера: [C++](Part-04-Hashing-and-pitfalls/examples/example-01.cpp).

</details>

---

## 21. Пример: `defaultdict(int)` в Python3 и `unordered_map` в C++

Теперь та же идея, но по каждому слову храним ещё и частоту.

<details>
<summary><strong>Python3: подсчёт частот через <code>defaultdict(int)</code></strong></summary>

```python
from collections import defaultdict


def print_dict(name, mp):
    parts = [f"{key}: {value}" for key, value in mp.items()]
    print(f"{name} = {{{', '.join(parts)}}}")


words = ["pear", "apple", "kiwi", "pear", "plum", "apple"]

# Считаем частоты слов.
cnt = defaultdict(int)
for word in words:
    cnt[word] += 1

# Количество различных ключей.
print(len(cnt))

print_dict("cnt", cnt)

# Поиск по ключу.
for word in ["pear", "mango"]:
    if word in cnt:
        print(f"Find {word}: ok, value = {cnt[word]}")
    else:
        print(f"Find {word}: fail")

# Удаление ключей.
for word in ["pear", "mango", "apple"]:
    print(f"Delete {word}: ", end="")
    if word in cnt:
        print("ok", end="")
        del cnt[word]
    else:
        print("fail", end="")
    print_dict(", cnt", cnt)
```

Вывод программы:

```text
4
cnt = {pear: 2, apple: 2, kiwi: 1, plum: 1}
Find pear: ok, value = 2
Find mango: fail
Delete pear: ok, cnt = {apple: 2, kiwi: 1, plum: 1}
Delete mango: fail, cnt = {apple: 2, kiwi: 1, plum: 1}
Delete apple: ok, cnt = {kiwi: 1, plum: 1}
```

Файл примера: [Python3](Part-04-Hashing-and-pitfalls/examples/example-02.py).

</details>

<details>
<summary><strong>C++: аналогичные операции с <code>unordered_map</code></strong></summary>

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

void print_dict(const string &name, const auto &mp) {
    cout << name << " = {";
    bool first = true;
    for (const auto &[key, value] : mp) {
        if (!first) cout << ", ";
        cout << key << ": " << value;
        first = false;
    }
    cout << "}" << '\n';
}

int main() {
    vector<string> words = {"pear", "apple", "kiwi", "pear", "plum", "apple"};

    // Считаем частоты слов.
    unordered_map<string, int> cnt;
    for (const string &word : words) {
        cnt[word]++;
    }

    // Количество различных ключей.
    cout << cnt.size() << '\n';

    print_dict("cnt", cnt);

    // Поиск по ключу.
    for (const string &word : vector<string>{"pear", "mango"}) {
        auto it = cnt.find(word);
        if (it == cnt.end()) {
            cout << "Find " << word << ": fail" << '\n';
        } else {
            cout << "Find " << word << ": ok, value = " << it->second << '\n';
        }
    }

    // Удаление ключей.
    for (const string &word : vector<string>{"pear", "mango", "apple"}) {
        cout << "Delete " << word << ": ";
        auto it = cnt.find(word);
        if (it == cnt.end()) {
            cout << "fail";
        } else {
            cout << "ok";
            cnt.erase(it);
        }
        print_dict(", cnt", cnt);
    }
}
```

Один из возможных выводов программы:

```text
4
cnt = {plum: 1, kiwi: 1, apple: 2, pear: 2}
Find pear: ok, value = 2
Find mango: fail
Delete pear: ok, cnt = {plum: 1, kiwi: 1, apple: 2}
Delete mango: fail, cnt = {plum: 1, kiwi: 1, apple: 2}
Delete apple: ok, cnt = {plum: 1, kiwi: 1}
```

Файл примера: [C++](Part-04-Hashing-and-pitfalls/examples/example-02.cpp).

</details>

---

## 22. Как защищаться от анти-хеш тестов

У hash-based структур есть неприятная особенность: в худшем случае они могут деградировать до линейного времени.

На обычных тестах это редко заметно. Но на платформах со взломами (например, Codeforces) анти-хеш тесты будут с вероятностью $100%$: ключи специально подберут так, чтобы контейнер начал работать намного хуже.

> [!WARNING]
> Это относится и к Python3 `set`/`dict`, и к C++ `unordered_set`/`unordered_map`.
> Среднее $O(1)$ не означает гарантированное $O(1)$ в худшем случае.

> [!IMPORTANT]
> Поэтому не используйте хеш-таблицу, если можно обойтись без неё.

### Python3

Цель — поменять хеш-функцию со стандартной на безопасную.Статья: https://codeforces.com/blog/entry/62393

В Python мы оборачиваем каждый ключ в свой класс и переопределяем для него `__hash__`.

> [!IMPORTANT]
> Это уже не обычные `int`-ключи, а отдельный тип.
> То есть вместо `x` в `dict` или `set` нужно класть `SafeInt(x)`.

> [!WARNING]
> Такой подход обычно тяжелее по времени и памяти, чем работа с обычными `int`. Поэтому не используйте хеш-таблицы на Codeforces, если можно их не использовать.

<details>
<summary><strong>Python3: обёртка над <code>int</code> со своим <code>__hash__</code></strong></summary>

```python
from random import randrange

# 64-битная арифметика по модулю 2^64, как в C++ unsigned long long.
MASK64 = (1 << 64) - 1

# Один случайный сдвиг на весь запуск программы.
RANDOM = randrange(1 << 64)


# Тот же splitmix64, что часто используют в C++ custom_hash.
def splitmix64(x):
    x = (x + 0x9e3779b97f4a7c15) & MASK64
    x = ((x ^ (x >> 30)) * 0xbf58476d1ce4e5b9) & MASK64
    x = ((x ^ (x >> 27)) * 0x94d049bb133111eb) & MASK64
    return (x ^ (x >> 31)) & MASK64


# Обёртка над int со своей хеш-функцией.
class SafeInt:
    __slots__ = ("x",)

    def __init__(self, x):
        self.x = x

    def __hash__(self):
        # Перемешиваем ключ и случайный сдвиг.
        return splitmix64(self.x + RANDOM)

    def __eq__(self, other):
        # Равенство определяется исходным значением ключа.
        return isinstance(other, SafeInt) and self.x == other.x


data = [10, 20, 10, 35, 20, 10]

# used хранит уникальные ключи, cnt -- их частоты.
used = set()
cnt = {}
for x in data:
    # Вместо int кладём в hash-структуры объекты SafeInt.
    key = SafeInt(x)
    used.add(key)
    cnt[key] = cnt.get(key, 0) + 1

# Для запросов тоже оборачиваем число в SafeInt.
print(f"10 in used = {'yes' if SafeInt(10) in used else 'no'}")
print(f"15 in used = {'yes' if SafeInt(15) in used else 'no'}")
print(f"count[10] = {cnt.get(SafeInt(10), 0)}")
print(f"count[20] = {cnt.get(SafeInt(20), 0)}")

# Печатаем исходные значения, а не объекты SafeInt.
print("keys = {", end="")
first = True
for key in used:
    if not first:
        print(",", end="")
    print(key.x, end="")
    first = False
print("}")
```

Один из возможных выводов программы:

```text
10 in used = yes
15 in used = no
count[10] = 3
count[20] = 2
keys = {10,20,35}
```

Файл примера: [Python3](Part-04-Hashing-and-pitfalls/examples/example-03.py).

</details>



### C++

Цель та же самая — поменять хеш-функцию. В C++ стандартный соревновательный приём — `custom_hash` на основе `splitmix64`. Статья: https://codeforces.com/blog/entry/62393

К нему обычно добавляют ещё две настройки:

- `reserve(...)`, чтобы заранее выделить место;
- `max_load_factor(...)`, чтобы уменьшить среднюю длину цепочек или плотность бакетов.

<details>
<summary><strong>C++: <code>custom_hash</code> для <code>unordered_set</code> и <code>unordered_map</code></strong></summary>

```cpp
#include <chrono>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // Качественно перемешиваем биты числа.
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        // Один случайный сдвиг на весь запуск программы.
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int main() {
    vector<long long> data = {10, 20, 10, 35, 20, 10};

    // Подключаем custom_hash и для множества, и для словаря.
    unordered_set<long long, custom_hash> used;
    unordered_map<long long, int, custom_hash> cnt;

    // Заранее выделяем место и уменьшаем среднюю плотность бакетов.
    used.reserve(1024);
    used.max_load_factor(0.25f);
    cnt.reserve(1024);
    cnt.max_load_factor(0.25f);

    // Заполняем set уникальными ключами, а map -- частотами.
    for (long long x : data) {
        used.insert(x);
        cnt[x]++;
    }

    // Проверка наличия и чтение частот.
    cout << "10 in used = " << (used.count(10) ? "yes" : "no") << '\n';
    cout << "15 in used = " << (used.count(15) ? "yes" : "no") << '\n';
    cout << "count[10] = " << cnt.find(10)->second << '\n';
    cout << "count[20] = " << cnt.find(20)->second << '\n';

    cout << "keys = {";
    bool first = true;
    for (long long x : used) {
        if (!first) cout << ',';
        cout << x;
        first = false;
    }
    cout << "}" << '\n';
}
```

Один из возможных выводов программы:

```text
10 in used = yes
15 in used = no
count[10] = 3
count[20] = 2
keys = {35,20,10}
```

Файл примера: [C++](Part-04-Hashing-and-pitfalls/examples/example-03.cpp).

</details>
