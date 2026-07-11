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

Файл примера: [C++](examples/example-01.cpp).

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
<summary><strong>Пример: вставка, поиск и удаление элементов в `set` по убыванию</strong></summary>

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

Файл примера: [C++](examples/example-02.cpp).

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

Файл реализации: [Python3](examples/ordered_set_treap.py).

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

Файл примера: [Python3](examples/example-03.py).

Файл тестов: [Python3](examples/test_ordered_set_treap.py).

</details>

> [!IMPORTANT]
> Если вы планируете участвовать в очных олимпиадах, всё равно рекомендуется уверенно освоить `std::set` в C++.