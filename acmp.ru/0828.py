# -*- coding: utf-8 -*-
# Задача: 828. Красивые последовательности
# Решение: длинная арифметика, динамическое программирование, двумерное дп, O(n^2)
# Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
n,k=(int(x) for x in input().split())
count = [0] * ((n+1) * (k+3))
count[1*(k+2)+1] = 1;
for len in range(1,n):
    for mx in range(1,k+1):
        count[(len+1)*(k+2)+mx] += mx * count[len*(k+2)+mx];
        count[(len+1)*(k+2)+mx+1] += count[len*(k+2)+mx];
res = 0;
for mx in range(1,k+1):
    res += count[n*(k+2)+mx]
print(res)