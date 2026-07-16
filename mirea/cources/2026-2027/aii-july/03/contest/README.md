# Разбор задач

## A. Различные значения

<details>
<summary>Текстовый разбор</summary>

Прочитаем элементы, вставим их в `set`, чтобы оставить только уникальные, а затем выведем их на экран. В C++ этого достаточно, потому что `set` уже хранит элементы в отсортированном порядке.

В Python3 контейнер `set` является хеш-таблицей, поэтому понадобится сначала собрать уникальные элементы, потом преобразовать их в список, отсортировать и только после этого вывести.

Асимптотика: $O(n \log(n))$ по времени и $O(n)$ по памяти.

</details>

<details>
<summary>Решение на C++</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем элементы и добавляем их в set:
    int n; cin >> n;
    set<int> s;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        s.insert(x);
    }
    // вывод уникальных элементов на экран:
    for (auto item : s)
        cout << item << ' ';
    cout << '\n';
}
main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
```

</details>

<details>
<summary>Решение на Python3</summary>

```python
def solve():
    # читаем элементы и добавляем их в set:
    n = int(input())
    s = set()
    i = 0
    while i < n:
        for x in map(int, input().split()):
            s.add(x)
            i += 1
            if i == n:
                break
    # вывод уникальных элементов на экран:
    print(" ".join(map(str, sorted(s))))


tt = int(input())
for _ in range(tt):
    solve()
```

</details>

## B. Первое и последнее вхождение

<details>
<summary>Текстовый разбор</summary>

Прочитаем элементы и создадим два словаря. Первый словарь будет хранить самую первую позицию каждого элемента в массиве, а второй словарь — самую последнюю. Заполнить словари можно, пройдя по массиву один раз слева направо: поиском по словарю проверяем, встречается ли элемент впервые, и, если да, запоминаем первую позицию. Последнюю позицию при этом просто обновляем.

При обработке запросов ищем элемент в одном из словарей. Если он не найден, то выводим $-1$, иначе выводим крайние левую и правую позиции.

Асимптотика: $O(n \log(n))$ при использовании самобалансирующихся деревьев поиска и $O(n)$ при использовании хеш-таблиц.

</details>

<details>
<summary>Решение на C++</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем элементы и запоминаем их позиции в map:
    int n, q; cin >> n >> q;
    map<int, int> firstPos, lastPos;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        // ищем последнюю позицию
        auto iter = lastPos.find(x);
        if (iter == lastPos.end()) {
            // не найдена - элемент ещё не встречался
            firstPos[x] = i;
            lastPos[x] = i;
        } else {
            // найдена - меняем только последнюю позицию
            iter->second = i;
        }
    }
    // читаем и отвечаем на запросы:
    while (q --> 0) {
        int x; cin >> x;
        auto iter = lastPos.find(x);
        if (iter == lastPos.end())
            cout << "-1\n";
        else // найден:
            cout << firstPos[x] << ' ' << iter->second << '\n';
    }
}
main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
```

</details>

<details>
<summary>Решение на Python3</summary>

```python
def solve():
    # читаем элементы и запоминаем их позиции в map:
    n, q = map(int, input().split())
    firstPos, lastPos = {}, {}
    i = 1
    while i <= n:
        for x in map(int, input().split()):
            # ищем последнюю позицию
            if x not in lastPos:
                # не найдена - элемент ещё не встречался
                firstPos[x] = i
                lastPos[x] = i
            else:
                # найдена - меняем только последнюю позицию
                lastPos[x] = i
            i += 1
            if i > n:
                break
    # читаем и отвечаем на запросы:
    while q > 0:
        for x in map(int, input().split()):
            if x not in lastPos:
                print(-1)
            else:  # найден:
                print(firstPos[x], lastPos[x])
            q -= 1
            if q == 0:
                break


tt = int(input())
for _ in range(tt):
    solve()
```

</details>

## C. Стек на количество уникальных элементов

<details>
<summary>Текстовый разбор</summary>

**Первый способ.** Храним стек из элементов в порядке их добавления, а также словарь с количеством каждого элемента. Для `std::map<int, int>` минимумом будет `*begin()`, максимумом — `*rbegin()`, а количеством уникальных элементов — `size()`. При удалении сначала достаём элемент из стека, а затем уменьшаем его количество в словаре. Если оно стало нулевым, то удаляем его при помощи метода `erase`.

Асимптотика: $O((n+q) \log(n+q))$.

**Второй способ.** Делаем то же самое, но теперь храним хеш-таблицу вместо сбалансированного дерева поиска. В C++ это `std::unordered_map<int, int>`, а в Python3 — `dict`. Так как мы не сможем бесплатно получать минимум и максимум, придётся создать и поддерживать ещё два стека: один на минимум, а второй — на максимум.

Асимптотика: $O(n+q)$.

</details>

<details>
<summary>Решение на C++: способ 1</summary>

```cpp
// храним одновременно и stack, и map. Минимум, максимум и количество уникальных
// берём из map, а при удалении вынимаем значение из stack, уменьшаем его количество и,
// если оно стало равно нулю, удаляем его из map.
#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем данные
    int n; cin >> n;
    map<int, int> cnt;
    stack<int> st;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        st.push(x);
        cnt[x]++;
    }
    // обрабатываем запросы
    int q; cin >> q;
    while (q --> 0) {
        char c; cin >> c;
        if (c == '+') {
            int x; cin >> x;
            st.push(x);
            cnt[x]++;
        } else if (c == '?') {
            int Min = cnt.begin()->first;
            int Max = cnt.rbegin()->first;
            int Cnt = cnt.size();
            cout << Min << ' ' << Max << ' ' << Cnt << '\n';
        } else if (c == '-') {
            // сначала удалим из стека:
            int last = st.top();
            st.pop();
            // теперь аккуратно удалим из map:
            auto iter = cnt.find(last);
            iter->second--; // уменьшаем количество
            if (iter->second == 0) // стало равным нулю => удаляем
                cnt.erase(iter);
        }
    }
}
main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
```

</details>

<details>
<summary>Разбор решения на C++: способ 1</summary>

Здесь структура данных буквально совпадает с формулировкой идеи: стек отвечает за порядок удаления, а `map` отвечает за минимум, максимум и количество различных элементов.

Самое важное место находится в обработке запроса `-`:

```cpp
auto iter = cnt.find(last);
iter->second--;
if (iter->second == 0)
    cnt.erase(iter);
```

После удаления из стека число $\text{last}$ может ещё оставаться в структуре несколько раз. Поэтому сначала уменьшаем его счётчик, а ключ удаляем только тогда, когда количество стало равно $0$.

Это нужно потому, что число различных элементов здесь считается как `cnt.size()`. Если оставить ключ в `map` со значением $0$, то контейнер всё равно продолжит считать его существующим, и ответ на запрос `?` станет неверным.

Почему этот способ работает удобно: минимум всегда лежит в `cnt.begin()->first`, максимум — в `cnt.rbegin()->first`, а количество различных значений — в `cnt.size()`. Платим за это логарифмами, потому что все операции с `map` работают за $O(\log(n+q))$.

</details>

<details>
<summary>Решение на C++: способ 2</summary>

```cpp
// Данное решение работает за линейное время - за O(n+q). Мы храним одновременно:
// 1) стек из элементов;
// 2) стек на минимум;
// 3) стек на максимум;
// 4) хеш-таблицу с количеством каждого элемента.
// Из хеш-таблицы удаляем значения, когда их количество достигло нуля. Таким образом,
// размер хеш-таблицы и будет количеством различных элементов. А минимум и максимум
// берём с верхушки стеков.
#include <bits/stdc++.h>
using namespace std;
const int inf = 1000000007;
void solve() {
    // читаем данные
    int n; cin >> n;
    unordered_map<int, int> cnt;
    stack<int> stVal, stMin, stMax;
    // добавим бесконечности:
    stVal.push(inf);
    stMin.push(+inf);
    stMax.push(-inf);
    // теперь добавим нормальные элементы:
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        stVal.push(x);
        stMin.push(min(stMin.top(), x));
        stMax.push(max(stMax.top(), x));
        cnt[x]++;
    }
    // обрабатываем запросы
    int q; cin >> q;
    while (q --> 0) {
        char c; cin >> c;
        if (c == '+') {
            int x; cin >> x;
            stVal.push(x);
            stMin.push(min(stMin.top(), x));
            stMax.push(max(stMax.top(), x));
            cnt[x]++;
        } else if (c == '?') {
            cout << stMin.top() << ' ' << stMax.top() << ' ' << cnt.size() << '\n';
        } else if (c == '-') {
            // сначала удалим из стека:
            int last = stVal.top();
            stVal.pop(); stMin.pop(); stMax.pop();
            // теперь аккуратно удалим из хеш-таблицы:
            auto iter = cnt.find(last);
            iter->second--; // уменьшаем количество
            if (iter->second == 0) // стало равным нулю => удаляем
                cnt.erase(iter);
        }
    }
}
main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
```

</details>

<details>
<summary>Разбор решения на C++: способ 2</summary>

Здесь идея уже другая: минимум и максимум мы больше не берём из упорядоченного контейнера, а поддерживаем их отдельными стеками.

Когда в стек добавляется новое число $x$, вместе с ним синхронно обновляются ещё два стека:

```cpp
stMin.push(min(stMin.top(), x));
stMax.push(max(stMax.top(), x));
```

Из-за этого на каждой глубине основного стека мы заранее знаем минимум и максимум среди всех элементов ниже и на этой позиции. Поэтому ответ на запрос `?` можно получить сразу с верхушек `stMin` и `stMax`.

При удалении нужно снимать вершину сразу со всех трёх стеков, потому что они должны всегда оставаться одной длины и описывать одно и то же состояние структуры.

Количество различных элементов хранится в `unordered_map`. Как и в первом способе, после уменьшения счётчика ключ нужно удалить, когда его значение стало равно $0$, иначе `cnt.size()` начнёт завышать ответ.

Именно поэтому этот способ работает за линейное время: все действия со стеками — это $O(1)$, а операции с `unordered_map` в среднем тоже считаются за $O(1)$.

</details>

<details>
<summary>Решение на Python3</summary>

```python
# Данное решение работает за линейное время - за O(n+q). Мы храним одновременно:
# 1) стек из элементов;
# 2) стек на минимум;
# 3) стек на максимум;
# 4) хеш-таблицу с количеством каждого элемента.
# Из хеш-таблицы удаляем значения, когда их количество достигло нуля. Таким образом,
# размер хеш-таблицы и будет количеством различных элементов. А минимум и максимум
# берём с верхушки стеков.
inf = 1000000007


def solve():
    # читаем данные
    n = int(input())
    cnt = {}
    stVal, stMin, stMax = [], [], []
    # добавим бесконечности:
    stVal.append(inf)
    stMin.append(+inf)
    stMax.append(-inf)
    # теперь добавим нормальные элементы:
    i = 0
    while i < n:
        for x in map(int, input().split()):
            stVal.append(x)
            stMin.append(min(stMin[-1], x))
            stMax.append(max(stMax[-1], x))
            cnt[x] = cnt.get(x, 0) + 1
            i += 1
            if i == n:
                break
    # обрабатываем запросы
    q = int(input())
    while q > 0:
        query = input().split()
        c = query[0]
        if c == '+':
            x = int(query[1])
            stVal.append(x)
            stMin.append(min(stMin[-1], x))
            stMax.append(max(stMax[-1], x))
            cnt[x] = cnt.get(x, 0) + 1
        elif c == '?':
            print(stMin[-1], stMax[-1], len(cnt))
        elif c == '-':
            # сначала удалим из стека:
            last = stVal[-1]
            stVal.pop()
            stMin.pop()
            stMax.pop()
            # теперь аккуратно удалим из хеш-таблицы:
            cnt[last] -= 1  # уменьшаем количество
            if cnt[last] == 0:  # стало равным нулю => удаляем
                del cnt[last]
        q -= 1


tt = int(input())
for _ in range(tt):
    solve()
```

