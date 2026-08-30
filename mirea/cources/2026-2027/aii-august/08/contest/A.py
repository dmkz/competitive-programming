from math import gcd, lcm
def solve():
    # читаем данные:
    g, l = map(int, input().split())
    # перебираем все подходящие значения a, проверяя каждое:
    answ = []
    for a in range(1, 1_000_001):
        if a % g == 0 and l % a == 0:
            b = g * l // a # используем a * b = НОК * НОД
            if b <= 1_000_000 and gcd(a, b) == g and lcm(a, b) == l:
                answ.append((a, b))
    # выводим ответ:
    print(len(answ))
    for a, b in answ:
        print(a, b)
tt = int(input())
for _ in range(tt):
    solve()