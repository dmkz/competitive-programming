from math import atan2
# В Python тип float имеет двойную точность
# Структура данных для точки:
class Pt:
    def __init__(self, x, y):
        self.x, self.y = x, y
    def __sub__(self, p):
        return Pt(self.x - p.x, self.y - p.y)
# скалярное произведение:
def dot(a, b):
    return a.x * b.x + a.y * b.y
# векторное произведение:
def cross(a, b):
    return a.x * b.y - a.y * b.x
# угол между двумя векторами:
def angle(a, b):
    return atan2(abs(cross(a,b)),dot(a,b))
# решение:
def solve():
    # читаем данные:
    n = int(input())
    x = list(map(int, input().split()))
    y = list(map(int, input().split()))
    # положение Олега:
    O = Pt(x[n+1], y[n+1])
    sum = 0
    for i in range(1, n+1):
        # наше предыдущее положение:
        A = Pt(x[i-1], y[i-1])
        # наше текущее положение:
        B = Pt(x[i], y[i])
        # Олег поворачивает свой прицел в треугольнике OAB: было OA, стало OB.
        sum += angle(B - O, A - O)
    # выводим ответ:
    print(f"{sum:.12f}")
tt = int(input())
for _ in range(tt):
    solve()