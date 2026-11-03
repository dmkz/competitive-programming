from array import array
from collections import deque
# решение задачи:
def solve():
    n, m, p = map(int, input().split())
    a = [list(input()) for _ in range(n)]
    # найдём старт и финиш
    sr, sc, fr, fc = -1, -1, -1, -1
    for r in range(n):
        for c in range(m):
            if a[r][c] == "S":
                sr, sc, a[r][c] = r, c, "."
            if a[r][c] == "T":
                fr, fc, a[r][c] = r, c, "."
    assert sr != -1 and sc != -1
    assert fr != -1 and sc != -1
    # теперь запустим поиск в ширину. чтобы проверять возможность перемещаться в двери, храним
    # также остаток от деления количества шагов на p в состоянии вершины
    # dist[r][c][rem] = кратчайшее время, за которое мы можем попасть в клетку (r, c) с остатком rem
    inf = 10**9+1
    dist = array("i", [inf]) * (n*m*p)
    q = deque()
    start = (sr*m+sc)*p
    dist[start] = 0
    q.append(start)
    while q:
        v = q.popleft()
        rem = v % p
        cell = v // p
        r, c = divmod(cell, m)
        length = dist[v]
        nrem = (rem+1) % p
        for dr in range(-1, 2):
            for dc in range(-1, 2):
                if dr*dr+dc*dc <= 1: # вариант dr=0 && dc=0 соответствует ожиданию на месте
                    nr, nc = r+dr, c+dc
                    if nr < 0 or nc < 0 or nr >= n or nc >= m:
                        continue
                    if a[nr][nc] == "#":
                        continue
                    nv = (nr*m+nc)*p+nrem
                    if dist[nv] != inf:
                        continue
                    # можем ли мы тут оказаться?
                    if a[nr][nc] == chr(ord("0")+nrem):
                        continue
                    dist[nv] = length+1
                    q.append(nv)
    # находим и выводим ответ:
    answ = inf
    for rem in range(p):
        answ = min(answ, dist[(fr*m+fc)*p+rem])
    if answ >= inf:
        answ = -1
    print(answ)
solve()