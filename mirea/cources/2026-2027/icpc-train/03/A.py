inf = 10**9+7
def flip(s, i, j):
    s[i] = chr(ord('T')-ord(s[i])+ord('H'))
    s[j] = chr(ord('T')-ord(s[j])+ord('H'))
def solve(s=None, fi=None, se=None):
    if s is not None:
        s = list(s)
        n = len(s)
        flip(s, fi, se)
        answ = 1
        i = se
        while i != fi:
            if s[i] == 'T': flip(s, i, (i+1)%n); answ += 1
            i = (i+1)%n
        return answ if s == ['H']*n else inf
    # читаем входные данные
    s = input()
    n = len(s)
    # находим символ i, который мы должны будем поменять. Либо мы меняем пару (i-1, i).
    # Либо меняем пару (i, i+1). Рассматриваем оба варианта, считаем ответ для каждого, и выводим минимум
    answ = 0
    for i in range(n):
        if s[i] == 'T':
            fi = solve(s, i, (i+1)%n)
            se = solve(s, (i-1+n)%n, i)
            answ = min(fi, se)
            break
    if answ >= inf: answ = -1
    print(answ)
tt = int(input())
for _ in range(tt): solve()