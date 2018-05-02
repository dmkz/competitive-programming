# -*- coding: utf-8 -*-
nSweets, nPeople, xMax, maxCount = (int(x) for x in input().split())
answ = 0
for curr in range(1, maxCount+1):
    # Нужно найти максимальный x для текущего значения curr
    # (curr - 1) * nPeople * x + x <= nSweets;
    x = min(xMax, nSweets // ((curr - 1) * nPeople + 1))
    answ = max(answ, x * curr)
print(answ)