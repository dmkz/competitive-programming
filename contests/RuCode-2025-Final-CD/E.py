# Задача: E, Вердикт: OK, Время: 0.068 сек, Память: 105 MB

# EF должно быть делителем числа n (по условию задачи). Найдём все делители
# числа n и проверим каждый из них. При проверке мы знаем, что EF = 14 * base + 15,
# поэтому мы должны найти base. Зафиксировав делитель, base находится однозначно.

# факторизация числа n за время O(sqrt(n))
def factor(n: int):
    # переберём делители до корня из n. В список lowerHalf запишем делители
    # меньше корня, а в upperHalf — больше корня
    lowerHalf, upperHalf = [], []
    x = 1
    while x * x <= n:
        if n % x == 0:
            y = n // x
            lowerHalf.append(x)
            if y != x:
                upperHalf.append(y)
        x += 1
    # объединяя обе половины, получаем полный список делителей в возрастающем порядке
    while upperHalf:
        lowerHalf.append(upperHalf.pop())
    return lowerHalf

def main():
    import sys
    n = int(sys.stdin.readline())
    INF = 10**30
    minBase = INF
    # переберём делители числа
    for x in factor(n):
        # Число EF = 14 * base + 15. Нужно найти base.
        # Предположим, что EF = x (текущему делителю), тогда выразим base:
        # x = 14 * base + 15
        # (x - 15) // 14 = base
        base = (x - 15) // 14
        # проверка что наше решение подошло:
        if base >= 16 and 14 * base + 15 == x:
            # обновляем лучший ответ:
            if base < minBase:
                minBase = base
    # выводим ответ, корректно обрабатывая случай с -1:
    if minBase >= INF:
        minBase = -1
    print(minBase)

if __name__ == "__main__":
    main()
