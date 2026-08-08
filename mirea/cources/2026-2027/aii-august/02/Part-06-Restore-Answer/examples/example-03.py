from bisect import bisect_left
# Читаем последовательность:
n = int(input())
a = list(map(int, input().split()))
# dp[k] хранит минимальное окончание длины k, last[k] — его индекс.
inf = 10 ** 30
dp = [-inf] + [inf] * n
last = [-1] * (n + 1)
parent = [-1] * n
answ = 0
for i in range(n):
    # Находим длину, для которой a[i] станет новым минимальным окончанием.
    pos = bisect_left(dp, a[i], 1)
    # Старый конец предыдущей длины становится предшественником a[i].
    parent[i] = last[pos - 1]
    dp[pos] = a[i]
    last[pos] = i
    answ = max(answ, pos)
# Идём по предкам от конца максимальной длины и разворачиваем ответ.
sequence = []
i = last[answ]
while i != -1:
    sequence.append(a[i])
    i = parent[i]
sequence.reverse()
# Выводим длину и значения одной наибольшей подпоследовательности:
print(len(sequence))
print(*sequence)