</details>

<details>
<summary>Разбор решения на Python3</summary>

Здесь идея та же, что и во втором способе на C++. Мы храним три согласованных стека: значения, префиксные минимумы и префиксные максимумы. Поэтому при добавлении нового числа $x$ не нужно заново пересчитывать минимум и максимум по всей структуре: достаточно сравнить $x$ с вершинами стеков $\text{stMin}$ и $\text{stMax}$.

Самый важный фрагмент:

```python
cnt[last] -= 1
if cnt[last] == 0:
    del cnt[last]
```

Словарь $\text{cnt}$ хранит количество вхождений каждого числа. Когда мы удаляем последний элемент стека, его счётчик уменьшается на $1$. Если после этого счётчик стал равен $0$, ключ нужно действительно удалить из словаря.

Это важно не только ради аккуратности. Количество различных элементов здесь считается как `len(cnt)`. Если оставить в словаре ключ со значением $0$, то такой элемент уже фактически исчез из стека, но `len(cnt)` всё равно продолжит его считать, и ответ на запрос `?` станет неверным.

</details>

## D. Ближайшая точка

<details>
<summary>Текстовый разбор</summary>

**Первый способ.** Будем читать и вставлять координаты в `std::set<int>`. На самом деле, у метода `insert` есть два возвращаемых значения. Первое — итератор на узел дерева, в значении которого записано число $x$, а второе — логическая переменная, которая равна `true`, если элемент был вставлен, и `false` иначе. Это как раз удобно, если $x$ уже присутствовал в множестве. Если элемент не был вставлен, то сразу выводим $0$, так как встретили повторяющееся значение. Иначе по итератору находим ближайших соседей справа и слева. Минимальное расстояние до них и будет ответом.

Асимптотика: $O(q \log(q))$.

**Второй способ.** Допустим, мы не знаем или не хотим использовать тот факт, что `insert` возвращает всё нужное. Тогда можно найти ближайшего соседа справа при помощи метода `lower_bound`, а затем и ближайшего соседа слева, шагнув один раз влево. Теперь, когда соседи найдены, считаем расстояние, выводим его, а затем вставляем элемент $x$.

Если $x$ уже есть в множестве, то `lower_bound(x)` вернёт итератор на сам $x$, и одно из расстояний автоматически станет равно нулю. Поэтому такой способ тоже работает.

Асимптотика: $O(q \log(q))$.

Если реализовать собственное красно-чёрное дерево с операциями `insert`, `lower_bound`, `prev` и `next`, то первые два способа проходят и на PyPy 3-64 как прямые аналоги решений на `std::set<int>`. Для первого способа получился вердикт `OK` за `687 мс` и `84 МБ`, а для второго — `OK` за `890 мс` и `81 МБ`.

**Третий способ.**

> [!WARNING]
> Данный способ содержит продвинутые техники и позволяет решить задачу на Python3 без собственной реализации дерева поиска. Он точно не для начинающих, поэтому можете пропустить его, если пока не готовы.

Давайте на минуту забудем о том, что нам нужно отвечать на запросы. Что будет, если мы все их обработаем? Верно, мы получим массив из $q$ чисел. Отсортируем его. Ура, у нас есть результат выполнения всех запросов. Но мы забыли ответить на них.

Теперь начинаем отвечать. Будем обрабатывать запросы с конца в начало. В прямом порядке запросы добавляли элементы. В обратном порядке они будут удалять элементы. Поэтому сначала удалим элемент, который был добавлен последним. Следом удалим тот, который был добавлен предпоследним, и так далее.

В данном случае удалять проще, чем добавлять. Для этого поддерживаем двусвязный список. Тогда соседей удаляемого элемента мы знаем автоматически, а само удаление из списка выполняется за $O(1)$.

Позицию удаляемого элемента ищем бинарным поиском в отсортированном массиве за $O(\log(q))$. Повторы удобно учитывать отдельным массивом `cnt`: пока количество одного и того же числа больше нуля, ответ равен $0$.

Асимптотика: $O(q \log(q))$ за счёт сортировки и бинарного поиска.

</details>

<details>
<summary>Решение на C++: способ 1</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
    set<int> s = {-1000000000, 1000000000};
    int q; cin >> q;
    while (q --> 0) {
        // читаем + вставляем + запоминаем итератор на вставленный элемент:
        int x; cin >> x;
        auto [iter, wasInserted] = s.insert(x);
        if (!wasInserted) // данный x уже есть
            cout << "0\n";
        else // расстояние до ближайшего - это минимум из расстояний до соседей:
            cout << min(*iter - *prev(iter), *next(iter) - *iter) << '\n';
    }
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
```

</details>

<details>
<summary>Разбор решения на C++: способ 1</summary>

Здесь самый важный фрагмент:

```cpp
auto [iter, wasInserted] = s.insert(x);
```

Метод `insert` возвращает пару. В `iter` попадает итератор на элемент $x$ внутри множества, а в `wasInserted` — флаг, удалось ли реально вставить новый элемент. Если $x$ уже был в `set`, флаг станет `false`, и это сразу даёт ответ $0$.

Если же вставка произошла, то выражения `prev(iter)` и `next(iter)` дают соседей слева и справа. Поэтому ответ считается сразу, без дополнительного поиска.

</details>

<details>
<summary>Решение на Python3: способ 1</summary>

```python
# Задача: D, Вердикт: OK, Время: 687 мс, Память: 84 МБ, Язык: PyPy 3-64

# -------------------------
# RedBlackTree
# -------------------------

"""Компактный RedBlackTree для задач на ordered set.

Использование:
- tree = RedBlackTree(values=())
  Создаёт дерево и по очереди вставляет все значения из values.
- tree.insert(x) -> bool
  Возвращает True, если x был вставлен, и False, если x уже был в дереве.
- tree.insert(x, with_id=True) -> (node_id, was_inserted)
  Возвращает идентификатор узла и флаг успешной вставки.
  Если x уже есть в дереве, node_id указывает на существующий узел,
  а was_inserted == False.
- tree.lower_bound_with_id(x) -> (value, node_id)
  Возвращает первый ключ >= x и его node_id.
  Если такого ключа нет, возвращает (None, 0).
- tree.lower_bound(x) -> value
  Возвращает первый ключ >= x или None.
- tree.lower_bound(x, with_id=True) -> (value, node_id)
  Возвращает тот же результат, что и lower_bound_with_id(x).
- tree.prev(node_id) -> (value, prev_node_id)
  Возвращает предыдущий ключ в inorder и его node_id.
  Если соседа слева нет, возвращает (None, 0).
- tree.next(node_id) -> (value, next_node_id)
  Возвращает следующий ключ в inorder и его node_id.
  Если соседа справа нет, возвращает (None, 0).
- tree.erase(x) -> ((next_value, next_node_id), was_erased)
  Удаляет ключ x, если он есть в дереве.
  Возвращает итератор на следующий элемент в inorder и флаг успешного удаления.
  Если x не найден, возвращает ((None, 0), False).
- tree.erase_id(node_id) -> ((next_value, next_node_id), was_erased)
  Удаляет узел по его node_id.
  Возвращает итератор на следующий элемент в inorder и флаг успешного удаления.
  Если node_id не указывает на текущий узел дерева, возвращает ((None, 0), False).

Замечание:
- node_id стабилен после поворотов и следующих вставок, потому что узлы
  хранятся в массивах и не перемещаются.
"""


