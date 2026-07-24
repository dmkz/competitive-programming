# Разбор задач

В лекции про два указателя и скользящее окно мы чаще рассуждали так: двигали правую границу и для каждого $R$ подбирали подходящую левую границу $L$.

В разборе задач мы смотрим на тот же процесс с другой стороны: фиксируем левую границу и двигаем правую как можно дальше, пока условие ещё выполняется.

Поэтому дальше почти в каждой задаче будет возникать один и тот же вопрос: какой максимальный полуинтервал $[i, j)$ можно удержать для фиксированного $i$.

Для удобства работаем с полуинтервалами $[i, j)$, где $i$ — левая граница, а $j$ — позиция сразу за правой. Тогда длина окна равна просто $j - i$.

## A. Слишком много ошибок

<details>
<summary>Текстовый разбор</summary>

Пройдёмся по строке слева направо. Поддерживаем текущее окно и считаем, сколько символов `x` попало внутрь. Как только количество `x` превысило $k$, дальше расширять окно уже нельзя: условие только ухудшится. Значит, для каждой левой границы $i$ можно найти максимальную правую границу $j$ такую, что полуинтервал $[i, j)$ ещё подходит.

Когда левая граница сдвигается вправо на один символ, правую границу заново не ищем. Всё, что до текущего $j$, мы уже проверили, а двигать $j$ назад смысла нет. Поэтому оба указателя идут только вправо и проходят строку не более одного раза.

Внутри окна достаточно хранить только количество символов `x`: при добавлении нового символа справа увеличиваем счётчик, а при уходе старого символа слева — уменьшаем (при необходимости).

Асимптотика: $O(n)$ по времени и $O(1)$ по дополнительной памяти на один набор.

</details>

<details>
<summary>Решение на C++</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем данные:
    int n, k; cin >> n >> k;
    string s; cin >> s;
    // методом двух указателей ищем подходящий отрезок:
    int cntX = 0, j = 0, answ = 0;
    for (int i = 0; i < n; i++) {
        // двигаем правую границу:
        while (j < n && (s[j] == '.' || (s[j] == 'x' && cntX + 1 <= k))) {
            cntX += (s[j] == 'x');
            j++;
        }
        // полуинтервал [i, j) подходит
        if (i <= j)
            answ = max(answ, j - i);
        // удаляем i-й символ
        if (s[i] == 'x')
            cntX--;
    }
    cout << answ << '\n';
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
    # читаем данные:
    n, k = map(int, input().split())
    s = input()
    # методом двух указателей ищем подходящий отрезок:
    cnt_x = 0
    j = 0
    answ = 0
    for i in range(n):
        # двигаем правую границу:
        while j < n and (s[j] == '.' or (s[j] == 'x' and cnt_x + 1 <= k)):
            cnt_x += (s[j] == 'x')
            j += 1
        # полуинтервал [i, j) подходит
        if i <= j:
            answ = max(answ, j - i)
        # удаляем i-й символ
        if s[i] == 'x':
            cnt_x -= 1
    print(answ)


tt = int(input())
while tt > 0:
    solve()
    tt -= 1
