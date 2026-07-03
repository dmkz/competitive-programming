<!-- Этот файл собран автоматически из README.md внутри Part-01-Arrays-and-lists, Part-02-Processing, Part-03-Sorting и Part-04-Binary-search. -->
<!-- Для обновления запустите: python build-readme.py -->

# Лекция 1. Массивы, сортировки, бинарный поиск в отсортированном массиве

## 1. Массивы

**Массив** — это способ хранения последовательности элементов, к которым можно обращаться по их номеру (индексу). Например, если дан массив `a`, то:
- `a[0]` — первый элемент;
- `a[1]` — второй элемент;
- `a[i]` — элемент с индексом `i`.

> [!NOTE]
> В C++ и Python3 индексация обычно начинается с `0`.
> Если в массиве `n` элементов, то допустимые индексы — от `0` до `n - 1`.

В задачах спортивного программирования массивы используются:
- для хранения входных данных;
- для обработки последовательностей чисел;
- для поиска минимума, максимума, суммы, количества подходящих элементов;
- как основа для более сложных структур и алгоритмов.

---

## 2. Какие массивы есть в C++

Для хранения последовательности целых чисел в C++ чаще всего встречаются три варианта:

```cpp
int a[N];        // 1) статический массив из C
array<int, N> a; // 2) статический массив из C++
vector<int> a;   // 3) динамический массив из C++
```

### `int a[N]`

Обычный статический массив.

```cpp
int a[100];
```

Его размер фиксирован заранее и не меняется во время работы программы.

### `array<int, N> a`

Контейнер из стандартной библиотеки, который тоже имеет фиксированный размер.

```cpp
#include <array>
using namespace std;

array<int, 100> a;
```

Он удобнее обычного массива, потому что поддерживает методы `.size()`, `.begin()`, `.end()` и хорошо работает со стандартными алгоритмами.

### `vector<int> a`

Динамический массив.

```cpp
#include <vector>
using namespace std;

vector<int> a;
```

Его размер можно менять во время работы программы: добавлять элементы в конец, удалять последний элемент, создавать вектор нужной длины.

> [!IMPORTANT]
> В спортивном программировании чаще всего рекомендуется использовать именно `vector<int>` из-за удобства, безопасности и хорошей совместимости со стандартной библиотекой.

---

## 3. Что использовать в Python3

В Python3 на первом занятии почти все задачи на массивы удобно решать с помощью списка `list`.

### `list`

Список `list` — это динамический массив.

```python
a = []
```

Его размер можно менять во время работы программы: добавлять элементы в конец, удалять последний элемент, создавать список нужной длины.

Пример:

```python
n = int(input())
a = [0] * n
```

Здесь создаётся список из `n` элементов, каждый из которых изначально равен `0`.

> [!IMPORTANT]
> В задачах спортивного программирования список `list` в Python3 обычно играет ту же роль, что и `vector<int>` в C++.

---

## 4. Преимущество `vector`

Топ-5 причин использования `vector`:

- размер можно задавать во время выполнения программы;
- можно легко добавлять элементы в конец;
- контейнер поддерживает полезные методы;
- удобно передавать в алгоритмы стандартной библиотеки;
- такой код обычно проще читать и сопровождать.

Пример:

```cpp
int n;
cin >> n;
vector<int> a(n);
```

Здесь размер массива определяется входными данными, а не фиксируется заранее в коде.

---

## 5. Основные операции с `vector`

Ниже перечислены самые важные действия, которые нужно знать на первом занятии.

```cpp
vector<int> a(n);   // создать вектор из n элементов
int sz = a.size();  // получить размер
int x = a[i];       // получить элемент с индексом i
a[i] = 10;          // изменить элемент с индексом i
a.push_back(x);     // добавить x в конец
a.pop_back();       // удалить последний элемент
```

> [!WARNING]
> Метод `pop_back()` можно вызывать только у непустого вектора.

Ещё один полезный пример:

