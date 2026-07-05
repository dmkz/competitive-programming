## 1. Stack, queue и deque в олимпиадном программировании

В задачах на обработку последовательностей чаще всего встречаются три базовые структуры данных:

- `stack`;
- `queue`;
- `deque`.

Их полезно воспринимать не как абстрактные объекты из учебника, а как инструменты, которые поддерживают нужный набор операций:

- сначала смотрим, какие операции нужны;
- потом выбираем самую простую структуру, которая их поддерживает;
- если стандартный контейнер неудобен, берём более практичную реализацию той же идеи.

---

## 2. Стек

Стек поддерживает операции только на конце структуры:

- добавить элемент в конец;
- получить последний элемент;
- удалить последний элемент.

То есть стек работает по принципу **LIFO**: последним пришёл — первым ушёл.

Стек полезен, когда нужно:

- откатить последнее действие;
- хранить незавершённые объекты;
- идти слева направо по последовательности и держать только её активный хвост;
- поддерживать монотонную структуру.

### Что обычно используют в C++?

Формально можно взять `stack<T>`:

```cpp
stack<int> st;
```

Но в олимпиадном программировании очень часто используют обычный `vector<T>`:

```cpp
vector<int> st;
st.push_back(x);
st.back();
st.pop_back();
```

Такой стек делает всё то же самое, что и `stack<T>`, но дополнительно позволяет:

- получать доступ к элементам по индексу;
- удобно хранить индексы, пары и другие структуры;
- печатать содержимое;
- при необходимости делать бинарный поиск по монотонному стеку.

### Что обычно используют в Python3?

В Python3 роль стека почти всегда играет обычный `list`:

```python
st = []
st.append(x)
st[-1]
st.pop()
```

Это естественный и быстрый выбор: операции на конце списка работают эффективно.

> [!NOTE]
> В Python3 `list.pop()` сразу удаляет элемент и возвращает его.
> В C++ у `vector` чтение вершины и удаление разделены: обычно сначала делают `st.back()`, а потом `st.pop_back()`.

### Простой пример: читаем числа и выводим их в обратном порядке

<details>
<summary><strong>C++: стек на vector</strong></summary>

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n;
	cin >> n;

	vector<int> st;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		st.push_back(x);
	}

	while (!st.empty()) {
		cout << st.back() << ' ';
		st.pop_back();
	}
	cout << '\n';
}
```

</details>

<details>
<summary><strong>Python3: стек на list</strong></summary>

```python
n = int(input())
st = list(map(int, input().split()))

while st:
	print(st.pop(), end=' ')
print()
```

</details>

<details>
<summary><strong>Пример ввода и вывода</strong></summary>

Для ввода

```text
5
3 1 4 1 5
```

получим вывод

```text
5 1 4 1 3
```

</details>

Файлы примера: [C++](examples/example-01.cpp), [Python3](examples/example-01.py).

---

## 3. Очередь

Очередь поддерживает другой набор операций:

- добавить элемент в конец;
- получить первый элемент;
- удалить первый элемент.

Это уже принцип **FIFO**: первым пришёл — первым ушёл.

Очередь используют, когда нужно:

- моделировать обработку запросов в порядке их поступления;
- хранить текущее начало обрабатываемой последовательности;
- работать с процессом, где элементы покидают структуру в порядке прихода.

### Что используют в C++?

Самый прямой вариант — `queue<T>`:

```cpp
queue<int> q;
```

У него есть `push`, `front`, `pop`, `empty`, `size`.

Иногда очередь удобно написать руками на `vector`, если хранить индекс головы:

```cpp
vector<int> q;
int head = 0;
```

Тогда добавление идёт через `push_back`, а удаление из начала превращается в `head++`.

> [!NOTE]
> Приём с `head` полезен, когда кроме обычных операций очереди нужен ещё доступ к элементам по индексу.

### Что используют в Python3?

В Python3 для очереди почти всегда используют `collections.deque`, а не `list`.

```python
from collections import deque

q = deque()
q.append(x)
q[0]
q.popleft()
```

> [!NOTE]
> В Python3 `deque.popleft()` сразу и удаляет элемент, и возвращает его.
> В C++ у `queue<T>` чтение и удаление разделены: сначала `q.front()`, потом `q.pop()`.

> [!WARNING]
> В Python3 не стоит моделировать очередь через `list.pop(0)`: этот вызов сдвигает элементы и в худшем случае работает за `O(n)`.

> [!NOTE]
> `queue<T>` в C++ специально имеет узкий интерфейс: у него нет индексации и по нему нельзя напрямую пройтись по элементам, как по обычному контейнеру.
> `collections.deque` в Python3 в этом смысле гибче: его можно итерировать, а к краям обращаться через индексы `q[0]` и `q[-1]`.

### Простой пример: читаем числа и выводим их в том же порядке

<details>
<summary><strong>C++: очередь на queue</strong></summary>

```cpp
#include <iostream>
#include <queue>
using namespace std;

