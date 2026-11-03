from bisect import bisect_left
# решение задачи:
def solve():
    n, k = map(int, input().split())
    # найдём период. для этого храним пары (позиция, шаг % n). они задают последовательность переходов
    # при попытке хранить пары в set получил Time Limit Exceeded.
    # поэтому храним список отсортированных списков.
    cache = [[] for _ in range(n)]
    pos, i, period = 0, 1, -1
    while i <= k:
        # делаем переход:
        pos = (pos + i) % n
        # мы уже были тут? смотрим сохранённые шаги и обновляем их
        it = bisect_left(cache[pos], i % n)
        if it != len(cache[pos]) and cache[pos][it] == i % n:
            period = i-1
            break
        cache[pos].insert(it, i % n)
        i += 1
    # нашли период, теперь эмулируем заново, но из k вычитаем чётное число периодов
    if period != -1 and k >= 2 * period:
        k -= k // (2 * period) * 2 * period
    a = [False] * n
    pos, i = 0, 1
    while i <= k:
        pos = (pos + i) % n
        a[pos] ^= True
        i += 1
    # считаем и выводим ответ:
    answ = 0
    for i in range(n):
        answ += a[i]
    print(answ)
tt = int(input())
while tt > 0:
    tt -= 1
    solve()