```cpp
vector<int> a;
a.push_back(5);
a.push_back(8);
a.push_back(13);
```

После этого вектор содержит три элемента: `5`, `8`, `13`.

Полный пример с основными операциями: [C++](Part-01-Arrays-and-lists/examples/example-01.cpp), [Python3](Part-01-Arrays-and-lists/examples/example-01.py).

---

## 6. Основные операции со списком `list`

Ниже перечислены самые важные действия, которые нужно знать на первом занятии.

```python
a = [0] * n      # создать список из n элементов
sz = len(a)      # получить размер
x = a[i]         # получить элемент с индексом i
a[i] = 10        # изменить элемент с индексом i
a.append(x)      # добавить x в конец
a.pop()          # удалить последний элемент
```

> [!WARNING]
> Метод `pop()` без аргументов можно вызывать только у непустого списка.

Ещё один полезный пример:

```python
a = []
a.append(5)
a.append(8)
a.append(13)
```

После этого список содержит три элемента: `5`, `8`, `13`.

Полный пример с основными операциями: [C++](Part-01-Arrays-and-lists/examples/example-01.cpp), [Python3](Part-01-Arrays-and-lists/examples/example-01.py).

---

## 7. Чтение и вывод массива

### Вариант 1. Сразу создать вектор нужного размера

<details>
<summary><strong>C++: чтение и вывод элементов в исходном порядке</strong></summary>

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}
```

**Пример**

Ввод:

```text
5
1 3 5 7 9
```

Вывод:

```text
1 3 5 7 9
```

</details>

Файлы примера: [C++](Part-01-Arrays-and-lists/examples/example-02.cpp), [Python3](Part-01-Arrays-and-lists/examples/example-02.py).

### Вариант 2. Считывать элементы и добавлять их в конец

<details>
<summary><strong>C++: чтение через push_back и вывод в обратном порядке</strong></summary>

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> a;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }

    for (int i = n - 1; i >= 0; i--) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}
```

**Пример**

Ввод:

```text
5
1 3 5 7 9
```

Вывод:

```text
9 7 5 3 1
```

</details>

Файлы примера: [C++](Part-01-Arrays-and-lists/examples/example-03.cpp), [Python3](Part-01-Arrays-and-lists/examples/example-03.py).

### Аналогичные примеры на Python

<details>
<summary><strong>Python: чтение списка и вывод в исходном порядке</strong></summary>

```python
n = int(input())
a = list(map(int, input().split()))

for x in a:
    print(x, end=' ')
print()
```

</details>

<details>
<summary><strong>Python: чтение и вывод в обратном порядке</strong></summary>

```python
n = int(input())
a = list(map(int, input().split()))

for i in range(n - 1, -1, -1):
    print(a[i], end=' ')
print()
```

</details>

> [!NOTE]
> Во всех дальнейших примерах на Python3 под массивом мы будем понимать именно список `list`.

---

## 8. Обработка массивов

При обработке массива обычно требуется найти какую-то характеристику:
- сумму элементов;
- минимум или максимум;
- количество элементов, удовлетворяющих условию;
- первую или последнюю позицию нужного элемента.

Делать это можно двумя способами:

1. Написать обработку вручную с помощью цикла `for`.
2. Использовать готовые алгоритмы стандартной библиотеки C++.

Оба подхода важны.

- Ручной способ нужен всегда, потому что не для каждой задачи есть готовая функция.
- Стандартные алгоритмы позволяют писать код короче и часто делают намерение программы более понятным.

---

## 9. Итераторы и диапазоны

Чтобы использовать многие алгоритмы стандартной библиотеки C++, нужно понимать, что такое **итераторы**.

Для вектора чаще всего используются:

```cpp
a.begin(); // итератор на первый элемент
a.end();   // итератор на позицию после последнего элемента
```

Если известен итератор, то значение элемента можно получить с помощью разыменования (звёздочки):

```cpp
*a.begin()
```