```

</details>

## B. Уникальные элементы в круговом окне

<details>
<summary>Текстовый разбор</summary>

Чтобы работать с круговым массивом, сначала уберём саму окружность: просто продублируем массив. Тогда окно длины $k$, которое по кругу начинается в позиции $i$, превратится в обычный полуинтервал $[i, i + k)$ в массиве длины $2n$. После этого задача уже сводится к обычному скользящему окну.

Но считать нужно не просто количество различных значений, а количество значений, которые встречаются ровно один раз. Поэтому вместе со словарём частот держим ещё один счётчик, `cntUniq`. Когда окно сдвигается, меняется частота только у двух элементов: один ушёл слева, один пришёл справа. Значит, для обновления счётчика достаточно аккуратно обрабатывать четыре перехода частоты: $0 \to 1$ (делаем $+1$), $1 \to 2$ (делаем $-1$), $2 \to 1$ (делаем $+1$) и $1 \to 0$ (делаем $-1$).

Сначала набираем первое окно длины $k$, потом $n - 1$ раз сдвигаем его на один вправо и каждый раз быстро обновляем `cntUniq`. В C++ в этой версии решения частоты хранятся в `map`, поэтому получается $O(n \log (n))$. В Python3 удобно взять `defaultdict(int)`, и тогда средняя асимптотика становится линейной. По памяти в обоих случаях нужно $O(n)$.

</details>

<details>
<summary>Решение на C++</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем массив и сразу же дублируем его:
    int n, k; cin >> n >> k;
    vector<int> a(2 * n);
    for (int i = 0; i < n; i++)
        cin >> a[i], a[i+n] = a[i];
    // поддерживаем окно длины k. Вспомогательные функции:
    vector<int> answer(n);
    map<int, int> cnt;
    int cntUniq = 0;
    auto add = [&](int x) {
        cnt[x]++;
        if (cnt[x] == 1) // стало равным 1
            cntUniq++;
        else if (cnt[x] == 2) // стало равным 2
            cntUniq--;
    };
    auto rem = [&](int x) {
        cnt[x]--;
        if (cnt[x] == 0) // стало равным 0
            cntUniq--;
        else if (cnt[x] == 1) // стало равным 1
            cntUniq++;
    };
    // Набираем начальное окно:
    for (int i = 0; i < k; i++)
        add(a[i]);
    answer[0] = cntUniq;
    // двигаем окно и записываем ответ:
    for (int i = 1; i < n; i++) {
        rem(a[i-1]);
        add(a[i+k-1]);
        answer[i] = cntUniq;
    }
    // выводим ответ:
    for (int i = 0; i < n; i++)
        cout << answer[i] << ' ';
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
from collections import defaultdict

def solve():
    # читаем массив и сразу же дублируем его:
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    a += a
    # поддерживаем окно длины k. Вспомогательные функции:
    answer = [0] * n
    cnt = defaultdict(int)
    cnt_uniq = 0

    def add(x):
        nonlocal cnt_uniq
        cnt[x] += 1
        if cnt[x] == 1:  # стало равным 1
            cnt_uniq += 1
        elif cnt[x] == 2:  # стало равным 2
            cnt_uniq -= 1

    def rem(x):
        nonlocal cnt_uniq
        cnt[x] -= 1
        if cnt[x] == 0:  # стало равным 0
            cnt_uniq -= 1
            del cnt[x]
        elif cnt[x] == 1:  # стало равным 1
            cnt_uniq += 1

    # Набираем начальное окно:
    for i in range(k):
        add(a[i])
    answer[0] = cnt_uniq
    # двигаем окно и записываем ответ:
    for i in range(1, n):
        rem(a[i - 1])
        add(a[i + k - 1])
        answer[i] = cnt_uniq
    # выводим ответ:
    print(*answer)


tt = int(input())
while tt > 0:
    solve()
    tt -= 1
```

</details>

## C. Два двойных указателя

<details>
<summary>Текстовый разбор</summary>

Здесь у окна сразу два ограничения: отдельно по сумме чётных элементов и отдельно по сумме нечётных. Так как все числа положительные, при расширении окна обе суммы могут только расти. Значит, для фиксированной левой границы $i$ можно двигать правую границу $j$ вправо, пока очередной элемент ещё помещается в свой лимит. Как только перестало помещаться, перестаём двигать правую границу.

Пусть для текущего $i$ мы получили максимальный полуинтервал $[i, j)$. Тогда подходят все его префиксы: $[i, i + 1)$, $[i, i + 2)$, $\ldots$, $[i, j)$. У каждого из них длина от $1$ до $j - i$, и все они автоматически удовлетворяют ограничениям.

Если прибавлять по единице к каждой такой длине отдельно, выйдет слишком медленно. Поэтому используем разностный массив по длинам: для каждой левой границы мы одним действием помечаем весь диапазон подходящих длин, а в конце одним префиксным проходом восстанавливаем итоговые ответы. Именно поэтому алгоритм остаётся линейным: $O(n)$ по времени и $O(n)$ по памяти.

</details>

