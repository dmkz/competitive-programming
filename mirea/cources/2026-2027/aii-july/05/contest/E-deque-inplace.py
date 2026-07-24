# Искомое количество подотрезков массива с L <= max(a[i..j]) - min(a[i..j]) <= R обозначим
# как f(L, R). Тогда верно следующее: f(L, R) = f(0, R) - f(0, L-1) = f(R) - f(L-1). Поэтому
# будем считать сразу f(R): количество подотрезков с max(a[i..j]) - min(a[i..j]) <= R.
# Если мы зафиксируем левую границу отрезка, то справедлива монотонность:
# 1. min(a[i..j]) >= min(a[i..j+1]) <-- минимум при расширении вправо только уменьшается;
# 2. max(a[i..j]) <= max(a[i..j+1]) <-- максимум при расширении вправо лишь увеличивается.
# Поэтому мы поддерживаем в текущем окне два монотонных дека: для минимума и для максимума.
# Реализуем добавление в конец, удаление из начала, а также получение значения min/max.
# После этого мы используем метод двух указателей, чтобы посчитать количество отрезков
# для фиксированной левой границы i.

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
