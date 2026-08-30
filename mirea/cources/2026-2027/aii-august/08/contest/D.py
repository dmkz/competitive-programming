from math import gcd
from collections import defaultdict
def solve():
    # читаем данные:
    n = int(input())
    x, y = [0] * n, [0] * n
    for i in range(n):
        x[i], y[i] = map(int, input().split())
    # будем вычитать из всех троек те тройки, которые не образуют треугольник
    # такие тройки лежат на одной прямой. переберём одну из точек треугольника
    # и посчитаем, сколько плохих троек она образует:
    answ = 0
    for i in range(n):
        cnt = defaultdict(int)
        for j in range(n):
            if j != i:
                # вектор (xi, yi) -> (xj, yj):
                dx = x[j] - x[i]
                dy = y[j] - y[i]
                # нормализуем длину:
                g = gcd(abs(dx), abs(dy))
                dx //= g; dy //= g
                # нормализуем знак:
                if dx < 0: dx = -dx; dy = -dy
                if dx == 0: dy = abs(dy)
                # добавляем в словарь:
                cnt[(dx, dy)] += 1
        # теперь из всех способов выбрать 2 точки вычитаем те, которые лежат на одной прямой:
        curr = (n-1)*(n-2)//2
        for _, k in cnt.items():
            curr -= k * (k-1)//2
        # обновляем глобальный ответ:
        answ += curr
    # выводим ответ, учитывая, что каждый треугольник посчитали трижды:
    assert answ % 3 == 0
    print(answ // 3)
tt = int(input())
for _ in range(tt):
    solve()