<details>
<summary>Решение на C++</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем данные:
    int n; int64_t s[2];
    cin >> n >> s[0] >> s[1];
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // храним отдельно суммы чётных и нечётных чисел и реализуем два указателя:
    vector<int> cnt(n+2);
    int64_t sum[2] = {};
    int j = 0;
    for (int i = 0; i < n; i++) {
        // для фиксированного i расширяем правую границу j до упора вправо:
        while (j < n && (a[j] % 2 == 0 ? sum[0] + a[j] <= s[0] : sum[1] + a[j] <= s[1])) {
            if (a[j] % 2 == 0) sum[0] += a[j];
            else sum[1] += a[j];
            j++;
        }
        // получили полуинтервал [i, j). Каждый его префикс подходит.
        if (i <= j) {
            // прибавляем +1 на отрезке [0, j - i], где j - i — длина полуинтервала
            cnt[0]++, cnt[j - i + 1]--;
        }
        // удаляем элемент с индексом i:
        if (a[i] % 2 == 0) sum[0] -= a[i];
        else sum[1] -= a[i];
    }
    // считаем и сразу выводим ответы:
    for (int i = 1; i <= n; i++) {
        cnt[i] += cnt[i-1];
        cout << cnt[i] << ' ';
    }
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
    # читаем данные:
    n, s0, s1 = map(int, input().split())
    a = list(map(int, input().split()))
    # храним отдельно суммы чётных и нечётных чисел и реализуем два указателя:
    cnt = [0] * (n + 2)
    sum0 = 0
    sum1 = 0
    j = 0
    for i in range(n):
        # для фиксированного i расширяем правую границу j до упора вправо:
        while j < n and ((a[j] % 2 == 0 and sum0 + a[j] <= s0) or (a[j] % 2 == 1 and sum1 + a[j] <= s1)):
            if a[j] % 2 == 0:
                sum0 += a[j]
            else:
                sum1 += a[j]
            j += 1
        # получили полуинтервал [i, j). Каждый его префикс подходит.
        if i <= j:
            # прибавляем +1 на отрезке [0, j - i], где j - i — длина полуинтервала
            cnt[0] += 1
            cnt[j - i + 1] -= 1
        # удаляем элемент с индексом i:
        if a[i] % 2 == 0:
            sum0 -= a[i]
        else:
            sum1 -= a[i]
    # считаем и сразу выводим ответы:
    for i in range(1, n + 1):
        cnt[i] += cnt[i - 1]
    print(*cnt[1:n + 1])


tt = int(input())
while tt > 0:
    solve()
    tt -= 1
```

</details>

## D. Почти одинаковые тройки

<details>
<summary>Текстовый разбор</summary>

Сначала отсортируем массив. После сортировки все элементы внутри окна идут по возрастанию, так что минимум всегда стоит слева, а максимум — справа. Значит, условие `max - min <= d` теперь зависит только от крайних элементов окна, и это сразу делает задачу удобной для двух указателей.

Для фиксированной левой границы $i$ двигаем правую границу $j$ как можно дальше, пока разность между крайними значениями не превышает $d$. После этого все элементы с индексами от $i + 1$ до $j - 1$ можно свободно комбинировать с `a[i]`: раз они лежат внутри того же окна, то и тройка вместе с ними тоже удовлетворяет ограничению. Если таких элементов `cnt = j - i - 1`, то к ответу нужно добавить $C_{\text{cnt}}^2$.

Но после сортировки отдельные структуры для минимума и максимума уже не нужны. Минимум текущего окна всегда равен `a[i]`, а самый правый элемент внутри окна и есть текущий максимум. Поэтому достаточно просто двигать правую границу, пока выполняется неравенство `a[j] - a[i] <= d`. После сортировки обе реализации делают один линейный проход, поэтому общая асимптотика определяется именно сортировкой: $O(n \log n)$ по времени и $O(1)$ по дополнительной памяти поверх массива.

</details>

<details>
<summary>Решение на C++</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем данные:
    int n, d;
    cin >> n >> d;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // сортируем вектор:
    sort(a.begin(), a.end());
    // запускаем два указателя
    int j = 0;
    int64_t answ = 0;
    for (int i = 0; i < n; i++) {
        // Двигаем правую границу j, пока выполняется неравенство:
        while (j < n && a[j] - a[i] <= d)
            j++;
        // Считаем количество троек с выбранным a[i]:
        if (int cnt = j - i - 1; cnt > 0)
            answ += cnt * (cnt - 1LL) / 2;
    }
    cout << answ << '\n';
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
    # читаем данные:
    n, d = map(int, input().split())
    a = list(map(int, input().split()))
    # сортируем массив:
    a.sort()
    # запускаем два указателя
    j = 0
    answ = 0
    for i in range(n):
        while j < n and a[j] - a[i] <= d:
            j += 1
        # Считаем количество троек с выбранным a[i]:
        cnt = j - i - 1
        if cnt > 0:
            answ += cnt * (cnt - 1) // 2
    print(answ)


tt = int(input())
while tt > 0:
    solve()
    tt -= 1
```

</details>

<details>
<summary>Разбор решения на C++</summary>

