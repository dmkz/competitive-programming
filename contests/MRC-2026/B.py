from math import isqrt
n = int(input())
if n == 1: print(1)
elif n == 3:
    # прямая линия XXX и полуквадрат вида XX
    #                                     X.
    print(2)
else:
    # прямая линия или квадрат
    root = isqrt(n)
    print(1 + (root * root == n))