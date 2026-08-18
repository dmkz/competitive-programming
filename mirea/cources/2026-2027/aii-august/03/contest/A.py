inf = 1 << 60
def solve():
    # читаем входные данные:
    n, q = map(int, input().split())
    w = list(map(int, input().split()))
    v = list(map(int, input().split()))
    x = list(map(int, input().split()))
    # считаем максимальную сумму:
    S = max(x)
    # строим два рюкзака:
    # dpMin[n][s] = минимальный суммарный вес для набора стоимостью s
    # dpMax[n][s] = максимальный суммарный вес для набора стоимостью s
    dpMin = [[inf] * (S + 1) for _ in range(n + 1)]
    dpMax = [[-inf] * (S + 1) for _ in range(n + 1)]
    # инициализация:
    dpMin[0][0] = 0
    dpMax[0][0] = 0
    # считаем переходы:
    for i in range(n):
        # копируем предыдущий слой - здесь мы не берём i-й предмет:
        dpMin[i + 1] = dpMin[i].copy()
        dpMax[i + 1] = dpMax[i].copy()
        # обновляем варианты, если i-й предмет выбран:
        for s in range(v[i], S + 1):
            # Сейчас стоимость s, взяли предмет (v[i], w[i]), значит до этого
            # стоимость была s - v[i], и нам нужен мин и макс вес для предыдущего рюкзака
            dpMin[i + 1][s] = min(dpMin[i + 1][s], w[i] + dpMin[i][s - v[i]])
            dpMax[i + 1][s] = max(dpMax[i + 1][s], w[i] + dpMax[i][s - v[i]])
    # отвечаем на запросы:
    for i in range(q):
        if dpMin[n][x[i]] >= inf:
            print(-1)
        else:
            print(dpMin[n][x[i]], dpMax[n][x[i]])

tt = int(input())
while tt > 0:
    solve()
    tt -= 1