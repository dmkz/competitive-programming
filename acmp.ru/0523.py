# -*- coding: utf-8 -*-
# Читаем входные данные:
n = int(input())
a = [int(x) for x in input().split()]
k = int(input())

# Сколько томов получится, если ограничение на максимальный том равно x?
def count(x):
    # Если максимальный размер одной главы больше x - все плохо
    if max(a) > x: return len(a)+1
    # Иначе жадно формируем главы в тома:
    c, s = 0, 0;
    for cur in a:
        if s + cur <= x:
            s += cur
        else:
            c += 1
            s = cur
    return c + 1 

# Бинарный поиск по ответу: нельзя издать так, чтобы макс. том <= low, но можно <= high
low, high = 0, sum(a)
while high - low > 1:
    mid = (low + high) // 2
    if count(mid) <= k:
        high = mid
    else: 
        low = mid

# Выводим ответ:
print(high)