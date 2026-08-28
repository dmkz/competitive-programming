import math
def solve():
    # читаем данные:
    n = int(input())
    x = list(map(int, input().split()))
    y = list(map(int, input().split()))
    # переберём точку, в которую встанем: для неё ответом является количество уникальных
    # направляющих векторов из неё до других точек множества.
    inf = 10**9
    answ = (inf, -1)
    for i in range(n):
        vectors = set()
        for j in range(n):
            if i != j:
                # вектор из точки (x[i], y[i]) в точку (x[j], y[j]):
                dx, dy = x[j] - x[i], y[j] - y[i]
                # нормализуем, сокращая на НОД:
                g = math.gcd(abs(dx), abs(dy))
                dx //= g
                dy //= g
                # вставляем в set:
                vectors.add((dx, dy))
        answ = min(answ, (len(vectors), i + 1))
    # выводим ответ:
    count, index = answ
    print(index, count)
tt = int(input())
for _ in range(tt):
    solve()