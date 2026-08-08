def best(i):
    if i == n: return 0
    answ = -(10 ** 30)
    # Перебираем все следующие прыжки без запоминания ответов.
    for jump in (1, 2):
        if i + jump <= n:
            answ = max(answ, a[i + jump] + best(i + jump))
    return answ
# Читаем награды ступеней:
n = int(input())
a = [0] + list(map(int, input().split()))
print(best(0))