Это значение первого элемента массива.

> [!CAUTION]
> Разыменовывать `a.end()` нельзя.
> Итератор `a.end()` указывает не на существующий элемент, а на позицию сразу после последнего.

### Полуинтервал `[begin, end)`

Почти все стандартные алгоритмы C++ работают с полуинтервалом:

```text
[begin, end)
```

Это означает:
- левая граница включается;
- правая граница не включается.

Например, запись

```cpp
accumulate(a.begin(), a.end(), 0)
```

означает: обработать все элементы вектора `a` от первого до последнего.

---

## 10. Сумма элементов

### Вручную

```cpp
long long sum = 0;
for (int i = 0; i < n; i++) {
    sum += a[i];
}
cout << sum << '\n';
```

### С помощью `std::accumulate`

```cpp
#include <numeric>

cout << accumulate(a.begin(), a.end(), 0LL) << '\n';
```

> [!NOTE]
> Функция `accumulate` принимает диапазон и начальное значение.
> Здесь используется `0LL`, чтобы суммирование происходило в типе `long long` и не возникло переполнения `int`.

### Python

```python
a = list(map(int, input().split()))
print(sum(a))
```

Файлы примера: [C++](Part-02-Processing/examples/example-04.cpp), [Python3](Part-02-Processing/examples/example-04.py).

---

## 11. Минимум и максимум

### Вручную

```cpp
int mn = a[0], mx = a[0];
for (int i = 1; i < n; i++) {
    if (a[i] < mn) {
        mn = a[i];
    }
    if (a[i] > mx) {
        mx = a[i];
    }
}
cout << mn << ' ' << mx << '\n';
```

> [!TIP]
> Не стоит называть переменные `min` и `max`, потому что такие имена могут конфликтовать с функциями `std::min` и `std::max`.

### С помощью `std::minmax_element`

```cpp
#include <algorithm>

auto [mn_it, mx_it] = minmax_element(a.begin(), a.end());
cout << *mn_it << ' ' << *mx_it << '\n';
```

### Python

```python
a = list(map(int, input().split()))
print(min(a), max(a))
```

Файлы примера: [C++](Part-02-Processing/examples/example-05.cpp), [Python3](Part-02-Processing/examples/example-05.py).

---

## 12. Максимум, его количество и позиции

Пусть требуется найти:
- значение максимального элемента;
- сколько раз он встречается;
- позицию первого вхождения;
- позицию последнего вхождения.

### Вручную

```cpp
int mx = a[0];
int cnt = 1;
int first = 0;
int last = 0;

for (int i = 1; i < n; i++) {
    if (a[i] > mx) {
        // встретили новый максимум
        mx = a[i];
        cnt = 1;
        first = i;
        last = i;
    } else if (a[i] == mx) {
        // встретили тот же самый максимум
        cnt++;
        last = i;
    }
}

cout << mx << ' ' << cnt << ' ' << first << ' ' << last << '\n';
```

### С помощью стандартных функций

```cpp
#include <algorithm>
#include <iterator>

auto mx_it = max_element(a.begin(), a.end());
int mx = *mx_it;
int cnt = count(a.begin(), a.end(), mx);
int first = mx_it - a.begin();
int last = (int)a.size() - 1 - (find(a.rbegin(), a.rend(), mx) - a.rbegin());

cout << mx << ' ' << cnt << ' ' << first << ' ' << last << '\n';
```

> [!IMPORTANT]
> Здесь используется несколько проходов по массиву.
> Это нормально: стандартная библиотека делает код короче, но не всегда позволяет решить всё за один проход.

> [!NOTE]
> Методы `a.rbegin()` и `a.rend()` задают обратный обход массива, то есть от последнего элемента к первому.

### Python

```python
a = list(map(int, input().split()))
mx = max(a)
cnt = a.count(mx)
first = a.index(mx)
last = len(a) - 1 - a[::-1].index(mx)
print(mx, cnt, first, last)
```

