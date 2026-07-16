def solve():
    # читаем элементы и запоминаем их позиции в map:
    n, q = map(int, input().split())
    firstPos, lastPos = {}, {}
    i = 1
    while i <= n:
        for x in map(int, input().split()):
            # ищем последнюю позицию
            if x not in lastPos:
                # не найдена - элемент ещё не встречался
                firstPos[x] = i
                lastPos[x] = i
            else:
                # найдена - меняем только последнюю позицию
                lastPos[x] = i
            i += 1
            if i > n:
                break
    # читаем и отвечаем на запросы:
    while q > 0:
        for x in map(int, input().split()):
            if x not in lastPos:
                print(-1)
            else:  # найден:
                print(firstPos[x], lastPos[x])
            q -= 1
            if q == 0:
                break


tt = int(input())
for _ in range(tt):
    solve()