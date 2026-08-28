import math
pi = math.acos(-1)
def solve():
    # читаем данные:
    x0, y0, xv, yv, xp, yp = map(int, input().split())
    # переносим окружность в начало координат:
    xv -= x0
    yv -= y0
    xp -= x0
    yp -= y0
    # считаем полярный угол для Васи и Пети:
    a1 = math.atan2(yv, xv)
    a2 = math.atan2(yp, xp)
    # считаем минимальный угол между ними:
    if a1 < a2:
        a1, a2 = a2, a1
    minAngle = min(a1 - a2, a2 - a1 + 2 * pi)
    # находим ответ: делим длину дуги пополам, так как они двигаются навстречу друг другу
    R = math.hypot(xv, yv) # радиус окружности
    print(f"{R * minAngle / 2:.12f}") # длина дуги
tt = int(input())
for _ in range(tt):
    solve()