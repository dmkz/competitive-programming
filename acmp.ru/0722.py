# -*- coding: utf-8 -*-
# Задача: 722. Шоколадки
# Решение: динамическое программирование, исследование, длинная арифметика, O(n+m)
# Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru

cnt = [[1] * 2 + [0] * 999 for x in range(2)] #[last][len] -> numbre of sequences
for len in range(2, 1001):
    cnt[0][len] = cnt[1][len-1] + cnt[1][len-2];
    cnt[1][len] = cnt[0][len-1] + cnt[0][len-2];

r, c = (int(x) for x in input().split())
res = cnt[0][r] + cnt[1][r]
for i in range(1, min(c,3)): res += 2;
prev = 2; curr = 2;
for i in range(3,c):
    next = curr + prev;
    prev = curr;
    curr = next;
    res += curr;
print(res)