### Более эффективный вариант на Python за один проход

```python
a = list(map(int, input().split()))
mx = a[0]
cnt = 1
first = 0
last = 0

for i in range(1, len(a)):
    if a[i] > mx:
        # встретили новый максимум
        mx = a[i]
        cnt = 1
        first = i
        last = i
    elif a[i] == mx:
        # встретили тот же самый максимум
        cnt += 1
        last = i

print(mx, cnt, first, last)
```

Файлы примера: [C++](Part-02-Processing/examples/example-06.cpp), [Python3](Part-02-Processing/examples/example-06.py).

---

## 13. Типичные ошибки

<details>
<summary><strong>Раскрыть список типичных ошибок</strong></summary>

### 1. Выход за границы массива

Нельзя обращаться к `a[n]`, если в массиве `n` элементов.
Последний допустимый индекс — `n - 1`.

### 2. Обработка пустого массива

Код вида

```cpp
int mn = a[0];
```

корректен только тогда, когда массив не пустой.

### 3. Переполнение типа `int`

Если сумма элементов может быть большой, нужно использовать `long long`.

### 4. Ошибка в обратном проходе

Правильный цикл по индексам справа налево выглядит так:

```cpp
for (int i = n - 1; i >= 0; i--)
```

### 5. Неаккуратные имена переменных

Лучше использовать `mn`, `mx`, `sum`, `cnt`, чем называть переменные `min`, `max` или `count`.

</details>

---

## 14. Сортировка массива

**Сортировка** — это упорядочивание элементов массива по некоторому правилу.

Чаще всего массив сортируют:
- по возрастанию;
- по убыванию;
- по собственному правилу сравнения.

После сортировки массивом часто удобнее пользоваться дальше: искать минимум и максимум, группировать одинаковые элементы, применять бинарный поиск.

---

## 15. Сортировка по возрастанию

### C++

Для сортировки массива или вектора по возрастанию обычно используется `std::sort`.

```cpp
#include <algorithm>

sort(a.begin(), a.end());
```

Здесь, как и раньше, используется полуинтервал `[begin, end)`, то есть сортируются все элементы от первого до последнего.

### Python3

В Python3 есть два основных варианта:

```python
a.sort()
```

или

```python
b = sorted(a)
```

- `a.sort()` сортирует список `a` на месте;
- `sorted(a)` создаёт и возвращает новый отсортированный список.

Файлы примера: [C++](Part-03-Sorting/examples/example-07.cpp), [Python3](Part-03-Sorting/examples/example-07.py).

---

## 16. Сортировка по убыванию

### C++

В C++ есть два популярных способа отсортировать вектор по убыванию.

### Способ 1. Через обратные итераторы

```cpp
sort(a.rbegin(), a.rend());
```

Здесь сортировка идёт по тому же правилу `<`, но обход массива рассматривается справа налево.

### Способ 2. Через `greater<int>()`

```cpp
#include <algorithm>
#include <functional>

sort(a.begin(), a.end(), greater<int>());
```

Здесь порядок задаётся явно: больший элемент должен идти раньше меньшего.

### Python3

В Python3 для сортировки по убыванию обычно используется аргумент `reverse=True`.

```python
a.sort(reverse=True)
```

или

```python
b = sorted(a, reverse=True)
```

Файлы примера: [C++](Part-03-Sorting/examples/example-07.cpp), [Python3](Part-03-Sorting/examples/example-07.py).

---

## 17. `stable_sort` и устойчивость сортировки

Иногда важно не только отсортировать элементы, но и сохранить относительный порядок равных элементов.

Такая сортировка называется **устойчивой**.

### C++

Для этого используется `stable_sort`.

```cpp
#include <algorithm>

stable_sort(a.begin(), a.end());
```

Если сортировка идёт по какому-то полю или по собственному правилу, то компаратор можно передать так же, как и в `sort`.

```cpp
stable_sort(a.begin(), a.end(), cmp);
```

