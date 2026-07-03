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

Файлы примера: [C++](examples/example-11.cpp), [Python3](examples/example-11.py).

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

Файлы примера: [C++](examples/example-12.cpp), [Python3](examples/example-12.py).

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

Файлы примера: [C++](examples/example-13.cpp), [Python3](examples/example-13.py).

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

Файлы примера: [C++](examples/example-13.cpp), [Python3](examples/example-13.py).

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

Файлы примера: [C++](examples/example-14.cpp), [Python3](examples/example-14.py).

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