В C++ ключевая идея видна прямо в паре строк

```cpp
while (j < n && a[j] - a[i] <= d)
    j++;
answ += cnt * (cnt - 1LL) / 2;
```

Для фиксированного `i` цикл `while` доводит правую границу до первого элемента, который уже не помещается в окно с левым концом `a[i]`. Значит, все элементы с индексами от `i + 1` до `j - 1` ещё подходят. Их количество равно `cnt = j - i - 1`.

После этого остаётся выбрать любые два таких элемента и добавить их к `a[i]`. Именно поэтому вклад текущего `i` считается формулой `cnt * (cnt - 1) / 2`: это число способов выбрать пару из `cnt` кандидатов.

Отдельно важно, что указатель `j` нигде не двигается назад. После перехода от `i` к `i + 1` условие становится только слабее, потому что минимальный элемент окна увеличивается. Значит, всё, что уже подходило раньше, повторно проверять не нужно. За счёт этого после сортировки весь двухуказательный проход остаётся линейным.

</details>

<details>
<summary>Разбор решения на Python3</summary>

В Python3 опорный фрагмент такой:

```python
while j < n and a[j] - a[i] <= d:
    j += 1

cnt = j - i - 1
if cnt > 0:
    answ += cnt * (cnt - 1) // 2
```

После сортировки для фиксированного индекса `i` нужно просто найти максимально далёкий индекс `j`, для которого ещё верно `a[j] - a[i] <= d`. Пока условие выполняется, указатель `j` расширяет окно вправо.

Когда цикл остановился, элементы с индексами `i + 1, i + 2, \ldots, j - 1` можно брать вместе с `a[i]` в одну тройку: у них тот же минимум `a[i]`, а их значения всё ещё не выходят за предел `d`. Если таких элементов `cnt`, то подходящих троек с минимальным элементом `a[i]` ровно `cnt * (cnt - 1) // 2`.

Проверка `if cnt > 0` здесь просто отсекает случаи, когда справа от `a[i]` не набралось хотя бы двух кандидатов для тройки. Сам указатель `j` за весь алгоритм только растёт, поэтому после сортировки весь проход занимает линейное время поверх массива, а основной вклад в асимптотику даёт именно сортировка.

</details>

## E. Разброс в допустимом диапазоне

<details>
<summary>Текстовый разбор</summary>

Сразу считать подотрезки с условием $L \le \max - \min \le R$ неудобно: у нас одновременно нижняя и верхняя границы накладывают ограничение на одно и то же выражение. Поэтому сначала решим более простую задачу. Обозначим через $F(T)$ количество подотрезков, у которых $\max - \min \le T$. Тогда исходный ответ равен $F(R) - F(L - 1)$.

Осталось быстро считать $F(T)$. Для фиксированной левой границы $i$ будем двигать правую границу $j$ вправо, пока новый элемент не портит условие. Как только разброс стал больше $T$, останавливаемся: при дальнейшем расширении максимум может только вырасти, а минимум — только уменьшиться, значит, лучше уже не станет. Поэтому для этой левой границы подходят все полуинтервалы $[i, i + 1)$, $[i, i + 2)$, $\ldots$, $[i, j)$, и их ровно $j - i$.

Чтобы быстро проверять условие, нужно уметь мгновенно получать минимум и максимум текущего окна. Для этого и используются две монотонные очереди: одна хранит кандидатов на минимум, другая — кандидатов на максимум. Каждый индекс попадает в каждый дек не более одного раза и не более одного раза из него удаляется, поэтому одна функция $F(T)$ считается за $O(n)$.

Ниже приведены два авторских варианта одной и той же идеи. В `E-deque-inplace` работа с деками написана прямо в теле функции. В `E-struct` эта логика вынесена в отдельную структуру очереди. По асимптотике это одно и то же решение, различается только форма записи.

**Важная деталь.** Ограничение времени $0.7$ секунд здесь поставлено специально, чтобы решения через `multiset` не проходили. Нужен именно линейный подход с монотонными деками. Для Python3 здесь важен и ввод-вывод: выгоднее читать поток сразу в виде байтов и печатать ответ через `bytearray`. На серверах Codeforces проходит именно вариант `E-deque-inplace.py`: полное решение, $30$ баллов $(43)$, $625$ мс, $122400$ КБ. Вариант `E-struct.py` полезен как учебный близнец C++-решения, но в Python на Codeforces получает `Time Limit Exceeded`. Ускорить его до полного прохождения в такой форме не получилось.