> [!IMPORTANT]
> `sort` работает быстро, но не обязан сохранять порядок равных элементов.
> `stable_sort` специально сохраняет этот порядок.

### Python3

В Python3 встроенные сортировки `list.sort()` и `sorted()` уже являются устойчивыми.

Это означает, что отдельного аналога `stable_sort` обычно не нужно: стандартная сортировка Python3 уже ведёт себя как устойчивая.

Файлы примера: [C++](Part-03-Sorting/examples/example-08.cpp), [Python3](Part-03-Sorting/examples/example-08.py).

---

## 18. Компаратор в C++ и Python3

Иногда сортировать нужно не просто по возрастанию или убыванию, а по своему правилу.

### C++

В C++ для этого в `sort` или `stable_sort` передают **компаратор**.

Компаратор — это функция, лямбда-функция или функциональный объект, который по двум элементам отвечает, должен ли первый идти раньше второго.

Например, так можно сортировать числа по возрастанию абсолютного значения:

```cpp
#include <algorithm>
#include <cmath>

sort(a.begin(), a.end(), [](int x, int y) {
    if (abs(x) != abs(y)) {
        return abs(x) < abs(y);
    }
    return x < y;
});
```

> [!WARNING]
> Компаратор должен задавать корректный строгий порядок.
> Например, писать `return x <= y;` нельзя: такой код может привести к некорректной работе сортировки.

### Python3

В Python3 обычно передают не компаратор, а **key-функцию**.

Она для каждого элемента вычисляет ключ, по которому и будет происходить сортировка.

```python
a.sort(key=lambda x: (abs(x), x))
```

Здесь сначала элементы сравниваются по `abs(x)`, а при равенстве — по самому значению `x`.

> [!NOTE]
> В Python3 тоже можно имитировать компаратор через `functools.cmp_to_key`, но в большинстве задач удобнее и проще использовать именно `key`.

Файлы примера: [C++](Part-03-Sorting/examples/example-09.cpp), [Python3](Part-03-Sorting/examples/example-09.py).

---

## 19. Сортировка слиянием

Стандартная сортировка очень удобна, но полезно уметь написать сортировку и вручную.

Один из самых важных алгоритмов такого типа — **сортировка слиянием**.

<details>
<summary><strong>C++: сортировка слиянием</strong></summary>

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> merge_sort(const vector<int>& a) {
    if (a.size() <= 1) {
        return a;
    }

    int mid = (int)a.size() / 2;

    // Разбиваем массив на две половины и сортируем их отдельно
    vector<int> left(a.begin(), a.begin() + mid);
    vector<int> right(a.begin() + mid, a.end());
    left = merge_sort(left);
    right = merge_sort(right);

    // Сливаем две уже отсортированные половины в один отсортированный массив
    vector<int> merged;
    merged.reserve(a.size());

    int i = 0;
    int j = 0;
    while (i < (int)left.size() && j < (int)right.size()) {
        if (left[i] <= right[j]) {
            merged.push_back(left[i]);
            i++;
        } else {
            merged.push_back(right[j]);
            j++;
        }
    }

    // Добавляем хвост той половины, в которой ещё остались элементы
    while (i < (int)left.size()) {
        merged.push_back(left[i]);
        i++;
    }
    while (j < (int)right.size()) {
        merged.push_back(right[j]);
        j++;
    }

    return merged;
}

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    a = merge_sort(a);

    for (int x : a) {
        cout << x << ' ';
    }
    cout << '\n';
}
```

</details>

<details>
<summary><strong>Python3: сортировка слиянием</strong></summary>

```python
def merge_sort(a):
    if len(a) <= 1:
        return a

    mid = len(a) // 2

    # Разбиваем список на две половины и сортируем их отдельно
    left = merge_sort(a[:mid])
    right = merge_sort(a[mid:])

    # Сливаем две уже отсортированные половины в один отсортированный список
    merged = []
    i = 0
    j = 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            merged.append(left[i])
            i += 1
        else:
            merged.append(right[j])
            j += 1

    # Добавляем оставшиеся элементы
    while i < len(left):
        merged.append(left[i])
        i += 1
    while j < len(right):
        merged.append(right[j])
        j += 1

    return merged