class RedBlackTree:
    __slots__ = ("root", "key", "left", "right", "parent", "color", "prev_id", "next_id")

    RED = 1
    BLACK = 0

    def __init__(self, values=()):
        self.root = 0
        self.key = [0]
        self.left = [0]
        self.right = [0]
        self.parent = [0]
        self.color = [self.BLACK]
        self.prev_id = [0]
        self.next_id = [0]
        for x in values:
            self.insert(x)

    def _new_node(self, x, color, pred, succ):
        self.key.append(x)
        self.left.append(0)
        self.right.append(0)
        self.parent.append(0)
        self.color.append(color)
        self.prev_id.append(pred)
        self.next_id.append(succ)
        node = len(self.key) - 1
        if pred:
            self.next_id[pred] = node
        if succ:
            self.prev_id[succ] = node
        return node

    def _rotate_left(self, node):
        right_node = self.right[node]
        self.right[node] = self.left[right_node]
        if self.left[right_node]:
            self.parent[self.left[right_node]] = node

        parent = self.parent[node]
        self.parent[right_node] = parent
        if parent == 0:
            self.root = right_node
        elif self.left[parent] == node:
            self.left[parent] = right_node
        else:
            self.right[parent] = right_node

        self.left[right_node] = node
        self.parent[node] = right_node

    def _rotate_right(self, node):
        left_node = self.left[node]
        self.left[node] = self.right[left_node]
        if self.right[left_node]:
            self.parent[self.right[left_node]] = node

        parent = self.parent[node]
        self.parent[left_node] = parent
        if parent == 0:
            self.root = left_node
        elif self.left[parent] == node:
            self.left[parent] = left_node
        else:
            self.right[parent] = left_node

        self.right[left_node] = node
        self.parent[node] = left_node

    def _fix_insert(self, node):
        left = self.left
        right = self.right
        parent = self.parent
        color = self.color

        while node != self.root and color[parent[node]] == self.RED:
            parent_node = parent[node]
            grand = parent[parent_node]

            if parent_node == left[grand]:
                uncle = right[grand]
                if color[uncle] == self.RED:
                    color[parent_node] = self.BLACK
                    color[uncle] = self.BLACK
                    color[grand] = self.RED
                    node = grand
                else:
                    if node == right[parent_node]:
                        node = parent_node
                        self._rotate_left(node)
                        parent_node = parent[node]
                        grand = parent[parent_node]
                    color[parent_node] = self.BLACK
                    color[grand] = self.RED
                    self._rotate_right(grand)
            else:
                uncle = left[grand]
                if color[uncle] == self.RED:
                    color[parent_node] = self.BLACK
                    color[uncle] = self.BLACK
                    color[grand] = self.RED
                    node = grand
                else:
                    if node == left[parent_node]:
                        node = parent_node
                        self._rotate_right(node)
                        parent_node = parent[node]
                        grand = parent[parent_node]
                    color[parent_node] = self.BLACK
                    color[grand] = self.RED
                    self._rotate_left(grand)

        color[self.root] = self.BLACK

    def _find_node(self, x):
        node = self.root
        key = self.key
        left = self.left
        right = self.right

        while node:
            node_key = key[node]
            if x < node_key:
                node = left[node]
            elif x > node_key:
                node = right[node]
            else:
                return node
        return 0

    def _contains_node(self, node_id):
        return 0 < node_id < len(self.key) and self._find_node(self.key[node_id]) == node_id

    def _transplant(self, old_node, new_node):
        parent = self.parent[old_node]
        if parent == 0:
            self.root = new_node
        elif self.left[parent] == old_node:
            self.left[parent] = new_node
        else:
            self.right[parent] = new_node

        if new_node:
            self.parent[new_node] = parent

    def _fix_delete(self, node, node_parent):
        left = self.left
        right = self.right
        parent = self.parent
        color = self.color

        while node != self.root and color[node] == self.BLACK:
            if node == left[node_parent]:
                sibling = right[node_parent]
                if color[sibling] == self.RED:
                    color[sibling] = self.BLACK
                    color[node_parent] = self.RED
                    self._rotate_left(node_parent)
                    sibling = right[node_parent]

                sibling_left = left[sibling]
                sibling_right = right[sibling]
                if color[sibling_left] == self.BLACK and color[sibling_right] == self.BLACK:
                    color[sibling] = self.RED
                    node = node_parent
                    node_parent = parent[node]
                else:
                    if color[sibling_right] == self.BLACK:
                        color[sibling_left] = self.BLACK
                        color[sibling] = self.RED
                        self._rotate_right(sibling)
                        sibling = right[node_parent]
                        sibling_right = right[sibling]

                    color[sibling] = color[node_parent]
                    color[node_parent] = self.BLACK
                    color[sibling_right] = self.BLACK
                    self._rotate_left(node_parent)
                    node = self.root
            else:
                sibling = left[node_parent]
                if color[sibling] == self.RED:
                    color[sibling] = self.BLACK
                    color[node_parent] = self.RED
                    self._rotate_right(node_parent)
                    sibling = left[node_parent]

                sibling_left = left[sibling]
                sibling_right = right[sibling]
                if color[sibling_left] == self.BLACK and color[sibling_right] == self.BLACK:
                    color[sibling] = self.RED
                    node = node_parent
                    node_parent = parent[node]
                else:
                    if color[sibling_left] == self.BLACK:
                        color[sibling_right] = self.BLACK
                        color[sibling] = self.RED
                        self._rotate_left(sibling)
                        sibling = left[node_parent]
                        sibling_left = left[sibling]

                    color[sibling] = color[node_parent]
                    color[node_parent] = self.BLACK
                    color[sibling_left] = self.BLACK
                    self._rotate_right(node_parent)
                    node = self.root

        color[node] = self.BLACK

    def _erase_node(self, node):
        next_node = self.next_id[node]
        prev_node = self.prev_id[node]
        if prev_node:
            self.next_id[prev_node] = next_node
        if next_node:
            self.prev_id[next_node] = prev_node

        left = self.left
        right = self.right
        parent = self.parent
        color = self.color

        moved_up = node
        moved_up_original_color = color[moved_up]
        if left[node] == 0:
            fix_node = right[node]
            fix_parent = parent[node]
            self._transplant(node, fix_node)
        elif right[node] == 0:
            fix_node = left[node]
            fix_parent = parent[node]
            self._transplant(node, fix_node)
        else:
            moved_up = next_node
            moved_up_original_color = color[moved_up]
            fix_node = right[moved_up]
            if parent[moved_up] == node:
                fix_parent = moved_up
            else:
                fix_parent = parent[moved_up]
                self._transplant(moved_up, fix_node)
                right[moved_up] = right[node]
                parent[right[moved_up]] = moved_up

            self._transplant(node, moved_up)
            left[moved_up] = left[node]
            parent[left[moved_up]] = moved_up
            color[moved_up] = color[node]

        left[node] = 0
        right[node] = 0
        parent[node] = 0
        color[node] = self.BLACK
        self.prev_id[node] = 0
        self.next_id[node] = 0

        if moved_up_original_color == self.BLACK:
            self._fix_delete(fix_node, fix_parent)

        return next_node

    def _iter_pair(self, node_id):
        if node_id == 0:
            return None, 0
        return self.key[node_id], node_id

    def insert(self, x, with_id=False):
        root = self.root
        if root == 0:
            self.root = self._new_node(x, self.BLACK, 0, 0)
            return (self.root, True) if with_id else True

        key = self.key
        left = self.left
        right = self.right
        parent = self.parent
        pred = 0
        succ = 0
        node = root

        while node:
            node_key = key[node]
            if x < node_key:
                succ = node
                next_node = left[node]
                if next_node == 0:
                    new_node = self._new_node(x, self.RED, pred, succ)
                    left[node] = new_node
                    parent[new_node] = node
                    self._fix_insert(new_node)
                    return (new_node, True) if with_id else True
                node = next_node
            elif x > node_key:
                pred = node
                next_node = right[node]
                if next_node == 0:
                    new_node = self._new_node(x, self.RED, pred, succ)
                    right[node] = new_node
                    parent[new_node] = node
                    self._fix_insert(new_node)
                    return (new_node, True) if with_id else True
                node = next_node
            else:
                return (node, False) if with_id else False

    def lower_bound_with_id(self, x):
        node = self.root
        answer_node = 0
        key = self.key
        left = self.left
        right = self.right

        while node:
            if key[node] >= x:
                answer_node = node
                node = left[node]
            else:
                node = right[node]

        if answer_node == 0:
            return None, 0
        return key[answer_node], answer_node

    def lower_bound(self, x, with_id=False):
        answer, node_id = self.lower_bound_with_id(x)
        return (answer, node_id) if with_id else answer

    def prev(self, node_id):
        prev_id = self.prev_id[node_id]
        if prev_id == 0:
            return None, 0
        return self.key[prev_id], prev_id

    def next(self, node_id):
        next_id = self.next_id[node_id]
        if next_id == 0:
            return None, 0
        return self.key[next_id], next_id

    def erase(self, x):
        node = self._find_node(x)
        if node == 0:
            return (None, 0), False
        next_node = self._erase_node(node)
        return self._iter_pair(next_node), True

    def erase_id(self, node_id):
        if not self._contains_node(node_id):
            return (None, 0), False
        next_node = self._erase_node(node_id)
        return self._iter_pair(next_node), True


# -------------------------
# Основное решение
# -------------------------

BOUND = 10**9


def solve() -> None:
    points = RedBlackTree((-BOUND, BOUND))
    q = int(input())
    values = list(map(int, input().split()))
    answers = []
    for x in values:
        # читаем + вставляем + запоминаем идентификатор вставленного узла:
        node_id, was_inserted = points.insert(x, with_id=True)
        if not was_inserted:  # данный x уже есть
            answers.append("0")
        else:  # расстояние до ближайшего - это минимум из расстояний до соседей:
            left, _ = points.prev(node_id)
            right, _ = points.next(node_id)
            answers.append(str(min(x - left, right - x)))
    print("\n".join(answers))


t = int(input())
for _ in range(t):
    solve()
```

</details>

<details>
<summary>Разбор решения на Python3: способ 1</summary>

Это прямой аналог решения на `std::set<int>`, только вместо готового контейнера используется собственный `RedBlackTree` с теми же нужными операциями.

Самая важная строка здесь такая:

```python
node_id, was_inserted = points.insert(x, with_id=True)
```

Метод `insert` возвращает идентификатор узла и флаг, удалось ли реально вставить новое число. Если вставка не произошла, значит $x$ уже был в дереве, и ответ сразу равен $0$.

Если же вставка произошла, то соседи слева и справа находятся методами `prev(node_id)` и `next(node_id)`. Поэтому ответ считается ровно так же, как и в C++-версии: это минимум из двух расстояний до соседних элементов.

</details>

<details>
<summary>Решение на C++: способ 2</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
    set<int> s = {-1000000000, 1000000000};
    int q; cin >> q;
    while (q --> 0) {
        // читаем икс и ищем соседа слева и справа:
        int x; cin >> x;
        auto rightIter = s.lower_bound(x);
        auto leftIter = prev(rightIter);
        // расстояние до ближайшего - это минимум из расстояний до соседей:
        cout << min(x - *leftIter, *rightIter - x) << '\n';
        // вставляем:
        s.insert(x);
    }
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
```

</details>

<details>
<summary>Разбор решения на C++: способ 2</summary>

Здесь используется та же структура `set`, но без опоры на возвращаемое значение `insert`. Вместо этого ответ вычисляется ещё до вставки нового числа.

Ключевая строка такая:

```cpp
auto rightIter = s.lower_bound(x);
```

Метод `lower_bound(x)` возвращает первый элемент множества, который не меньше $x$. Значит, это ближайший кандидат справа. Тогда сосед слева получается как `prev(rightIter)`.

После этого ответ уже считается как минимум из двух расстояний:

```cpp
cout << min(x - *leftIter, *rightIter - x) << '\n';
```

Почему такой код корректно работает и для повторов: если число $x$ уже есть в `set`, то `lower_bound(x)` укажет ровно на него. Тогда одно из расстояний сразу станет равно $0$, и мы автоматически получим правильный ответ без отдельной проверки на дубликат.

</details>

<details>
<summary>Решение на Python3: способ 2</summary>