Асимптотика: $O(n)$ по времени и $O(n)$ по памяти на один набор, а суммарно по всем тестам — $O(\sum n)$.

</details>

<details>
<summary>Решение на C++: E-deque-inplace.cpp</summary>

```cpp
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
int64_t solve(int n, int R, const vector<int> &a) {
// Функция считает, сколько подотрезков [i, j], на которых max - min <= R.
    if (R < 0)
        return 0;
// Минимум и максимум будем хранить в монотонных deque:
    deque<pair<int,int>> minQueue, maxQueue;
    int j = 0;
    int64_t answ = 0;
    for (int i = 0; i < n; i++) {
        // расширяем правую границу отрезка [i, j) до упора вправо:
        while (j < n) {
            // если после добавления нового элемента условие всё ещё выполняется:
            int newMax = maxQueue.empty() ? a[j] : max(maxQueue.front().first, a[j]);
            int newMin = minQueue.empty() ? a[j] : min(minQueue.front().first, a[j]);
            if (newMax - newMin <= R) {
                // добавляем элемент и расширяем отрезок
                // сначала добавляем в очередь на минимум:
                while (!minQueue.empty() && minQueue.back().first > a[j])
                    minQueue.pop_back();
                minQueue.emplace_back(a[j], j);
                // затем в очередь на максимум:
                while (!maxQueue.empty() && maxQueue.back().first < a[j])
                    maxQueue.pop_back();
                maxQueue.emplace_back(a[j], j);
                j++;
            } else
                break;
        }
        // Отрезок [i, j) - максимальный подходящий для этой левой границы
        if (i <= j)
            answ += j - i;
        // Удаляем элемент с индексом i из обоих очередей:
        if (!minQueue.empty() && minQueue.front().second == i)
            minQueue.pop_front();
        if (!maxQueue.empty() && maxQueue.front().second == i)
            maxQueue.pop_front();
    }
    return answ;
}
void solve() {
    // читаем данные:
    int n, L, R;
    cin >> n >> L >> R;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // выводим ответ:
    cout << solve(n, R, a) - solve(n, L-1, a) << '\n';
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
<summary>Решение на Python3: E-deque-inplace.py</summary>

```python
import sys
from collections import deque


# Читаем весь вход сразу в байтовый буфер, чтобы потом разбирать числа указателем.
data = sys.stdin.buffer.read()
data_len = len(data)
data_pos = 0
# Ответы тоже копим в байтовом буфере и печатаем одним вызовом в самом конце.
output = bytearray()


def read_int():
    # Пропускаем пробельные символы и читаем очередное целое число из bytes.
    global data_pos
    while data_pos < data_len and data[data_pos] <= 32:
        data_pos += 1
    sign = 1
    if data[data_pos] == 45:
        sign = -1
        data_pos += 1
    value = 0
    while data_pos < data_len and data[data_pos] > 32:
        value = value * 10 + data[data_pos] - 48
        data_pos += 1
    return sign * value


def write_int(x):
    # Дописываем число в выходной bytearray по цифрам, не создавая промежуточных строк.
    if x == 0:
        output.append(48)
        return
    if x < 0:
        output.append(45)
        x = -x
    digits = []
    while x > 0:
        digits.append(48 + x % 10)
        x //= 10
    while digits:
        output.append(digits.pop())


def write_eoln():
    # Дописываем символ конца строки в выходной буфер.
    output.append(10)


def solve_limit(n, R, a):
    # Функция считает, сколько подотрезков [i, j], на которых max - min <= R.
    if R < 0:
        return 0
    # Минимум и максимум будем хранить в монотонных deque:
    minQueue = deque()
    maxQueue = deque()
    # Копируем самые горячие методы deque в локальные переменные:
    # в tight loop это убирает повторный поиск атрибутов и немного ускоряет Python-код.
    minQueuePop = minQueue.pop
    minQueueAppend = minQueue.append
    minQueuePopleft = minQueue.popleft
    maxQueuePop = maxQueue.pop
    maxQueueAppend = maxQueue.append
    maxQueuePopleft = maxQueue.popleft

    j = 0
    answ = 0
    for i in range(n):
        # расширяем правую границу отрезка [i, j) до упора вправо:
        while j < n:
            current = a[j]
            # если после добавления нового элемента условие всё ещё выполняется:
            newMax = current if not maxQueue else (maxQueue[0][0] if maxQueue[0][0] > current else current)
            newMin = current if not minQueue else (minQueue[0][0] if minQueue[0][0] < current else current)
            if newMax - newMin <= R:
                # добавляем элемент и расширяем отрезок
                # сначала добавляем в очередь на минимум:
                while minQueue and minQueue[-1][0] > current:
                    minQueuePop()
                minQueueAppend((current, j))
                # затем в очередь на максимум:
                while maxQueue and maxQueue[-1][0] < current:
                    maxQueuePop()
                maxQueueAppend((current, j))
                j += 1
            else:
                break
        # Отрезок [i, j) - максимальный подходящий для этой левой границы
        if i <= j:
            answ += j - i
        # Удаляем элемент с индексом i из обоих очередей:
        if minQueue and minQueue[0][1] == i:
            minQueuePopleft()
        if maxQueue and maxQueue[0][1] == i:
            maxQueuePopleft()
    return answ