n = int(input())
a = list(map(int, input().split()))
a = merge_sort(a)
print(*a)
```

</details>

Файлы примера: [C++](Part-03-Sorting/examples/example-10.cpp), [Python3](Part-03-Sorting/examples/example-10.py).

---

## 20. Как работает сортировка слиянием

Сортировка слиянием состоит из трёх основных этапов.

1. **Разделение.**
   Массив делится примерно пополам, затем каждая половина снова делится пополам, и так далее, пока не останутся массивы длины `0` или `1`.

2. **Рекурсивная сортировка половин.**
   Левая и правая половины сортируются тем же самым алгоритмом.

3. **Слияние.**
   Два уже отсортированных массива объединяются в один: каждый раз берётся меньший из двух текущих элементов.

Именно этап слияния делает алгоритм удобным и понятным.

> [!NOTE]
> Сортировка слиянием работает за `O(n log n)` и требует дополнительной памяти `O(n)`.

> [!TIP]
> Если при равенстве элементов сначала брать элемент из левой половины, сортировка получится устойчивой.

---

## 21. Типичные ошибки при сортировке

<details>
<summary><strong>Раскрыть список типичных ошибок</strong></summary>

### 1. Забыт `#include <algorithm>`

Без этого заголовка `sort` и `stable_sort` в C++ не будут доступны.

### 2. Использован некорректный компаратор

Код вида

```cpp
return x <= y;
```

для компаратора писать нельзя.

### 3. Ошибка с `sort()` в Python3

Метод `a.sort()` сортирует список на месте и ничего не возвращает.
Поэтому запись

```python
a = a.sort()
```

неправильна.

### 4. Забыли добавить хвост при слиянии

После основного цикла в сортировке слиянием нужно обязательно дописать оставшиеся элементы из одной из половин.

### 5. Перепутали `sort` и `stable_sort`

Если порядок равных элементов важен, нужно использовать `stable_sort` в C++ или помнить, что сортировка в Python3 уже устойчива.

</details>

---

## 22. Что такое бинарный поиск

**Бинарный поиск** — это способ быстро работать с **отсортированным** массивом.

Идея очень простая:
- смотрим на элемент в середине массива;
- если он слишком маленький, отбрасываем левую половину;
- если он слишком большой, отбрасываем правую половину;
- продолжаем так, пока не найдём ответ.

Главная польза бинарного поиска в том, что за один шаг он отбрасывает примерно половину вариантов.

Поэтому время работы бинарного поиска равно `O(log n)`.

Бинарный поиск нужен не только для проверки, есть ли элемент в массиве. С его помощью удобно:
- искать конкретный элемент;
- находить первую подходящую позицию;
- считать количество элементов, удовлетворяющих условию;
- находить границы группы одинаковых элементов.

> [!IMPORTANT]
> Обычный бинарный поиск по массиву работает только тогда, когда массив отсортирован.

---

## 23. Простейший бинарный поиск: поиск элемента

Пусть дан отсортированный массив `a` и число `x`.
Нужно найти индекс элемента `x` или сообщить, что такого элемента нет.

### C++

<details>
<summary><strong>C++: поиск элемента вручную</strong></summary>

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int x;
    cin >> x;

    // Поддерживаем текущий отрезок поиска и каждый раз отбрасываем половину
    int left = 0;
    int right = n - 1;
    int answer = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (a[mid] == x) {
            answer = mid;
            break;
        }
        if (a[mid] < x) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << answer << '\n';
}
```

</details>

### Python3

<details>
<summary><strong>Python3: поиск элемента вручную</strong></summary>

```python
n = int(input())
a = list(map(int, input().split()))
x = int(input())

