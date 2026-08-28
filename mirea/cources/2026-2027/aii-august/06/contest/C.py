def solve():
    x0, y0, r = map(int, input().split())
    # переносим окружность в (0, 0), то есть просто игнорируем координаты центра
    # далее идём вдоль левой полуплоскости и для каждого x находим границы столбца
    # [yMin+1, yMax-1], который целиком влезает в окружность. Прибавляем его высоту.
    # используем два указателя, чтобы эффективно переходить от x к (x-1).
    yMax, yMin, answ = 0, 0, 0
    for x in range(-r, 0):
        while x * x + yMax * yMax <= r * r:
            yMax += 1
        while x * x + yMin * yMin <= r * r:
            yMin -= 1
        answ += max(0, yMax - yMin - 2)
    print(answ * 2)
tt = int(input())
for _ in range(tt):
    solve()