```python
# Вердикт: OK, Время: 890 мс, Память: 81 МБ, Язык: PyPy 3-64

# -------------------------
# RedBlackTree
# -------------------------

"""Компактный RedBlackTree для задач на ordered set.

Использование:
- tree = RedBlackTree(values=())
  Создаёт дерево и по очереди вставляет все значения из values.
- tree.insert(x) -> bool
  Возвращает True, если x был вставлен, и False, если x уже был в дереве.
- tree.insert(x, with_id=True) -> (node_id, was_inserted)
  Возвращает идентификатор узла и флаг успешной вставки.
  Если x уже есть в дереве, node_id указывает на существующий узел,
  а was_inserted == False.
- tree.lower_bound_with_id(x) -> (value, node_id)
  Возвращает первый ключ >= x и его node_id.
  Если такого ключа нет, возвращает (None, 0).
- tree.lower_bound(x) -> value
  Возвращает первый ключ >= x или None.
- tree.lower_bound(x, with_id=True) -> (value, node_id)
  Возвращает тот же результат, что и lower_bound_with_id(x).
- tree.prev(node_id) -> (value, prev_node_id)
  Возвращает предыдущий ключ в inorder и его node_id.
  Если соседа слева нет, возвращает (None, 0).
- tree.next(node_id) -> (value, next_node_id)
  Возвращает следующий ключ в inorder и его node_id.
  Если соседа справа нет, возвращает (None, 0).
- tree.erase(x) -> ((next_value, next_node_id), was_erased)
  Удаляет ключ x, если он есть в дереве.
  Возвращает итератор на следующий элемент в inorder и флаг успешного удаления.
  Если x не найден, возвращает ((None, 0), False).
- tree.erase_id(node_id) -> ((next_value, next_node_id), was_erased)
  Удаляет узел по его node_id.
  Возвращает итератор на следующий элемент в inorder и флаг успешного удаления.
  Если node_id не указывает на текущий узел дерева, возвращает ((None, 0), False).

Замечание:
- node_id стабилен после поворотов и следующих вставок, потому что узлы
  хранятся в массивах и не перемещаются.
"""


class RedBlackTree:
    __slots__ = ("root", "key", "left", "right", "parent", "color", "prev_id", "next_id")

    RED = 1
    BLACK = 0

    def __init__(self, values=()):
        self.root = 0
        self.key = [0]
        self.left = [0]
        self.right = [0]
        self.parent = [0]
        self.color = [self.BLACK]
        self.prev_id = [0]
        self.next_id = [0]
        for x in values:
            self.insert(x)

    def _new_node(self, x, color, pred, succ):
        self.key.append(x)
        self.left.append(0)
        self.right.append(0)
        self.parent.append(0)
        self.color.append(color)
        self.prev_id.append(pred)
        self.next_id.append(succ)
        node = len(self.key) - 1
        if pred:
            self.next_id[pred] = node
        if succ:
            self.prev_id[succ] = node
        return node

    def _rotate_left(self, node):
        right_node = self.right[node]
        self.right[node] = self.left[right_node]
        if self.left[right_node]:
            self.parent[self.left[right_node]] = node

        parent = self.parent[node]
        self.parent[right_node] = parent
        if parent == 0:
            self.root = right_node
        elif self.left[parent] == node:
            self.left[parent] = right_node
        else:
            self.right[parent] = right_node

        self.left[right_node] = node
        self.parent[node] = right_node

    def _rotate_right(self, node):
        left_node = self.left[node]
        self.left[node] = self.right[left_node]
        if self.right[left_node]:
            self.parent[self.right[left_node]] = node

        parent = self.parent[node]
        self.parent[left_node] = parent
        if parent == 0:
            self.root = left_node
        elif self.left[parent] == node:
            self.left[parent] = left_node
        else:
            self.right[parent] = left_node

        self.right[left_node] = node
        self.parent[node] = left_node

    def _fix_insert(self, node):
        left = self.left
        right = self.right
        parent = self.parent
        color = self.color

        while node != self.root and color[parent[node]] == self.RED:
            parent_node = parent[node]
            grand = parent[parent_node]

            if parent_node == left[grand]:
                uncle = right[grand]
                if color[uncle] == self.RED:
                    color[parent_node] = self.BLACK
                    color[uncle] = self.BLACK
                    color[grand] = self.RED
                    node = grand
                else:
                    if node == right[parent_node]:
                        node = parent_node
                        self._rotate_left(node)
                        parent_node = parent[node]
                        grand = parent[parent_node]
                    color[parent_node] = self.BLACK
                    color[grand] = self.RED
                    self._rotate_right(grand)
            else:
                uncle = left[grand]
                if color[uncle] == self.RED:
                    color[parent_node] = self.BLACK
                    color[uncle] = self.BLACK
                    color[grand] = self.RED
                    node = grand
                else:
                    if node == left[parent_node]:
                        node = parent_node
                        self._rotate_right(node)
                        parent_node = parent[node]
                        grand = parent[parent_node]
                    color[parent_node] = self.BLACK
                    color[grand] = self.RED
                    self._rotate_left(grand)

        color[self.root] = self.BLACK

    def _find_node(self, x):
        node = self.root
        key = self.key
        left = self.left
        right = self.right

        while node:
            node_key = key[node]
            if x < node_key:
                node = left[node]
            elif x > node_key:
                node = right[node]
            else:
                return node
        return 0

    def _contains_node(self, node_id):
        return 0 < node_id < len(self.key) and self._find_node(self.key[node_id]) == node_id

    def _transplant(self, old_node, new_node):
        parent = self.parent[old_node]
        if parent == 0:
            self.root = new_node
        elif self.left[parent] == old_node:
            self.left[parent] = new_node
        else:
            self.right[parent] = new_node

        if new_node:
            self.parent[new_node] = parent

    def _fix_delete(self, node, node_parent):
        left = self.left
        right = self.right
        parent = self.parent
        color = self.color

        while node != self.root and color[node] == self.BLACK:
            if node == left[node_parent]:
                sibling = right[node_parent]
                if color[sibling] == self.RED:
                    color[sibling] = self.BLACK
                    color[node_parent] = self.RED
                    self._rotate_left(node_parent)
                    sibling = right[node_parent]

                sibling_left = left[sibling]
                sibling_right = right[sibling]
                if color[sibling_left] == self.BLACK and color[sibling_right] == self.BLACK:
                    color[sibling] = self.RED
                    node = node_parent
                    node_parent = parent[node]
                else:
                    if color[sibling_right] == self.BLACK:
                        color[sibling_left] = self.BLACK
                        color[sibling] = self.RED
                        self._rotate_right(sibling)
                        sibling = right[node_parent]
                        sibling_right = right[sibling]

                    color[sibling] = color[node_parent]
                    color[node_parent] = self.BLACK
                    color[sibling_right] = self.BLACK
                    self._rotate_left(node_parent)
                    node = self.root
            else:
                sibling = left[node_parent]
                if color[sibling] == self.RED:
                    color[sibling] = self.BLACK
                    color[node_parent] = self.RED
                    self._rotate_right(node_parent)
                    sibling = left[node_parent]

                sibling_left = left[sibling]
                sibling_right = right[sibling]
                if color[sibling_left] == self.BLACK and color[sibling_right] == self.BLACK:
                    color[sibling] = self.RED
                    node = node_parent
                    node_parent = parent[node]
                else:
                    if color[sibling_left] == self.BLACK:
                        color[sibling_right] = self.BLACK
                        color[sibling] = self.RED
                        self._rotate_left(sibling)
                        sibling = left[node_parent]
                        sibling_left = left[sibling]

                    color[sibling] = color[node_parent]
                    color[node_parent] = self.BLACK
                    color[sibling_left] = self.BLACK
                    self._rotate_right(node_parent)
                    node = self.root

        color[node] = self.BLACK

    def _erase_node(self, node):
        next_node = self.next_id[node]
        prev_node = self.prev_id[node]
        if prev_node:
            self.next_id[prev_node] = next_node
        if next_node:
            self.prev_id[next_node] = prev_node

        left = self.left
        right = self.right
        parent = self.parent
        color = self.color

        moved_up = node
        moved_up_original_color = color[moved_up]
        if left[node] == 0:
            fix_node = right[node]
            fix_parent = parent[node]
            self._transplant(node, fix_node)
        elif right[node] == 0:
            fix_node = left[node]
            fix_parent = parent[node]
            self._transplant(node, fix_node)
        else:
            moved_up = next_node
            moved_up_original_color = color[moved_up]
            fix_node = right[moved_up]
            if parent[moved_up] == node:
                fix_parent = moved_up
            else:
                fix_parent = parent[moved_up]
                self._transplant(moved_up, fix_node)
                right[moved_up] = right[node]
                parent[right[moved_up]] = moved_up

            self._transplant(node, moved_up)
            left[moved_up] = left[node]
            parent[left[moved_up]] = moved_up
            color[moved_up] = color[node]

        left[node] = 0
        right[node] = 0
        parent[node] = 0
        color[node] = self.BLACK
        self.prev_id[node] = 0
        self.next_id[node] = 0

        if moved_up_original_color == self.BLACK:
            self._fix_delete(fix_node, fix_parent)

        return next_node

    def _iter_pair(self, node_id):
        if node_id == 0:
            return None, 0
        return self.key[node_id], node_id

    def insert(self, x, with_id=False):
        root = self.root
        if root == 0:
            self.root = self._new_node(x, self.BLACK, 0, 0)
            return (self.root, True) if with_id else True

        key = self.key
        left = self.left
        right = self.right
        parent = self.parent
        pred = 0
        succ = 0
        node = root

        while node:
            node_key = key[node]
            if x < node_key:
                succ = node
                next_node = left[node]
                if next_node == 0:
                    new_node = self._new_node(x, self.RED, pred, succ)
                    left[node] = new_node
                    parent[new_node] = node
                    self._fix_insert(new_node)
                    return (new_node, True) if with_id else True
                node = next_node
            elif x > node_key:
                pred = node
                next_node = right[node]
                if next_node == 0:
                    new_node = self._new_node(x, self.RED, pred, succ)
                    right[node] = new_node
                    parent[new_node] = node
                    self._fix_insert(new_node)
                    return (new_node, True) if with_id else True
                node = next_node
            else:
                return (node, False) if with_id else False

    def lower_bound_with_id(self, x):
        node = self.root
        answer_node = 0
        key = self.key
        left = self.left
        right = self.right

        while node:
            if key[node] >= x:
                answer_node = node
                node = left[node]
            else:
                node = right[node]

        if answer_node == 0:
            return None, 0
        return key[answer_node], answer_node

    def lower_bound(self, x, with_id=False):
        answer, node_id = self.lower_bound_with_id(x)
        return (answer, node_id) if with_id else answer

    def prev(self, node_id):
        prev_id = self.prev_id[node_id]
        if prev_id == 0:
            return None, 0
        return self.key[prev_id], prev_id

    def next(self, node_id):
        next_id = self.next_id[node_id]
        if next_id == 0:
            return None, 0
        return self.key[next_id], next_id

    def erase(self, x):
        node = self._find_node(x)
        if node == 0:
            return (None, 0), False
        next_node = self._erase_node(node)
        return self._iter_pair(next_node), True

    def erase_id(self, node_id):
        if not self._contains_node(node_id):
            return (None, 0), False
        next_node = self._erase_node(node_id)
        return self._iter_pair(next_node), True


# -------------------------
# Основное решение
# -------------------------

BOUND = 10**9


def solve() -> None:
    points = RedBlackTree((-BOUND, BOUND))
    q = int(input())
    values = list(map(int, input().split()))
    answers = []
    for x in values:
        # читаем икс и ищем соседа слева и справа:
        right, right_id = points.lower_bound_with_id(x)
        left, _ = points.prev(right_id)
        # расстояние до ближайшего - это минимум из расстояний до соседей:
        answers.append(str(min(x - left, right - x)))
        # вставляем:
        points.insert(x)
    print("\n".join(answers))


t = int(input())
for _ in range(t):
    solve()
```

</details>

<details>
<summary>Разбор решения на Python3: способ 2</summary>

Это ещё один прямой аналог решения на `std::set<int>`, только теперь мы повторяем не поведение `insert`, а поведение `lower_bound`.

Ключевая строка здесь такая:

```python
right, right_id = points.lower_bound_with_id(x)
```

Она возвращает ближайший ключ справа и идентификатор узла, в котором этот ключ лежит. Левого соседа после этого можно взять как `prev(right_id)`.

Дальше всё работает точно так же, как в C++-версии. Если число $x$ уже есть в дереве, то `lower_bound_with_id(x)` вернёт именно его, поэтому одно из расстояний автоматически окажется равно $0$. После этого можно спокойно вызвать `insert(x)`: дерево просто не добавит дубликат.

</details>

<details>
<summary>Решение на C++: способ 3</summary>

