# перестановки, циклы, O(n)
import sys

input = sys.stdin.readline

tt = int(input())
for _ in range(tt):
    n, k = map(int, input().split())
    perm = [x - 1 for x in map(int, input().split())]

    # раскладываем перестановку в произведение независимых циклов:
    used = [0] * n
    answ = [0] * n

    for i in range(n):
        if not used[i]:
            # ищем цикл, который начинается с элемента i:
            used[i] = 1
            cycle = [i]
            j = perm[i]
            while j != i:
                used[j] = 1
                cycle.append(j)
                j = perm[j]

            # сдвигаем все элементы цикла на k mod (длина цикла)
            m = len(cycle)
            shift = k % m
            for j in range(m):
                answ[cycle[j]] = cycle[(j + shift) % m]

    # выводим ответ:
    print(' '.join(str(x + 1) for x in answ))