# -*- coding: utf-8 -*-
import os, sys

from fractions import *

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

input_data = os.read(0, 100*1000*1000)
p, q = (int(x) for x in input_data.split())

answ = solve(p, q)

results = [str.encode(str(len(answ)+1))]
results = (str.encode(str(x)) for x in answ)
os.write(1, "".join(results))