```cpp
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using namespace std;
void solve() {
    // читаем запросы и запоминаем использованные координаты:
    int q; cin >> q;
    vector<int> x = {-1000000000, 1000000000};
    vector<int> queries(q);
    for (int i = 0; i < q; i++) {
        int xi; cin >> xi;
        queries[i] = xi;
        x.push_back(xi);
    }
    // сортируем координаты
    sort(all(x));
    // считаем количество каждого числа методом двух указателей:
    vector<int> cnt;
    for (int i = 0, j; i < isz(x); i = j) {
        // двигаем правую границу подотрезка равных элементов:
        for (j = i; j < isz(x) && x[i] == x[j]; j++);
        // полуинтервал [i, j) состоит из чисел, равных x[i]
        cnt.push_back(j - i);
    }
    // удаляем повторы:
    x.erase(unique(all(x)), x.end());
    // строим двусвязный список:
    vector<int> Prev(isz(x), -1), Next(isz(x), -1);
    for (int i = 0; i + 1 < isz(x); i++)
        Prev[i+1] = i, Next[i] = i+1;
    // теперь обрабатываем запросы в обратном порядке
    // каждый запрос удаляет ранее добавленный элемент
    vector<int> answ(q);
    for (int queryId = q-1; queryId >= 0; queryId--) {
        // находим и удаляем текущий элемент:
        int xi = int(lower_bound(all(x), queries[queryId]) - x.begin());
        cnt[xi]--;
        if (cnt[xi] > 0) // остался повтор
            answ[queryId] = 0;
        else {
            // соседи справа и слева:
            int ni = Next[xi], pi = Prev[xi];
            // расстояние: это минимум из расстояний до соседей:
            answ[queryId] = min(x[ni] - x[xi], x[xi] - x[pi]);
            // связываем соседей друг с другом, удаляя xi:
            Prev[ni] = pi, Next[pi] = ni;
        }
    }
    // выводим ответ:
    for (int i = 0; i < q; i++)
        cout << answ[i] << ' ';
    cout << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
```

</details>

<details>
<summary>Разбор решения на C++: способ 3</summary>

Это офлайн-решение. Вместо того чтобы отвечать на запросы в прямом порядке, мы сначала собираем все числа, сортируем их и строим состояние после выполнения всех добавлений. Затем идём по запросам справа налево и на каждом шаге удаляем очередное число.

Повторы учитываются массивом $\text{cnt}$. Пока после уменьшения $\text{cnt}[\text{xi}]$ значение остаётся положительным, такое число всё ещё есть в структуре, поэтому ответ равен $0$.

Когда удаляется последнее вхождение числа, его позиция вырезается из двусвязного списка по массивам $\text{Prev}$ и $\text{Next}$. Именно поэтому ближайшие ещё живые соседи доступны сразу:

```cpp
int ni = Next[xi], pi = Prev[xi];
```

После этого ответ считается как минимум из расстояний до этих соседей, а сама вершина удаляется из списка:

```cpp
answ[queryId] = min(x[ni] - x[xi], x[xi] - x[pi]);
Prev[ni] = pi, Next[pi] = ni;
```

Главная идея в том, что удалять из готового отсортированного набора проще, чем динамически вставлять элементы в Python-подобной логике. В C++ это решение тоже корректно, но интересно прежде всего как мост к версии на Python3.

</details>

<details>
<summary>Решение на Python3: способ 3</summary>

```python
from bisect import bisect_left

def solve():
    # читаем запросы и запоминаем использованные координаты:
    q = int(input())
    queries = list(map(int, input().split()))
    x = [-1000000000, 1000000000]
    for i in range(q):
        xi = queries[i]
        x.append(xi)
    # сортируем координаты
    x.sort()
    # считаем количество каждого числа методом двух указателей:
    cnt = []
    i = 0
    while i < len(x):
        j = i
        # двигаем правую границу подотрезка равных элементов:
        while j < len(x) and x[i] == x[j]:
            j += 1
        # полуинтервал [i, j) состоит из чисел, равных x[i]
        cnt.append(j - i)
        i = j
    # удаляем повторы:
    x = list(dict.fromkeys(x))
    # строим двусвязный список:
    Prev = [-1] * len(x)
    Next = [-1] * len(x)
    for i in range(len(x) - 1):
        Prev[i + 1] = i
        Next[i] = i + 1
    # теперь обрабатываем запросы в обратном порядке
    # каждый запрос удаляет ранее добавленный элемент
    answ = [0] * q
    for queryId in range(q - 1, -1, -1):
        # находим и удаляем текущий элемент:
        xi = bisect_left(x, queries[queryId])
        cnt[xi] -= 1
        if cnt[xi] > 0:  # остался повтор
            answ[queryId] = 0
        else:
            # соседи справа и слева:
            ni = Next[xi]
            pi = Prev[xi]
            # расстояние: это минимум из расстояний до соседей:
            answ[queryId] = min(x[ni] - x[xi], x[xi] - x[pi])
            # связываем соседей друг с другом, удаляя xi:
            Prev[ni] = pi
            Next[pi] = ni
    # выводим ответ:
    print(" ".join(map(str, answ)))

tt = int(input())
for _ in range(tt):
    solve()
```

</details>

<details>
<summary>Разбор решения на Python3: способ 3</summary>

Это тот же самый офлайн-алгоритм, что и в третьем способе на C++, только вместо `lower_bound` используется `bisect_left`.

Сначала собираем все координаты, сортируем их и удаляем повторы. Массив $\text{cnt}$ хранит количество вхождений каждого числа. Это важно для повторов: если после уменьшения $\text{cnt}[\text{xi}]$ оно остаётся положительным, значит такое число всё ещё есть в структуре, поэтому ответ равен $0$.

Массивы $\text{Prev}$ и $\text{Next}$ играют роль двусвязного списка по уникальным координатам. Пока число ещё присутствует в структуре, его вершина остаётся в этом списке. Как только последнее вхождение числа удалено, вершина вырезается:

```python
Prev[ni] = pi
Next[pi] = ni
```

После этого соседи напрямую ссылаются друг на друга, и позже удалённая вершина уже не сможет снова появиться как сосед. Поэтому в момент, когда $\text{cnt}[\text{xi}]$ стало равно $0$, ближайшие числа слева и справа уже лежат в $\text{Prev}[\text{xi}]$ и $\text{Next}[\text{xi}]$, а ответ считается как минимум из двух расстояний до них.

</details>

## E. Менеджер памяти

<details>
<summary>Текстовый разбор</summary>

**Первый способ.** Храним границы свободных отрезков в `std::set` в виде пар $(R, L)$. Такой способ хранения позволит нам эффективно искать отрезок, содержащий точку $x$: это `lower_bound` от пары $(x, -\infty)$. Изначально у нас ровно один свободный отрезок $[1, n]$. Он хранится как пара $(n, 1)$.

Длины свободных отрезков храним в `std::multiset`. Это позволит находить максимальную длину за $O(1)$. Изначально там два числа: $0$ и $n$. Первое число — длина пустого отрезка, а второе — длина отрезка $[1, n]$.

Когда читаем очередной запрос $[l, r]$, он попадает в некоторый свободный отрезок $[L, R]$ и делит его на три части: $[L, l-1]$, $[l, r]$ и $[r+1, R]$. Первая и третья части остаются свободными. Поэтому делаем следующее:

1. Ищем отрезок $[L, R]$ с помощью `lower_bound`.
2. Удаляем отрезок $[L, R]$ из `set` и его длину из `multiset`.
3. Вставляем отрезок $[L, l-1]$ в `set` и его длину в `multiset`.
4. Вставляем отрезок $[r+1, R]$ в `set` и его длину в `multiset`.

Каждый шаг выполняется за $O(\log(q))$, поэтому итоговая асимптотика — $O(q \log(q))$.

Ту же идею можно записать немного проще через `map<int, int>`, где ключом будет левая граница $L$, а значением — правая граница $R$ свободного отрезка. Тогда вместо `set<pair<int,int>>` и поиска по паре $(r, -\infty)$ можно сделать `upper_bound(l)` по левой границе и взять предыдущий отрезок: именно он и будет содержать запрос $[l, r]$. Логика с `multiset` длин при этом вообще не меняется.

Можно также написать и Python3-версию этого же подхода. Для этого один собственный `RedBlackTree` играет роль `map<int, int>` для свободных отрезков, а второй хранит количество отрезков каждой длины. В отличие от `multiset`, длины из второго дерева можно не удалять: достаточно менять их счётчики, а максимум поддерживать указателем на текущий самый большой ключ. Этот указатель только двигается влево, потому что после очередного запроса максимальная длина свободного отрезка не может увеличиться.

В файле `E-1-map-optimized.py` записана та же идея, но с локальной оптимизацией обновления свободных отрезков. Если после вырезания запроса остаётся левая часть $[L, l-1]$, то можно не удалять старый узел и не вставлять новый, а просто переиспользовать тот же `node_id` и поменять только правую границу через `set_value`. Это не меняет асимптотику, но уменьшает число лишних операций с деревом и заметно ускоряет Python-версию на больших тестах.

**Второй способ.**

> [!WARNING]
> Данный способ содержит продвинутые техники и позволяет решить задачу на Python3. Он точно не для начинающих, поэтому можете пропустить его, если пока не готовы.

Также, как делали в задаче D, временно забудем, что нам нужно отвечать на запросы, и посмотрим, что получится в конце. В конце получится массив отрезков, как свободных, так и занятых. Сформируем его, собрав все координаты из запросов, отсортировав их, удалив повторы и отметив, какие отрезки заняты, а какие — свободны.

Теперь обработаем запросы в обратном порядке. Если раньше отрезок занимал память, то теперь он освобождает её. Это значит, что нам нужно бинарным поиском найти освобождающий память отрезок и объединить его с соседом слева и соседом справа. Важно, что он объединяется с соседом только если сосед тоже свободен. После объединения обновляем ответ.

Если хочется использовать что-то стандартное, то для объединения отрезков можно взять структуру данных Система Непересекающихся Множеств (СМН, DSU).

Если хочется использовать что-то креативное, то в этой конкретной задаче хватает и двусвязного списка занятых отрезков. Это работает потому, что после сжатия координат каждый запрос соответствует ровно одному занятому блоку, а в обратном порядке мы просто удаляем этот блок и склеиваем два соседних свободных промежутка.

Асимптотика: $O(q \log(q))$.

</details>

