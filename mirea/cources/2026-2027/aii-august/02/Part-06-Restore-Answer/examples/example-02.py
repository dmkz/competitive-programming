# Читаем последовательность:
n = int(input())
a = list(map(int, input().split()))
# dp[i] хранит длину LIS, которая заканчивается в позиции i.
dp = [1] * n
parent = [-1] * n
finish = 0
for i in range(n):
    # Выбираем предпоследний элемент, который даёт максимальную длину.
    for j in range(i):
        if a[j] < a[i] and dp[j] + 1 > dp[i]:
            dp[i] = dp[j] + 1
            parent[i] = j
    # Запоминаем конец лучшей подпоследовательности среди уже обработанных.
    if dp[i] > dp[finish]: finish = i
# Идём по предкам от конца и разворачиваем выбранную подпоследовательность.
sequence = []
i = finish
while i != -1:
    sequence.append(a[i])
    i = parent[i]
sequence.reverse()
# Выводим длину и значения одной наибольшей подпоследовательности:
print(len(sequence))
print(*sequence)