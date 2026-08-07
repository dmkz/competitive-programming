from bisect import bisect_right
# Храним все возможные расходы, не превосходящие ограничение на n.
sums = [0]
k = 1
while sums[-1] + k * k <= 10 ** 18:
    sums.append(sums[-1] + k * k)
    k += 1
# Отвечаем на запрос последним расходом, не превосходящим n.
n = int(input())
print(bisect_right(sums, n) - 1)