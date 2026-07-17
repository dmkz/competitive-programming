# Пример: один и тот же шаблон push_back для префиксов и суффиксов.
# Ввод: n и массив.
# Вывод: сначала префиксные суммы, потом суффиксные суммы по длине.

n = int(input())
a = list(map(int, input().split()))

pref = [0]
for value in a:
    pref.append(pref[-1] + value)

suff_len = [0]
for i in range(n - 1, -1, -1):
    suff_len.append(suff_len[-1] + a[i])

print(*pref)
print(*suff_len)