# Задача: F, Вердикт: OK, Время: 0.118 сек, Память: 109 МБ
#
# Идея: используем теорему Пифагора и свойство делимости периметра из условия,
# чтобы для заданного a сказать, сколько уникальных прямоугольных треугольников
# существует. Из теоремы Пифагора:
# a^2 + b^2 = c^2 => a^2 = c^2 - b^2 = (c-b)*(c+b)
# получаем: a^2 = (c-b)*(c+b). Обозначим как (*)
# по условию задачи: a+b+c делится на один из катетов. Значит:
# случай 1) a+b+c делится на a;
# случай 2) a+b+c делится на b.
# Распишем каждый случай отдельно.
# Случай 1) a+b+c делится на a => b+c делится на a => b+c = k * a, k >= 1
# подставим в (*), получаем: a^2 = (c - b) * k * a => a = (c - b) * k
# получили что, (c-b) и k — парные делители числа a.
# Случай 2) a+b+c делится на b. Проблема в том, что мы не знаем b, мы знаем
# только a. Давайте выразим b через a.
# Итак, из делимости периметра на b: (a + c) = k * b
# Из теоремы Пифагора: b^2 = (c - a) * (c + a) => b = (c - a) * k
# Надо избавиться от c: c = k * b - a => b = (k * b - 2 * a) * k
# Упрощаем: b = k^2 * b - 2*k*a
# Получаем: b = (2 * k / (k^2 - 1)) * a
# Идея: НОД(2 * k, (k^2 - 1)) равен либо 1, либо 2. Тогда, после сокращения
# на НОД, знаменатель — делитель a. Снова перебираем парные делители и находим все
# возможные ответы, сортируем и удаляем повторы.
# Объединяя решения для случаев (1) и (2), получаем все возможные треугольники.
#
# Примечания для Python:
# - В Python целые числа произвольной точности, отдельной __int128 не требуется.
# - Стандартный ввод/вывод: input() / print().

import math

def idiv(a: int, b: int) -> int:
    # Целочисленное деление с усечением к нулю (как в C/C++), при b > 0.
    return a // b # if a >= 0 else -((-a) // b)

def factor(n: int):
    # Возвращает все делители n по возрастанию
    lower = []
    upper = []
    x = 1
    while x * x <= n:
        y = n // x
        if x * y == n:
            lower.append(x)
            if x != y:
                upper.append(y)
        x += 1
    while upper:
        lower.append(upper.pop())
    return lower

def solve(a: int) -> int:
    divs = factor(a)
    answer = []

    def check_and_update(b: int, c: int):
        if b >= 1 and c >= 1 and c * c == b * b + a * a:
            answer.append([a, b, c])

    # Случай (1)
    for k in divs:
        q = a // k
        c = (k * a + q) // 2
        b = c - q
        check_and_update(b, c)

    # Случай (2)
    for d in divs:
        # Нечётные k: k = 2t - 1
        D = 4 + 8 * d
        s = int(math.floor(math.sqrt(D)))
        t1 = (2 + s) // 4
        t2 = (2 - s) // 4
        for t in (t1, t2):
            k = 2 * t - 1
            b = (k * a) // d
            c = k * b - a
            check_and_update(b, c)

        # Чётные k: k = 2t, где t = sqrt((d+1)/4)
        t = int(math.floor(math.sqrt((d + 1) // 4)))
        k = 2 * t
        b = (2 * k * a) // d
        c = k * b - a
        check_and_update(b, c)

    # Сортировка и удаление повторов
    for triple in answer:
        x, y, z = triple
        if x > y:
            x, y = y, x
        triple[0], triple[1], triple[2] = x, y, z

    answer.sort()
    uniq = []
    prev = None
    for t in answer:
        tup = tuple(t)
        if tup != prev:
            uniq.append(tup)
            prev = tup

    return len(uniq)

def main():
    a = int(input().strip())
    print(solve(a))

if __name__ == "__main__":
    main()