# Поддерживаем текущий отрезок поиска и каждый раз отбрасываем половину
left = 0
right = n - 1
answer = -1

while left <= right:
    mid = (left + right) // 2
    if a[mid] == x:
        answer = mid
        break
    if a[mid] < x:
        left = mid + 1
    else:
        right = mid - 1

print(answer)
```

</details>

> [!NOTE]
> Если одинаковых элементов несколько, такая реализация может вернуть любой подходящий индекс, а не обязательно первый.

Файлы примера: [C++](Part-04-Binary-search/examples/example-11.cpp), [Python3](Part-04-Binary-search/examples/example-11.py).

---

## 24. Первый элемент, не меньший `x`

Очень частая задача: найти **первый элемент, который больше либо равен `x`**.

Именно эта версия бинарного поиска лежит в основе `lower_bound`.

### C++

<details>
<summary><strong>C++: первый элемент >= x вручную</strong></summary>

```cpp
int left = 0;
int right = n;

// Ищем минимальный индекс, на котором a[index] >= x
while (left < right) {
    int mid = left + (right - left) / 2;
    if (a[mid] < x) {
        left = mid + 1;
    } else {
        right = mid;
    }
}

if (left == n) {
    cout << -1 << '\n';
} else {
    cout << left << ' ' << a[left] << '\n';
}
```

</details>

### Python3

<details>
<summary><strong>Python3: первый элемент >= x вручную</strong></summary>

```python
left = 0
right = n

# Ищем минимальный индекс, на котором a[index] >= x
while left < right:
    mid = (left + right) // 2
    if a[mid] < x:
        left = mid + 1
    else:
        right = mid

if left == n:
    print(-1)
else:
    print(left, a[left])
```

</details>

> [!TIP]
> Если ответом является первый элемент `>= x`, то для поиска максимального элемента `< x` часто достаточно взять предыдущую позицию.

Файлы примера: [C++](Part-04-Binary-search/examples/example-12.cpp), [Python3](Part-04-Binary-search/examples/example-12.py).

---

## 25. Стандартные алгоритмы бинарного поиска

### C++

В C++ для бинарного поиска по отсортированному диапазону чаще всего используются четыре функции.

```cpp
#include <algorithm>

lower_bound(a.begin(), a.end(), x);  // первый элемент >= x
upper_bound(a.begin(), a.end(), x);  // первый элемент > x
binary_search(a.begin(), a.end(), x); // существует ли x в массиве
equal_range(a.begin(), a.end(), x);   // пара итераторов [lower_bound, upper_bound)
```

### Python3

В Python3 для таких задач обычно используется модуль `bisect`.

```python
from bisect import bisect_left, bisect_right

left = bisect_left(a, x)   # первый элемент >= x
right = bisect_right(a, x) # первый элемент > x
```

Прямых функций с именами `binary_search` и `equal_range` в Python3 нет, но их аналоги легко получить:
- элемент найден, если `left < len(a)` и `a[left] == x`;
- диапазон равных `x` элементов — это полуинтервал `[left, right)`.

Файлы примера: [C++](Part-04-Binary-search/examples/example-13.cpp), [Python3](Part-04-Binary-search/examples/example-13.py).

---

## 26. Как проверить, что элемент найден

После вызова `lower_bound` важно не забыть проверить, действительно ли найденный итератор указывает на `x`.

### C++

```cpp
auto it = lower_bound(a.begin(), a.end(), x);
if (it != a.end() && *it == x) {
    cout << "YES\n";
} else {
    cout << "NO\n";
}
```

Если использовать `equal_range`, то элемент найден тогда и только тогда, когда диапазон не пустой:

```cpp
auto [first, last] = equal_range(a.begin(), a.end(), x);
if (first != last) {
    cout << "YES\n";
}
```

### Python3

```python
from bisect import bisect_left