<details>
<summary>Решение на C++: способ 1</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;
const int inf = 1000000007;
void solve() {
    // храним границы свободных отрезков в виде пар (R, L) - сначала правая граница,
    // затем левая граница. Это удобно, потому что s.lower_bound({x,-inf}) найдёт нам
    // первый отрезок такой, что: x <= R.
    // Дополнительно храним мультисет из длин отрезков, чтобы выдавать максимум.
    int n, q; cin >> n >> q;
    set<pair<int,int>> segments{{n, 1}}; // 1 отрезок: [1, n]
    multiset<int> lengths = {n, 0};      // 2 элемента: "n" и "0"
    while (q --> 0) {
        char c; int l, r;
        cin >> c >> l >> r;
        // находим отрезок, в который попадает граница r:
        auto iter = segments.lower_bound({r, -inf});
        // запоминаем его левую и правую границу, затем удаляем вместе с длиной:
        auto [R, L] = *iter;
        segments.erase(iter);
        lengths.erase(lengths.find(R-L+1));
        // Из отрезка [L, R] мы вырезали подотрезок [l, r]. Нужно вставить два
        // два отрезка: [L, l-1] и [r+1, R]:
        if (L < l) {
            segments.insert({l-1, L});
            lengths.insert(l - L);
        }
        if (r < R) {
            segments.insert({R, r+1});
            lengths.insert(R - r);
        }
        // выводим ответ - максимальную длину отрезка:
        cout << *lengths.rbegin() << '\n';
    }
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
```

</details>

<details>
<summary>Разбор решения на C++: способ 1</summary>

Здесь самая нестандартная идея — хранить свободный отрезок не как $(L, R)$, а как $(R, L)$.

Это делается ради строки:

```cpp
auto iter = segments.lower_bound({r, -inf});
```

`set` из пар сравнивает пары лексикографически. Значит, `lower_bound({r, -inf})` найдёт первый отрезок, у которого правая граница не меньше $r$. А по условию именно этот отрезок и содержит текущий запрос.

Есть и более прямолинейная запись той же идеи через `map<int, int> segments`, где хранится соответствие $L \to R$. Тогда свободные отрезки уже упорядочены по левой границе, и нужный отрезок ищется так: `prev(segments.upper_bound(l))`. `upper_bound(l)` даёт первый отрезок, начинающийся строго правее $l$, поэтому предыдущий отрезок и является тем, который содержит $l$. Вся остальная логика решения, включая `multiset` длин, остаётся прежней.

Ещё одна важная строка:

```cpp
lengths.erase(lengths.find(R-L+1));
```

У `multiset` нельзя писать просто `erase(value)`, если нужно удалить ровно одно вхождение: такой вызов удалит все копии этого значения. Поэтому сначала берём итератор на одно конкретное вхождение через `find`, а потом удаляем именно его.

</details>

<details>
<summary>Решение на Python3: способ 1</summary>

Ниже приведена базовая версия этого подхода. В файле `E-1-map-optimized.py` лежит его более быстрая реализация с переиспользованием узла левого остатка свободного отрезка.

```python
# Вердикт: ..., Время: ..., Память: ..., Язык: PyPy 3-64

# -------------------------
# RedBlackTree
# -------------------------

"""Компактный RedBlackTree для задач на ordered map<int, int>.

Использование:
- tree = RedBlackTree(items=())
  Создаёт дерево и по очереди вставляет пары (key, value) из items.
- tree.set(key, value) -> node_id
  Вставляет ключ, если его ещё нет, либо перезаписывает значение.
  Возвращает node_id этого ключа.
- tree.set(key, value, with_id=True) -> (node_id, was_inserted)
  Возвращает node_id и флаг, был ли ключ создан заново.
- tree.add(key, delta) -> node_id
  Увеличивает значение по ключу на delta. Если ключа нет, создаёт его.
- tree.get(key, default=None) -> value
  Возвращает значение по ключу или default, если ключ не найден.
- tree.get_key(node_id) -> key
  Возвращает ключ по node_id.
- tree.get_value(node_id) -> value
  Возвращает значение по node_id.
- tree.upper_bound_with_id(x) -> (key, value, node_id)
  Возвращает первый ключ > x, его значение и node_id.
  Если такого ключа нет, возвращает (None, None, 0).
- tree.prev(node_id) -> (key, value, prev_node_id)
  Возвращает предыдущий ключ в inorder, его значение и node_id.
  Если соседа слева нет, возвращает (None, None, 0).
- tree.last() -> (key, value, node_id)
  Возвращает максимальный ключ, его значение и node_id.
  Если дерево пусто, возвращает (None, None, 0).
- tree.erase_id(node_id) -> bool
  Удаляет узел по его node_id.
  Возвращает True, если удаление произошло, иначе False.

Замечание:
- node_id стабилен после поворотов и следующих вставок, пока сам узел не удалён.
"""


class RedBlackTree:
    __slots__ = ("root", "key", "value", "left", "right", "parent", "color", "prev_id", "next_id")

    RED = 1
    BLACK = 0

    def __init__(self, items=()):
        self.root = 0
        self.key = [0]
        self.value = [0]
        self.left = [0]
        self.right = [0]
        self.parent = [0]
        self.color = [self.BLACK]
        self.prev_id = [0]
        self.next_id = [0]
        for key, value in items:
            self.set(key, value)

    def _new_node(self, key, value, color, pred, succ):
        self.key.append(key)
        self.value.append(value)
        self.left.append(0)
        self.right.append(0)
        self.parent.append(0)
        self.color.append(color)
        self.prev_id.append(pred)
        self.next_id.append(succ)
        node = len(self.key) - 1
        if pred:
            self.next_id[pred] = node
        if succ:
            self.prev_id[succ] = node
        return node

    def _rotate_left(self, node):
        right_node = self.right[node]
        self.right[node] = self.left[right_node]
        if self.left[right_node]:
            self.parent[self.left[right_node]] = node

        parent = self.parent[node]
        self.parent[right_node] = parent
        if parent == 0:
            self.root = right_node
        elif self.left[parent] == node:
            self.left[parent] = right_node
        else:
            self.right[parent] = right_node

        self.left[right_node] = node
        self.parent[node] = right_node

    def _rotate_right(self, node):
        left_node = self.left[node]
        self.left[node] = self.right[left_node]
        if self.right[left_node]:
            self.parent[self.right[left_node]] = node

        parent = self.parent[node]
        self.parent[left_node] = parent
        if parent == 0:
            self.root = left_node
        elif self.left[parent] == node:
            self.left[parent] = left_node
        else:
            self.right[parent] = left_node

        self.right[left_node] = node
        self.parent[node] = left_node

    def _fix_insert(self, node):
        left = self.left
        right = self.right
        parent = self.parent
        color = self.color

        while node != self.root and color[parent[node]] == self.RED:
            parent_node = parent[node]
            grand = parent[parent_node]

            if parent_node == left[grand]:
                uncle = right[grand]
                if color[uncle] == self.RED:
                    color[parent_node] = self.BLACK
                    color[uncle] = self.BLACK
                    color[grand] = self.RED
                    node = grand
                else:
                    if node == right[parent_node]:
                        node = parent_node
                        self._rotate_left(node)
                        parent_node = parent[node]
                        grand = parent[parent_node]
                    color[parent_node] = self.BLACK
                    color[grand] = self.RED
                    self._rotate_right(grand)
            else:
                uncle = left[grand]
                if color[uncle] == self.RED:
                    color[parent_node] = self.BLACK
                    color[uncle] = self.BLACK
                    color[grand] = self.RED
                    node = grand
                else:
                    if node == left[parent_node]:
                        node = parent_node
                        self._rotate_right(node)
                        parent_node = parent[node]
                        grand = parent[parent_node]
                    color[parent_node] = self.BLACK
                    color[grand] = self.RED
                    self._rotate_left(grand)

        color[self.root] = self.BLACK

    def _find_node(self, key):
        node = self.root
        keys = self.key
        left = self.left
        right = self.right

        while node:
            node_key = keys[node]
            if key < node_key:
                node = left[node]
            elif key > node_key:
                node = right[node]
            else:
                return node
        return 0

    def _contains_node(self, node_id):
        return 0 < node_id < len(self.key) and self._find_node(self.key[node_id]) == node_id

    def _transplant(self, old_node, new_node):
        parent = self.parent[old_node]
        if parent == 0:
            self.root = new_node
        elif self.left[parent] == old_node:
            self.left[parent] = new_node
        else:
            self.right[parent] = new_node

        if new_node:
            self.parent[new_node] = parent

    def _fix_delete(self, node, node_parent):
        left = self.left
        right = self.right
        parent = self.parent
        color = self.color

        while node != self.root and color[node] == self.BLACK:
            if node == left[node_parent]:
                sibling = right[node_parent]
                if color[sibling] == self.RED:
                    color[sibling] = self.BLACK
                    color[node_parent] = self.RED
                    self._rotate_left(node_parent)
                    sibling = right[node_parent]

                sibling_left = left[sibling]
                sibling_right = right[sibling]
                if color[sibling_left] == self.BLACK and color[sibling_right] == self.BLACK:
                    color[sibling] = self.RED
                    node = node_parent
                    node_parent = parent[node]
                else:
                    if color[sibling_right] == self.BLACK:
                        color[sibling_left] = self.BLACK
                        color[sibling] = self.RED
                        self._rotate_right(sibling)
                        sibling = right[node_parent]
                        sibling_right = right[sibling]

                    color[sibling] = color[node_parent]
                    color[node_parent] = self.BLACK
                    color[sibling_right] = self.BLACK
                    self._rotate_left(node_parent)
                    node = self.root
            else:
                sibling = left[node_parent]
                if color[sibling] == self.RED:
                    color[sibling] = self.BLACK
                    color[node_parent] = self.RED
                    self._rotate_right(node_parent)
                    sibling = left[node_parent]

                sibling_left = left[sibling]
                sibling_right = right[sibling]
                if color[sibling_left] == self.BLACK and color[sibling_right] == self.BLACK:
                    color[sibling] = self.RED
                    node = node_parent
                    node_parent = parent[node]
                else:
                    if color[sibling_left] == self.BLACK:
                        color[sibling_right] = self.BLACK
                        color[sibling] = self.RED
                        self._rotate_left(sibling)
                        sibling = left[node_parent]
                        sibling_left = left[sibling]

                    color[sibling] = color[node_parent]
                    color[node_parent] = self.BLACK
                    color[sibling_left] = self.BLACK
                    self._rotate_right(node_parent)
                    node = self.root

        color[node] = self.BLACK

    def _erase_node(self, node):
        next_node = self.next_id[node]
        prev_node = self.prev_id[node]
        if prev_node:
            self.next_id[prev_node] = next_node
        if next_node:
            self.prev_id[next_node] = prev_node

        left = self.left
        right = self.right
        parent = self.parent
        color = self.color

        moved_up = node
        moved_up_original_color = color[moved_up]
        if left[node] == 0:
            fix_node = right[node]
            fix_parent = parent[node]
            self._transplant(node, fix_node)
        elif right[node] == 0:
            fix_node = left[node]
            fix_parent = parent[node]
            self._transplant(node, fix_node)
        else:
            moved_up = next_node
            moved_up_original_color = color[moved_up]
            fix_node = right[moved_up]
            if parent[moved_up] == node:
                fix_parent = moved_up
            else:
                fix_parent = parent[moved_up]
                self._transplant(moved_up, fix_node)
                right[moved_up] = right[node]
                parent[right[moved_up]] = moved_up

            self._transplant(node, moved_up)
            left[moved_up] = left[node]
            parent[left[moved_up]] = moved_up
            color[moved_up] = color[node]

        left[node] = 0
        right[node] = 0
        parent[node] = 0
        color[node] = self.BLACK
        self.prev_id[node] = 0
        self.next_id[node] = 0

        if moved_up_original_color == self.BLACK:
            self._fix_delete(fix_node, fix_parent)

    def _node_entry(self, node_id):
        if node_id == 0:
            return None, None, 0
        return self.key[node_id], self.value[node_id], node_id

    def set(self, key, value, with_id=False):
        root = self.root
        if root == 0:
            self.root = self._new_node(key, value, self.BLACK, 0, 0)
            return (self.root, True) if with_id else self.root

        keys = self.key
        left = self.left
        right = self.right
        parent = self.parent
        pred = 0
        succ = 0
        node = root

        while node:
            node_key = keys[node]
            if key < node_key:
                succ = node
                next_node = left[node]
                if next_node == 0:
                    new_node = self._new_node(key, value, self.RED, pred, succ)
                    left[node] = new_node
                    parent[new_node] = node
                    self._fix_insert(new_node)
                    return (new_node, True) if with_id else new_node
                node = next_node
            elif key > node_key:
                pred = node
                next_node = right[node]
                if next_node == 0:
                    new_node = self._new_node(key, value, self.RED, pred, succ)
                    right[node] = new_node
                    parent[new_node] = node
                    self._fix_insert(new_node)
                    return (new_node, True) if with_id else new_node
                node = next_node
            else:
                self.value[node] = value
                return (node, False) if with_id else node

    def add(self, key, delta):
        root = self.root
        if root == 0:
            self.root = self._new_node(key, delta, self.BLACK, 0, 0)
            return self.root

        keys = self.key
        values = self.value
        left = self.left
        right = self.right
        parent = self.parent
        pred = 0
        succ = 0
        node = root

        while node:
            node_key = keys[node]
            if key < node_key:
                succ = node
                next_node = left[node]
                if next_node == 0:
                    new_node = self._new_node(key, delta, self.RED, pred, succ)
                    left[node] = new_node
                    parent[new_node] = node
                    self._fix_insert(new_node)
                    return new_node
                node = next_node
            elif key > node_key:
                pred = node
                next_node = right[node]
                if next_node == 0:
                    new_node = self._new_node(key, delta, self.RED, pred, succ)
                    right[node] = new_node
                    parent[new_node] = node
                    self._fix_insert(new_node)
                    return new_node
                node = next_node
            else:
                values[node] += delta
                return node

    def get(self, key, default=None):
        node = self._find_node(key)
        return default if node == 0 else self.value[node]

    def get_key(self, node_id):
        if node_id == 0:
            return None
        return self.key[node_id]

    def get_value(self, node_id):
        if node_id == 0:
            return None
        return self.value[node_id]

    def upper_bound_with_id(self, x):
        node = self.root
        answer_node = 0
        keys = self.key
        left = self.left
        right = self.right

        while node:
            if keys[node] > x:
                answer_node = node
                node = left[node]
            else:
                node = right[node]

        return self._node_entry(answer_node)

    def prev(self, node_id):
        if node_id == 0:
            return None, None, 0
        return self._node_entry(self.prev_id[node_id])

    def last(self):
        node = self.root
        if node == 0:
            return None, None, 0
        right = self.right
        while right[node]:
            node = right[node]
        return self._node_entry(node)

    def erase_id(self, node_id):
        if not self._contains_node(node_id):
            return False
        self._erase_node(node_id)
        return True


# -------------------------
# Основное решение
# -------------------------


def solve() -> None:
    # храним свободные отрезки в map<int, int>: ключ - левая граница L,
    # значение - правая граница R. Тогда upper_bound(l) найдёт первый
    # отрезок, который начинается строго правее l, а предыдущий отрезок
    # и будет тем самым [L, R], который содержит запрос [l, r].
    # Вместо multiset длин храним ещё один map<int, int>: ключ - длина,
    # значение - количество отрезков такой длины.
    n, q = map(int, input().split())
    segments = RedBlackTree(((1, n),))
    lengths = RedBlackTree(((0, 1), (n, 1)))
    _, _, max_length_id = lengths.last()
    answers = []
    while q > 0:
        c, l, r = input().split()
        l = int(l)
        r = int(r)
        # находим отрезок, в который попадает граница l:
        _, _, next_segment_id = segments.upper_bound_with_id(l)
        if next_segment_id == 0:
            L, R, segment_id = segments.last()
        else:
            L, R, segment_id = segments.prev(next_segment_id)
        # запоминаем его левую и правую границу, затем удаляем вместе с длиной:
        segments.erase_id(segment_id)
        lengths.add(R - L + 1, -1)
        # Из отрезка [L, R] мы вырезали подотрезок [l, r]. Нужно вставить два
        # отрезка: [L, l-1] и [r+1, R]:
        if L < l:
            segments.set(L, l - 1)
            lengths.add(l - L, +1)
        if r < R:
            segments.set(r + 1, R)
            lengths.add(R - r, +1)
        # максимальная длина могла только уменьшиться, поэтому двигаемся влево,
        # пока количество отрезков текущей длины не станет положительным:
        while lengths.get_value(max_length_id) == 0:
            _, _, max_length_id = lengths.prev(max_length_id)
        # выводим ответ - максимальную длину отрезка:
        answers.append(str(lengths.get_key(max_length_id)))
        q -= 1
    print("\n".join(answers))


t = int(input())
for _ in range(t):
    solve()
```

</details>

<details>
<summary>Разбор решения на Python3: способ 1</summary>

Здесь мы повторяем именно `map`-версию первого способа. Один `RedBlackTree` хранит свободные отрезки как соответствие $L \to R$, а второй хранит количество отрезков каждой длины.

Самый важный фрагмент такой:

```python
while lengths.get_value(max_length_id) == 0:
    _, _, max_length_id = lengths.prev(max_length_id)
```

Во втором дереве мы не удаляем ключи-длины, даже если их количество стало равно $0$. Вместо этого просто меняем счётчики. Это удобно, потому что ответ по задаче никогда не возрастает: максимальный свободный отрезок после очередного вырезания может только уменьшиться или остаться тем же. Значит, указатель $\text{max\_length\_id}$ никогда не двигается вправо, а только шаг за шагом уходит влево.

Поиск нужного свободного отрезка устроен так же, как в версии на `map<int, int>` в C++: `upper_bound_with_id(l)` возвращает первый отрезок, начинающийся строго правее $l$, а предыдущий узел и есть тот самый отрезок, который содержит текущий запрос.

В файле `E-1-map-optimized.py` используется та же структура данных и та же асимптотика $O(q \log q)$, но обновление отрезков записано чуть аккуратнее. В обычной версии мы удаляем найденный отрезок $[L, R]$, а потом при необходимости заново вставляем левый остаток $[L, l-1]$. В оптимизированной версии ключ $L$ не меняется, поэтому левый остаток можно оставить в том же узле: достаточно вызвать `segments.set_value(segment_id, l - 1)`. Удаление через `erase_id(segment_id)` требуется только когда левого остатка вообще нет, а правый остаток $[r+1, R]$ по-прежнему создаётся как новый узел, потому что у него уже другой ключ. За счёт этого в Python уменьшается число удалений, вставок и выделений новых вершин дерева.

</details>

<details>
<summary>Решение на C++: способ 2</summary>

```cpp
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using namespace std;
int lowpos(const auto &v, const auto &x) { return int(lower_bound(all(v), x) - v.begin()); }
void setmax(auto &x, const auto &y) { if (x < y) x = y; }

// система непересекающихся множеств: каждому отрезку [l, r) соответствует
// своя вершина в дереве, которая хранит длину этого отрезка
struct DSU {
    vector<int> par, len, sz;
    DSU(int n)
        : par(n), len(n, 0), sz(n, 1)
    {
        for (int i = 0; i < n; i++)
            par[i] = i;
    }
    // получение представителя с эвристикой сжатия путей:
    int getPar(int u) {
        return u == par[u] ? u : par[u] = getPar(par[u]);
    }
    // объединение двух множеств с эвристикой по их размеру:
    void merge(int u, int v) {
        u = getPar(u), v = getPar(v);
        if (u == v)
            return;
        if (sz[u] < sz[v])
            swap(u, v);
        sz[u] += sz[v];
        par[v] = u;
        len[u] += len[v];
    }
    // функции для работы с длиной отрезков:
    void addLen(int u, int x) {
        len[getPar(u)] += x;
    }
    int getLen(int u) {
        return len[getPar(u)];
    }
};

void solve() {
    // читаем запросы, собираем множество используемых координат:
    int n, q; cin >> n >> q;
    vector<pair<int,int>> queries(q);
    vector<int> x = {1, n+1};
    for (auto &[l, r] : queries) {
        char c; cin >> c >> l >> r;
        x.push_back(l);
        x.push_back(r+1);
    }
    // делаем сжатие координат:
    sort(all(x));
    x.erase(unique(all(x)), x.end());
    // отмечаем, какие отрезки заняты после всех запросов:
    const int numSegments = isz(x)-1;
    vector<int> occupied(numSegments, 0);
    for (auto &[l, _] : queries) {
        l = lowpos(x, l);
        occupied[l] = 1;
    }
    // инициализируем DSU, находим лучший ответ после всех запросов:
    DSU dsu(numSegments);
    int best = 0;
    for (int i = 0; i < numSegments; i++) {
        if (!occupied[i]) {
            setmax(best, x[i+1] - x[i]);
            dsu.addLen(i, x[i+1] - x[i]);
        }
    }
    // начинаем обрабатывать запросы в обратном порядке
    // теперь один запрос [l, r] объединяет три отрезка: l-1, l, l+1
    // правая граница не используется, так как в сжатых координатах l == r
    vector<int> answ(isz(queries));
    for (int queryId = isz(queries)-1; queryId >= 0; queryId--) {
        // текущее состояние соответствует ответу после queryId-го запроса
        // в исходном порядке, поэтому сохраняем best до "отката":
        answ[queryId] = best;
        // освобождаем текущий отрезок:
        int i = queries[queryId].first;
        dsu.addLen(i, x[i+1] - x[i]);
        occupied[i] = 0;
        // объединяем текущий отрезок с его соседом слева:
        if (i - 1 >= 0 && !occupied[i-1])
            dsu.merge(i-1, i);
        // объединяем текущий отрезок с его соседом справа:
        if (i + 1 < numSegments && !occupied[i+1])
            dsu.merge(i, i+1);
        // обновляем ответ:
        setmax(best, dsu.getLen(i));
    }
    // выводим ответ:
    for (int i = 0; i < isz(answ); i++)
        cout << answ[i] << ' ';
    cout << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
```

</details>

<details>
<summary>Разбор решения на C++: способ 2</summary>

Здесь основная идея состоит в том, что после сжатия координат каждый запрос соответствует ровно одному элементарному отрезку. Поэтому в обратном порядке мы не «снимаем произвольный диапазон», а освобождаем одну конкретную вершину с индексом $i$.

Структура DSU хранит для каждой компоненты свободных отрезков не только представителя, но и суммарную длину этой компоненты в массиве $\text{len}$. Поэтому после освобождения сегмента нужно:

1. Добавить длину самого сегмента.
2. Объединить его с левым соседом, если тот свободен.
3. Объединить его с правым соседом, если тот свободен.
4. Обновить лучший ответ длиной новой компоненты.

Это видно прямо по коду:

```cpp
dsu.addLen(i, x[i+1] - x[i]);
if (i - 1 >= 0 && !occupied[i-1])
    dsu.merge(i-1, i);
if (i + 1 < numSegments && !occupied[i+1])
    dsu.merge(i, i+1);
setmax(best, dsu.getLen(i));
```

Отдельно важен порядок действий: сначала сохраняем текущий ответ в `answ[queryId]`, и только потом откатываем запрос. Это нужно потому, что текущее состояние в обратном проходе уже соответствует состоянию памяти после данного запроса в исходном порядке.

</details>

<details>
<summary>Решение на Python3: способ 2</summary>

```python
from bisect import bisect_left

# система непересекающихся множеств: каждому отрезку [l, r) соответствует
# своя вершина в дереве, которая хранит длину этого отрезка
class DSU:
    def __init__(self, n):
        self.par = list(range(n))
        self.len = [0] * n
        self.sz = [1] * n

    # получение представителя с эвристикой сжатия путей:
    def getPar(self, u):
        if u == self.par[u]:
            return u
        self.par[u] = self.getPar(self.par[u])
        return self.par[u]

    # объединение двух множеств с эвристикой по их размеру:
    def merge(self, u, v):
        u = self.getPar(u)
        v = self.getPar(v)
        if u == v:
            return
        if self.sz[u] < self.sz[v]:
            u, v = v, u
        self.sz[u] += self.sz[v]
        self.par[v] = u
        self.len[u] += self.len[v]

    # функции для работы с длиной отрезков:
    def addLen(self, u, x):
        self.len[self.getPar(u)] += x

    def getLen(self, u):
        return self.len[self.getPar(u)]

def solve():
    # читаем запросы, собираем множество используемых координат:
    n, q = map(int, input().split())
    queries = [[0, 0] for _ in range(q)]
    x = [1, n + 1]
    for query in queries:
        c, l, r = input().split()
        query[0] = int(l)
        query[1] = int(r)
        x.append(query[0])
        x.append(query[1] + 1)
    # делаем сжатие координат:
    x = sorted(set(x))
    # отмечаем, какие отрезки заняты после всех запросов:
    numSegments = len(x) - 1
    occupied = [0] * numSegments
    for query in queries:
        query[0] = bisect_left(x, query[0])
        occupied[query[0]] = 1
    # инициализируем DSU, находим лучший ответ после всех запросов:
    dsu = DSU(numSegments)
    best = 0
    for i in range(numSegments):
        if not occupied[i]:
            best = max(best, x[i + 1] - x[i])
            dsu.addLen(i, x[i + 1] - x[i])
    # начинаем обрабатывать запросы в обратном порядке
    # теперь один запрос [l, r] объединяет три отрезка: l-1, l, l+1
    # правая граница не используется, так как в сжатых координатах l == r
    answ = [0] * len(queries)
    for queryId in range(len(queries) - 1, -1, -1):
        # текущее состояние соответствует ответу после queryId-го запроса
        # в исходном порядке, поэтому сохраняем best до "отката":
        answ[queryId] = best
        # освобождаем текущий отрезок:
        i = queries[queryId][0]
        dsu.addLen(i, x[i + 1] - x[i])
        occupied[i] = 0
        # объединяем текущий отрезок с его соседом слева:
        if i - 1 >= 0 and not occupied[i - 1]:
            dsu.merge(i - 1, i)
        # объединяем текущий отрезок с его соседом справа:
        if i + 1 < numSegments and not occupied[i + 1]:
            dsu.merge(i, i + 1)
        # обновляем ответ:
        best = max(best, dsu.getLen(i))
    # выводим ответ:
    print(" ".join(map(str, answ)))

tt = int(input())
for _ in range(tt):
    solve()
```

</details>

<details>
<summary>Разбор решения на Python3: способ 2</summary>

Это прямая Python-версия решения с DSU. После сжатия координат каждый элементарный промежуток имеет длину $x[i + 1] - x[i]$, а массив $\text{occupied}$ показывает, какие из этих промежутков заняты после выполнения всех запросов.

Дальше алгоритм идёт в обратном порядке. В начале каждой итерации текущее состояние уже соответствует ответу после очередного запроса, поэтому сначала сохраняем $\text{best}$, а потом откатываем этот запрос, освобождая очередной сегмент.

Структура DSU хранит не просто связность, а суммарную длину свободной компоненты в массиве $\text{len}$. Поэтому после освобождения сегмента нужно сделать четыре шага:

1. Добавить длину самого сегмента.
2. Объединить его с левым соседом, если тот уже свободен.
3. Объединить его с правым соседом, если тот уже свободен.
4. Взять длину получившейся компоненты через `getLen(i)` и обновить $\text{best}$.

Отдельно полезно заметить, что после сжатия координат в $\text{query}[0]$ нам достаточно запомнить только индекс левой границы. Правая граница для объединений больше не нужна, потому что каждый запрос соответствует ровно одному элементарному сегменту.

</details>

<details>
<summary>Решение на C++: способ 3</summary>

```cpp
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using namespace std;
int lowpos(const auto &v, const auto &x) { return int(lower_bound(all(v), x) - v.begin()); }
void setmax(auto &x, const auto &y) { if (x < y) x = y; }

void solve() {
    // читаем запросы, собираем множество используемых координат:
    int n, q; cin >> n >> q;
    vector<pair<int,int>> queries(q);
    vector<int> x = {1, n+1};
    for (auto &[l, r] : queries) {
        char c; cin >> c >> l >> r;
        x.push_back(l);
        x.push_back(r+1);
    }
    // делаем сжатие координат:
    sort(all(x));
    x.erase(unique(all(x)), x.end());
    // отмечаем, какие отрезки заняты после всех запросов:
    const int numSegments = isz(x)-1;
    vector<int> occupied(numSegments, 0);
    for (auto &[l, _] : queries) {
        l = lowpos(x, l);
        occupied[l] = 1;
    }
    // строим двусвязный список занятых отрезков и находим лучший ответ
    // после всех запросов:
    vector<int> Prev(numSegments, -1), Next(numSegments, numSegments);
    int best = 0;
    int prevOccupied = -1;
    for (int i = 0; i < numSegments; i++) {
        if (!occupied[i])
            continue;
        setmax(best, x[i] - x[prevOccupied+1]);
        Prev[i] = prevOccupied;
        if (prevOccupied != -1)
            Next[prevOccupied] = i;
        prevOccupied = i;
    }
    setmax(best, x[numSegments] - x[prevOccupied+1]);
    // начинаем обрабатывать запросы в обратном порядке
    // теперь один запрос [l, r] удаляет один занятый отрезок и соединяет
    // два соседних свободных промежутка в один
    vector<int> answ(isz(queries));
    for (int queryId = isz(queries)-1; queryId >= 0; queryId--) {
        // текущее состояние соответствует ответу после queryId-го запроса
        // в исходном порядке, поэтому сохраняем best до "отката":
        answ[queryId] = best;
        // удаляем текущий занятый отрезок:
        int i = queries[queryId].first;
        // соседи справа и слева среди ещё занятых отрезков:
        int ni = Next[i], pi = Prev[i];
        // связываем соседей друг с другом, удаляя i:
        if (pi != -1)
            Next[pi] = ni;
        if (ni != numSegments)
            Prev[ni] = pi;
        // новый свободный промежуток ограничен занятыми соседями:
        setmax(best, x[ni] - x[pi+1]);
    }
    // выводим ответ:
    for (int i = 0; i < isz(answ); i++)
        cout << answ[i] << ' ';
    cout << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
```

</details>

<details>
<summary>Разбор решения на C++: способ 3</summary>

Здесь полезно держать в голове не только формулу длины, но и инвариант двусвязного списка. В обратном порядке мы не «строим свободные отрезки с нуля», а удаляем занятые блоки по одному.

Массивы $\text{Prev}$ и $\text{Next}$ изначально строятся только по тем сегментам, которые ещё заняты после всех запросов. Дальше на каждом шаге обратного прохода мы берём очередной занятый блок $i$, читаем его соседей

```cpp
int ni = Next[i], pi = Prev[i];
```

и только после этого вырезаем $i$ из списка:

```cpp
if (pi != -1)
    Next[pi] = ni;
if (ni != numSegments)
    Prev[ni] = pi;
```

Поэтому $\text{ni}$ и $\text{pi}$ всегда означают ближайшие ещё занятые блоки справа и слева. Если какой-то блок освободили раньше, он уже был вырезан из списка и больше не может встретиться как сосед.

После этого формула длины становится естественной. Если убрать текущий занятый блок $i$, то новый свободный промежуток растягивается от следующей координаты после левого занятого соседа до левой границы правого занятого соседа:

```cpp
setmax(best, x[ni] - x[pi+1]);
```

Это и есть длина объединения двух соседних свободных кусков плюс только что освобождённого блока. В этом и состоит главное упрощение: здесь уже не нужен DSU, потому что после сжатия координат каждый запрос соответствует ровно одному занятому сегменту.

</details>

<details>
<summary>Решение на Python3: способ 3</summary>

```python
from bisect import bisect_left

def solve():
    # читаем запросы, собираем множество используемых координат:
    n, q = map(int, input().split())
    queries = [[0, 0] for _ in range(q)]
    x = [1, n + 1]
    for query in queries:
        c, l, r = input().split()
        query[0], query[1] = int(l), int(r)
        x.append(query[0])
        x.append(query[1] + 1)
    # делаем сжатие координат:
    x = sorted(set(x))
    # отмечаем, какие отрезки заняты после всех запросов:
    numSegments = len(x) - 1
    occupied = [0] * numSegments
    for query in queries:
        query[0] = bisect_left(x, query[0])
        occupied[query[0]] = 1
    # строим двусвязный список занятых отрезков и находим лучший ответ
    # после всех запросов:
    Prev = [-1] * numSegments
    Next = [numSegments] * numSegments
    best = 0
    prevOccupied = -1
    for i in range(numSegments):
        if not occupied[i]:
            continue
        best = max(best, x[i] - x[prevOccupied + 1])
        Prev[i] = prevOccupied
        if prevOccupied != -1:
            Next[prevOccupied] = i
        prevOccupied = i
    best = max(best, x[numSegments] - x[prevOccupied + 1])
    # начинаем обрабатывать запросы в обратном порядке
    # теперь один запрос [l, r] удаляет один занятый отрезок и соединяет
    # два соседних свободных промежутка в один
    answ = [0] * len(queries)
    for queryId in range(len(queries) - 1, -1, -1):
        # текущее состояние соответствует ответу после queryId-го запроса
        # в исходном порядке, поэтому сохраняем best до "отката":
        answ[queryId] = best
        # удаляем текущий занятый отрезок:
        i = queries[queryId][0]
        # соседи справа и слева среди ещё занятых отрезков:
        ni, pi = Next[i], Prev[i]
        # связываем соседей друг с другом, удаляя i:
        if pi != -1:
            Next[pi] = ni
        if ni != numSegments:
            Prev[ni] = pi
        # новый свободный промежуток ограничен занятыми соседями:
        best = max(best, x[ni] - x[pi + 1])
    # выводим ответ:
    print(" ".join(map(str, answ)))

tt = int(input())
for _ in range(tt):
    solve()
```

</details>

<details>
<summary>Разбор решения на Python3: способ 3</summary>

Здесь работает тот же инвариант, что и в версии на C++. Списки $\text{Prev}$ и $\text{Next}$ хранят соседей не среди всех сегментов подряд, а только среди тех, которые ещё заняты в текущем состоянии.

В начале обратного прохода такой список строится по итоговому состоянию после всех запросов. Дальше на каждом шаге мы берём текущий занятый блок $i$, читаем его соседей

```python
ni, pi = Next[i], Prev[i]
```

и затем вырезаем этот блок из списка:

```python
if pi != -1:
    Next[pi] = ni
if ni != numSegments:
    Prev[ni] = pi
```

Поэтому если какой-то блок уже освобождали раньше, его уже нет в этом списке. Значит, $\text{pi}$ и $\text{ni}$ действительно являются ближайшими ещё занятыми соседями текущего блока.

После этого и формула длины читается прямо по границам. Новый свободный промежуток начинается сразу после левого занятого соседа, то есть в $x[\text{pi} + 1]$, и заканчивается в начале правого занятого соседа, то есть в $x[\text{ni}]$. Поэтому его длина равна $x[\text{ni}] - x[\text{pi} + 1]$.

</details>