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

Файл примера: [Python3](examples/example-01.py).

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

Файл примера: [C++](examples/example-01.cpp).

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

Файл примера: [Python3](examples/example-02.py).

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

Файл примера: [C++](examples/example-02.cpp).

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

Цель — поменять хеш-функцию со стандартной на безопасную. Статья: https://codeforces.com/blog/entry/62393

В Python мы оборачиваем каждый ключ в свой класс и переопределяем для него `__hash__`.

> [!IMPORTANT]
> Это уже не обычные `int`-ключи, а отдельный тип.
> То есть вместо `x` в `dict` или `set` нужно класть `SafeInt(x)`.

> [!WARNING]
> Такой подход обычно тяжелее по времени и памяти, чем работа с обычными `int`.

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

Файл примера: [Python3](examples/example-03.py).

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

Файл примера: [C++](examples/example-03.cpp).

</details>