int main() {
	int n;
	cin >> n;

	queue<int> q;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		q.push(x);
	}

	while (!q.empty()) {
		cout << q.front() << ' ';
		q.pop();
	}
	cout << '\n';
}
```

</details>

<details>
<summary><strong>Python3: очередь на deque</strong></summary>

```python
from collections import deque

n = int(input())
q = deque(map(int, input().split()))

while q:
	print(q.popleft(), end=' ')
print()
```

</details>

<details>
<summary><strong>Пример ввода и вывода</strong></summary>

Для ввода

```text
5
3 1 4 1 5
```

получим вывод

```text
3 1 4 1 5
```

</details>

Файлы примера: [C++](examples/example-02.cpp), [Python3](examples/example-02.py).

---

## 4. Двунаправленная очередь

`deque` — это структура, у которой активно используются оба конца.

Она умеет эффективно:

- добавлять элемент в начало;
- добавлять элемент в конец;
- получать элемент из начала и из конца;
- удалять элемент из начала и из конца.

Это особенно полезно в задачах, где структура живёт сразу на двух границах:

- очередь на минимум;
- монотонная очередь;
- поддержание активного отрезка;
- некоторые симуляции и специальные варианты BFS.

### `deque` в C++

В C++ `deque<T>` поддерживает оба конца и индексируется:

```cpp
deque<int> d;
d.push_front(x);
d.push_back(y);
d.front();
d.back();
d[i];
```

> [!IMPORTANT]
> В C++ `deque` можно индексировать эффективно за `O(1)`.

### `deque` в Python3

В Python3 снова используется `collections.deque`:

```python
from collections import deque

d = deque()
d.append(x)
d.appendleft(y)
d.pop()
d.popleft()
```

У него тоже есть индексация, то есть можно написать `d[i]`, но лучше этого никогда не делать, потому что:

> [!WARNING]
> В Python3 у `collections.deque` доступ по произвольному индексу в худшем случае линейный по длине структуры — необходимо физически пройти все элементы, пока не найдём нужный нам.

> [!NOTE]
> В Python3 методы `d.pop()` и `d.popleft()` возвращают удалённый элемент.
> В C++ у `deque` чтение и удаление тоже разделены: `d.back()` и `d.front()` читают значение, а `pop_back()` и `pop_front()` только удаляют его.

Если нужен частый доступ к середине по индексам, обычно лучше взять `list`.

### Простой пример: кладём числа то в начало, то в конец

<details>
<summary><strong>C++: базовые операции deque</strong></summary>

```cpp
#include <deque>
#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;

	deque<int> d;
	for (int i = 0; i < n; i++) {
		char side;
		int x;
		cin >> side >> x;

		if (side == 'L') {
			d.push_front(x);
		} else {
			d.push_back(x);
		}
	}

	for (int x : d) {
		cout << x << ' ';
	}
	cout << '\n';
}
```

</details>

<details>
<summary><strong>Python3: базовые операции deque</strong></summary>

```python
from collections import deque

n = int(input())
d = deque()

for _ in range(n):
	side, value = input().split()
	x = int(value)

	if side == 'L':
		d.appendleft(x)
	else:
		d.append(x)

print(*d)
```

</details>

<details>
<summary><strong>Пример ввода и вывода</strong></summary>

Для ввода

```text
5
L 3
R 8
L 1
R 7
L 2
```

получим вывод

```text
2 1 3 8 7
```

</details>

Файлы примера: [C++](examples/example-03.cpp), [Python3](examples/example-03.py).

---

## 5. Как быстро выбрать структуру

Выбор структуры начинается не с названия контейнера, а с набора операций, которые требует задача:

- нужен только конец структуры — стек;
- нужны добавление в конец и доступ к началу — очередь;
- нужны оба конца — `deque`;
- нужен частый доступ по индексу — массив или список.

---

## 6. Сложность основных операций

### C++

- `vector.push_back`, `vector.back`, `vector.pop_back` — `O(1)` амортизированно;
- `queue.push`, `queue.front`, `queue.pop` — `O(1)`;
- `deque.push_front`, `deque.push_back`, `deque.pop_front`, `deque.pop_back` — `O(1)`;
- `deque[i]` — `O(1)`.

### Python3

- `list.append`, чтение `list[-1]`, `list.pop()` — `O(1)` амортизированно;
- `deque.append`, `deque.appendleft`, `deque.pop`, `deque.popleft` — `O(1)`;
- `deque[i]` — в худшем случае `O(n)`.

---

## 7. Файлы с примерами

Стек на `vector` / `list`: [C++](examples/example-01.cpp), [Python3](examples/example-01.py).

Очередь: [C++](examples/example-02.cpp), [Python3](examples/example-02.py).

Двунаправленная очередь: [C++](examples/example-03.cpp), [Python3](examples/example-03.py).