def solve():
    # читаем данные:
    n = read_int()
    L = read_int()
    R = read_int()
    # читаем массив:
    a = [0] * n
    for i in range(n):
        a[i] = read_int()
    # выводим ответ:
    write_int(solve_limit(n, R, a) - solve_limit(n, L - 1, a))
    write_eoln()


tt = read_int()
while tt > 0:
    solve()
    tt -= 1

# Печатаем весь накопленный ответ одним вызовом.
sys.stdout.buffer.write(output)
```

</details>

<details>
<summary>Разбор решения на C++: E-deque-inplace.cpp</summary>

Ключевой фрагмент здесь — поддержка двух деков. Для минимума мы хотим хранить значения по неубыванию, поэтому перед добавлением нового `a[j]` выбрасываем с конца все большие элементы:

```cpp
while (!minQueue.empty() && minQueue.back().first > a[j])
    minQueue.pop_back();
minQueue.emplace_back(a[j], j);
```

После этого в начале `minQueue` всегда стоит настоящий минимум окна. Для `maxQueue` делается симметричное действие: выбрасываются все меньшие элементы, и в начале остаётся максимум. Когда левая граница уходит вправо, мы удаляем индекс `i` из начала дека только в том случае, если он действительно там стоит. Благодаря этому каждый элемент заходит и выходит из каждого дека не более одного раза.

</details>

<details>
<summary>Разбор решения на Python3: E-deque-inplace.py</summary>

В Python3 важны две независимые идеи. Первая — сама линейная логика `solve_limit()`, которая почти построчно повторяет решение на C++ с двумя монотонными деками `minQueue` и `maxQueue`. Внутри них лежат пары `(значение, индекс)`, а перед реальным добавлением нового `a[j]` мы заранее считаем `newMax` и `newMin`. Вторая идея — максимально дешёвый ввод-вывод. Функция `read_int()` читает поток сразу как `bytes`, а затем указателем разбирает числа по их ASCII-кодам. Это быстрее, чем сначала делать `decode()`, а потом много раз вызывать `int(...)` на строках.

Ещё одна важная мелочь — строки вида `minQueuePop = minQueue.pop` и `maxQueueAppend = maxQueue.append`. Это не изменение алгоритма, а чисто Python-оптимизация: внутри горячего цикла меньше повторных поисков атрибутов объектов. Вывод устроен симметрично: `write_int()` сразу дописывает цифры в `bytearray`, а в конце весь буфер печатается одним вызовом `sys.stdout.buffer.write(output)`. Именно эта версия проходит на Codeforces на полный балл: $30$ баллов $(43)$, $625$ мс, $122400$ КБ, и отправлять её нужно под компилятор `Python 3`, а не `PyPy3-64`.

</details>

<details>
<summary>Решение на C++: E-struct.cpp</summary>

```cpp
#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// Очередь на минимум через монотонный deque. Для удобства реализуем в виде структуры.
template<typename T, typename Compare = std::less<T>>
struct MinQueue {
    // Данные храним как пары (значение, индекс)
    deque<pair<T, int>> data;
    // Добавление в конец (a[i], i):
    void push_back(T x, int i) {
        // сначала выталкиваем все >= элементы с конца:
        while (!data.empty() && Compare()(x, data.back().first))
            data.pop_back();
        // только теперь добавляем
        data.emplace_back(x, i);
    }
    // Удаление из начала очереди:
    void pop_front(int i) {
        // удаляем все элементы, у которых индекс <= i
        while (!data.empty() && data.front().second <= i)
            data.pop_front();
    }
    // Текущий минимум в окне:
    T getMin() const {
        assert(!data.empty());
        return data.front().first; // элемент в начале очереди и будет минимумом
    }
    // Какой будет минимум после добавления элемента x?
    T minAfterAdd(T x) const {
        return data.empty() ? x : min(x, getMin(), Compare());
    }

};

