def solve():
    # читаем элементы и добавляем их в set:
    n = int(input())
    s = set()
    i = 0
    while i < n:
        for x in map(int, input().split()):
            s.add(x)
            i += 1
            if i == n:
                break
    # вывод уникальных элементов на экран:
    print(" ".join(map(str, sorted(s))))


tt = int(input())
for _ in range(tt):
    solve()