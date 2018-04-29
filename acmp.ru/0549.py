# -*- coding: utf-8 -*-
import os, sys
from fractions import *

# Функция, решающая задачу:
def solve(p, q):
    count = 1
    fact = 1
    rem = Fraction(p, q)
    answ = []
    while rem != 0:
        count += 1
        fact *= count
        num = rem.numerator * fact // rem.denominator
        rem = rem - Fraction(num, fact)
        answ.append(num)
    return answ

# Чтение p и q:
s_in = sys.stdin.read()
p, q = (int(x) for x in s_in.split())

# Получение ответа:
answ = solve(p, q)

# Формирование строки вывода:
s_out = str(len(answ)+1) + "\n";
for it in answ: 
    s_out = s_out + str(it) + "\n";

# Вывод:
os.write(1, s_out.encode())