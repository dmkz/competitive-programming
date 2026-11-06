# факторизация на простые сомножители:
def factor(m):
    answ = []
    x = 2
    while x * x <= m:
        if m % x == 0:
            p = 1
            m //= x
            while m % x == 0: m //= x; p += 1
            answ.append((x, p))
        x += 1
    if m > 1: answ.append((m, 1))
    return answ
# сколько раз n! делится на p:
def getPowInFact(n, p):
    return 0 if n < p else n // p + getPowInFact(n // p, p)
# решение задачи:
def solve():
    # читаем данные:
    l, m = map(int, input().split())
    # раскладываем m на простые множители:
    divs = factor(m)
    # функция проверки, подходит ли граница r?
    def check(r):
        # проверить, что произведение чисел l, l+1, ..., r делится на m
        # это отношение двух факториалов fact(r) / fact(l-1)
        # нужно посчитать, сколько раз каждый из факториалов делится на простое число p
        for p, k in divs:
            t = getPowInFact(r, p) - getPowInFact(l-1, p)
            if t < k: return False
        return True
    # находим первое подходящее r бинарным поиском на отрезке [l, l+m+1):
    low, high = l-1, l+m
    while high - low > 1:
        mid = (low + high) // 2
        if check(mid): high = mid
        else: low = mid
    print(high)
tt = int(input())
while tt > 0:
    solve()
    tt -= 1