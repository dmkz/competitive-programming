# Время: 187 мс, Память: 5936 КБ
from math import gcd
def solve():
    # читаем данные:
    n, m = map(int, input().split())
    # находим их НОД: он содержит все общие простые делители
    g = gcd(n, m)
    # рассмотрим НОД как пересечение множества делителей. Сокращаем наши числа так:
    # пока пересечение простых делителей не пусто, делим на это пересечение
    # таким образом, факторизация здесь не нужна
    while True:
        common = gcd(n, g)
        if common <= 1:
            break
        n //= common
    while True:
        common = gcd(m, g)
        if common <= 1:
            break
        m //= common
    # выводим ответ (через пробел, потому что так тоже можно):
    if n > m:
        print("Nikita", end=" ")
    elif n < m:
        print("Misha", end=" ")
    else:
        print("Friendship", end=" ")
tt = int(input())
while tt > 0:
    solve()
    tt -= 1