int64_t solve(int n, int R, const vector<int> &a) {
// Функция считает, сколько подотрезков [i, j], на которых max - min <= R.
    if (R < 0)
        return 0;
// Минимум и максимум будем хранить в монотонных deque:
    MinQueue<int> minQueue;
    MinQueue<int, greater<int>> maxQueue;
    
    int j = 0;
    int64_t answ = 0;
    for (int i = 0; i < n; i++) {
        // расширяем правую границу отрезка [i, j) до упора вправо:
        while (j < n) {
            // если после добавления нового элемента условие всё ещё выполняется:
            int newMax = maxQueue.minAfterAdd(a[j]);
            int newMin = minQueue.minAfterAdd(a[j]);
            if (newMax - newMin <= R) {
                // добавляем элемент и расширяем отрезок:
                minQueue.push_back(a[j], j);
                maxQueue.push_back(a[j], j);
                j++;
            } else
                break;
        }
        // Отрезок [i, j) - максимальный подходящий для этой левой границы
        if (i <= j)
            answ += j - i;
        // Удаляем элемент с индексом i:
        minQueue.pop_front(i);
        maxQueue.pop_front(i);
    }
    return answ;
}
void solve() {
    // читаем данные:
    int n, L, R;
    cin >> n >> L >> R;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // выводим ответ:
    cout << solve(n, R, a) - solve(n, L-1, a) << '\n';
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
<summary>Решение на Python3: E-struct.py</summary>

```python
import sys


# Эта версия полезна как учебный близнец C++-решения с отдельным классом,
# но на серверах Codeforces в Python получает Time Limit Exceeded.
# Ускорить её до полного прохождения в такой форме не получилось.

# Читаем весь вход сразу в байтовый буфер, чтобы потом разбирать числа указателем.
data = sys.stdin.buffer.read()
data_len = len(data)
data_pos = 0
# Ответы тоже копим в байтовом буфере и печатаем одним вызовом в самом конце.
output = bytearray()


def read_int():
    # Пропускаем пробельные символы и читаем очередное целое число из bytes.
    global data_pos
    while data_pos < data_len and data[data_pos] <= 32:
        data_pos += 1
    sign = 1
    if data[data_pos] == 45:
        sign = -1
        data_pos += 1
    value = 0
    while data_pos < data_len and data[data_pos] > 32:
        value = value * 10 + data[data_pos] - 48
        data_pos += 1
    return sign * value


def write_int(x):
    # Дописываем число в выходной bytearray по цифрам, не создавая промежуточных строк.
    if x == 0:
        output.append(48)
        return
    if x < 0:
        output.append(45)
        x = -x
    digits = []
    while x > 0:
        digits.append(48 + x % 10)
        x //= 10
    while digits:
        output.append(digits.pop())


def write_eoln():
    # Дописываем символ конца строки в выходной буфер.
    output.append(10)


# Очередь на минимум через монотонный deque. Для удобства реализуем в виде структуры.
class MinQueue:
    # Логически данные храним как пары (значение, индекс).
    # В Python быстрее держать эти две компоненты в параллельных массивах.
    __slots__ = ("dataValue", "dataIndex", "head", "wantMinimum")

    def __init__(self, wantMinimum):
        self.dataValue = []
        self.dataIndex = []
        self.head = 0
        self.wantMinimum = wantMinimum

    # Добавление в конец (a[i], i):
    def push_back(self, x, i):
        dataValue = self.dataValue
        dataIndex = self.dataIndex
        head = self.head
        if self.wantMinimum:
            # сначала выталкиваем все >= элементы с конца:
            while len(dataValue) > head and dataValue[-1] > x:
                dataValue.pop()
                dataIndex.pop()
        else:
            # для очереди на максимум выталкиваем все <= элементы с конца:
            while len(dataValue) > head and dataValue[-1] < x:
                dataValue.pop()
                dataIndex.pop()
        # только теперь добавляем
        dataValue.append(x)
        dataIndex.append(i)

    # Удаление из начала очереди:
    def pop_front(self, i):
        # удаляем все элементы, у которых индекс <= i
        dataIndex = self.dataIndex
        head = self.head
        size = len(dataIndex)
        while head < size and dataIndex[head] <= i:
            head += 1
        if head == size:
            self.dataValue.clear()
            self.dataIndex.clear()
            self.head = 0
        else:
            self.head = head

    # Текущий минимум в окне:
    def getMin(self):
        return self.dataValue[self.head]  # элемент в начале очереди и будет минимумом

    # Какой будет минимум после добавления элемента x?
    def minAfterAdd(self, x):
        if self.head == len(self.dataValue):
            return x
        current = self.dataValue[self.head]
        if self.wantMinimum:
            return x if x < current else current
        return x if x > current else current


def solve_limit(n, R, a):
    # Функция считает, сколько подотрезков [i, j], на которых max - min <= R.
    if R < 0:
        return 0
    # Минимум и максимум будем хранить в монотонных deque:
    minQueue = MinQueue(True)
    maxQueue = MinQueue(False)
    # Копируем методы структуры в локальные переменные:
    # в горячем цикле так меньше обращений к атрибутам объектов, что немного ускоряет Python.
    minAfterAdd = minQueue.minAfterAdd
    maxAfterAdd = maxQueue.minAfterAdd
    pushMin = minQueue.push_back
    pushMax = maxQueue.push_back
    popMin = minQueue.pop_front
    popMax = maxQueue.pop_front

    j = 0
    answ = 0
    for i in range(n):
        # расширяем правую границу отрезка [i, j) до упора вправо:
        while j < n:
            current = a[j]
            # если после добавления нового элемента условие всё ещё выполняется:
            newMax = maxAfterAdd(current)
            newMin = minAfterAdd(current)
            if newMax - newMin <= R:
                # добавляем элемент и расширяем отрезок:
                pushMin(current, j)
                pushMax(current, j)
                j += 1
            else:
                break
        # Отрезок [i, j) - максимальный подходящий для этой левой границы
        if i <= j:
            answ += j - i
        # Удаляем элемент с индексом i:
        popMin(i)
        popMax(i)
    return answ


def solve():
    # читаем данные:
    n = read_int()
    L = read_int()
    R = read_int()
    # читаем массив:
    a = [0] * n
    for i in range(n):
        a[i] = read_int()
    # выводим ответ:
    write_int(solve_limit(n, R, a) - solve_limit(n, L - 1, a))
    write_eoln()


tt = read_int()
while tt > 0:
    solve()
    tt -= 1

# Печатаем весь накопленный ответ одним вызовом.
sys.stdout.buffer.write(output)
```

</details>

<details>
<summary>Разбор решения на C++: E-struct.cpp</summary>

Главная идея этого варианта — вынести монотонную очередь в отдельную структуру `MinQueue`. Тогда в основном цикле почти не остаётся технических деталей: код спрашивает, что будет с минимумом и максимумом после добавления нового элемента, а затем вызывает `push_back()` и `pop_front()`. Это делает двухуказательный каркас очень коротким.

Особенно полезен метод

```cpp
T minAfterAdd(T x) const {
    return data.empty() ? x : min(x, getMin(), Compare());
}
```

Он позволяет заранее понять, каким станет экстремум после добавления `x`, ещё до реального изменения структуры. Благодаря этому проверка условия `newMax - newMin <= R` выглядит в основном цикле почти так же, как математическая формула из разбора.

</details>

<details>
<summary>Разбор решения на Python3: E-struct.py</summary>

В Python3 этот вариант повторяет интерфейс C++ почти дословно: есть структура `MinQueue` и те же методы `push_back`, `pop_front`, `getMin`, `minAfterAdd`. Поэтому в основном цикле остаётся та же короткая схема, что и в `E-struct.cpp`: заранее посчитать `newMax` и `newMin`, затем вызвать `push_back`, а после сдвига левой границы — `pop_front`.

Здесь тоже используются все обычные Python-оптимизации для этого лимита: быстрый ввод-вывод на `bytes` и `bytearray`, хранение значений и индексов в двух параллельных массивах внутри `MinQueue`, а также копирование часто вызываемых методов структуры в локальные переменные перед горячим циклом. Но даже этого не хватает: на Codeforces такой вариант с классом в Python получает `Time Limit Exceeded`. То есть как учебный близнец C++-решения он полезен, но как реальная посылка под этот лимит времени — нет; сделать его достаточно быстрым в такой форме не получилось.

</details>
