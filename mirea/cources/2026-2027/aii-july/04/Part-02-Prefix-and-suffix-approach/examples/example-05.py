# Пример: удалить один элемент так, чтобы НОД оставшихся был максимальным.
# Ввод: n и массив чисел.
# Вывод: максимальный возможный НОД после удаления ровно одного элемента.

from math import gcd

n = int(input())
a = [0] + list(map(int, input().split()))

# Работаем в 1-индексации и добавляем нули по краям,
# чтобы одна и та же формула подходила для всех i.
pref = [0] * (n + 2)
suff = [0] * (n + 2)
for i in range(1, n + 1):
    pref[i] = gcd(pref[i - 1], a[i])
for i in range(n, 0, -1):
    suff[i] = gcd(a[i], suff[i + 1])

answer = 0
for i in range(1, n + 1):
    answer = max(answer, gcd(pref[i - 1], suff[i + 1]))

print(answer)
