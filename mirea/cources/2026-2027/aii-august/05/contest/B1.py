# Время: 93 мс, Память: 1440 КБ
from math import gcd
def solve():
    # читаем данные:
    n, m = map(int, input().split())
    # находим их НОД: он содержит все общие простые делители
    g = gcd(n, m)
    # раскладываем их НОД на простые множители:
    p = []
    i = 2
    while i * i <= g:
        if g % i == 0:
            p.append(i)
            while g % i == 0:
                g //= i
        i += 1
    if g > 1:
        p.append(g)
    # сокращаем числа n и m на их общие простые:
    for pi in p:
        while n % pi == 0:
            n //= pi
        while m % pi == 0:
            m //= pi
    # выводим ответ (через пробел, чтобы проверить, принимает ли Codeforces такой формат):
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