pos = bisect_left(a, x)
found = pos < len(a) and a[pos] == x
```

> [!WARNING]
> Сам по себе результат `lower_bound` или `bisect_left` ещё не означает, что `x` найден.
> Он может указывать на первый элемент, который просто больше `x`.

---

## 27. Количество элементов `< x`, `= x` и `> x`

Если известны результаты `lower_bound` и `upper_bound`, то многие вопросы решаются сразу.

### C++

```cpp
auto lower = lower_bound(a.begin(), a.end(), x);
auto upper = upper_bound(a.begin(), a.end(), x);

int less = lower - a.begin();
int equal = upper - lower;
int greater = a.end() - upper;
```

Здесь:
- `less` — количество элементов, меньших `x`;
- `equal` — количество элементов, равных `x`;
- `greater` — количество элементов, больших `x`.

Количество равных элементов можно получить и через `equal_range`:

```cpp
auto [first, last] = equal_range(a.begin(), a.end(), x);
int equal = last - first;
```

### Python3

```python
from bisect import bisect_left, bisect_right

left = bisect_left(a, x)
right = bisect_right(a, x)

less = left
equal = right - left
greater = len(a) - right
```

Файлы примера: [C++](Part-04-Binary-search/examples/example-13.cpp), [Python3](Part-04-Binary-search/examples/example-13.py).

---

## 28. Максимальный элемент, который `< x`

Эта задача тоже очень полезна.

### Ручная реализация

Можно искать **последний индекс**, на котором `a[index] < x`.

### C++

```cpp
int left = -1;
int right = n;

while (right - left > 1) {
    int mid = left + (right - left) / 2;
    if (a[mid] < x) {
        left = mid;
    } else {
        right = mid;
    }
}

if (left == -1) {
    cout << "NO\n";
} else {
    cout << a[left] << '\n';
}
```

### Python3

```python
left = -1
right = n

while right - left > 1:
    mid = (left + right) // 2
    if a[mid] < x:
        left = mid
    else:
        right = mid

if left == -1:
    print("NO")
else:
    print(a[left])
```

### Трюк через `lower_bound` и предыдущий элемент

Если уже умеем находить первый элемент `>= x`, то максимальный элемент `< x` получается почти бесплатно.

### C++

```cpp
#include <algorithm>
#include <iterator>

auto it = lower_bound(a.begin(), a.end(), x);
if (it == a.begin()) {
    cout << "NO\n";
} else {
    cout << *prev(it) << '\n';
}
```

### Python3

```python
from bisect import bisect_left

pos = bisect_left(a, x)
if pos == 0:
    print("NO")
else:
    print(a[pos - 1])
```

Именно поэтому часто достаточно найти первый элемент `>= x`, а затем просто перейти на одну позицию влево.

Файлы примера: [C++](Part-04-Binary-search/examples/example-14.cpp), [Python3](Part-04-Binary-search/examples/example-14.py).

---

## 29. Типичные ошибки при бинарном поиске

<details>
<summary><strong>Раскрыть список типичных ошибок</strong></summary>

### 1. Бинарный поиск запускается по неотсортированному массиву

Если массив не отсортирован, бинарный поиск работать корректно не будет.

### 2. Перепутаны границы цикла

Нужно аккуратно различать два популярных шаблона:
- поиск на отрезке `[left, right]`;
- поиск на полуинтервале `[left, right)`.

Смешивать их между собой нельзя.

### 3. Не проверили, что ответ существует

После `lower_bound` нужно проверить `it != a.end()`.
После `bisect_left` нужно проверить `pos < len(a)`.

### 4. Ожидали, что простой поиск элемента вернёт первое вхождение

Обычная версия бинарного поиска на равных элементах не обязана возвращать именно первое вхождение.
Для этого нужно искать первый элемент `>= x`.

### 5. Пытаются взять предыдущий элемент, когда его нет

Нельзя вызывать `prev(a.begin())`.
Нельзя брать `a[pos - 1]`, если `pos == 0`.

</details>

---
