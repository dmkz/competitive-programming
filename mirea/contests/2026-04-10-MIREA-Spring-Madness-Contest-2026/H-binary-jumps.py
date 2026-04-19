# перестановки, двоичные прыжки, O(n * log(k))
import sys

input = sys.stdin.readline

tt = int(input())
for _ in range(tt):
    n, k = map(int, input().split())
    perm = [x - 1 for x in map(int, input().split())]

    # посчитаем next[p][x] = где окажется элемент x через 2^p шагов
    nxt = [[] for _ in range(60)]
    nxt[0] = perm[:]
    for p in range(1, 60):
        nxt[p] = [0] * n
        for i in range(n):
            # чтобы сделать 2^p шагов:
            # 1) сначала делаем 2^(p-1) шагов -> предподсчитано
            # 2) затем ещё делаем 2^(p-1) шагов -> тоже предподсчитано
            nxt[p][i] = nxt[p - 1][nxt[p - 1][i]]

    # находим, где окажется каждый элемент через k шагов, раскладывая
    # k в сумму степеней двоек:
    ans = []
    for i in range(n):
        curr = i
        for bit in range(59, -1, -1):
            if (k >> bit) & 1:
                curr = nxt[bit][curr]
        ans.append(str(curr + 1))
    print(' '.join(ans))