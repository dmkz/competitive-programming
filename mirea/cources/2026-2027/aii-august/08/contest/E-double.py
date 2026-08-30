# Codeforces: OK, 562 мс
# Яндекс.Контест: OK, 1.143 с
from math import sqrt, hypot
# геометрия: решаем специально в типе "float", чтобы убедиться, что стандартный тип заходит
EPS = 1e-15
# стандартное сравнение двух чисел по относительной или абсолютной ошибке:
def isAlmostEqual(a, b, eps=EPS):
    return abs(a-b) <= eps * max(1, abs(a), abs(b))
# структура под геометрический вектор и операции с ним:
class Vec:
    def __init__(self, x=0, y=0):
        self.x, self.y = x, y
    def __add__(self, v):
        return Vec(self.x + v.x, self.y + v.y)
    def __sub__(self, v):
        return Vec(self.x - v.x, self.y - v.y)
    def __neg__(self):
        return Vec(-self.x, -self.y)
    def __mul__(self, a):
        return Vec(a * self.x, a * self.y)
    def __truediv__(self, a):
        return Vec(self.x / a, self.y / a)
# скалярное произведение:
def dot(a, b):
    return a.x * b.x + a.y * b.y
# длина вектора:
def norm(a):
    return sqrt(dot(a, a))
# векторное произведение:
def cross(a, b):
    return a.x * b.y - a.y * b.x
Pt = Vec
# проверка, находится ли точка P внутри треугольника ABC: сравниваем ориентацию векторов
def insideTriangle(P, A, B, C):
    return cross(B-A, P-A) >= 0 and cross(C-B, P-B) >= 0 and cross(A-C, P-C) >= 0
# решение задачи:
def solve():
    # читаем данные:
    n = int(input())
    xA, yA, xB, yB, xC, yC = map(int, input().split())
    x, y = [0] * n, [0] * n
    for i in range(n):
        x[i], y[i] = map(int, input().split())
    # Построение треугольника:
    pa, pb, pc = Pt(xA, yA), Pt(xB, yB), Pt(xC, yC)
    va = pa / norm(pa)
    vb = pb / norm(pb)
    vc = pc / norm(pc)
    # функция проверки, покрывает ли треугольник все точки через t секунд?
    def check(t):
        # Строим треугольник через t секунд:
        A = pa + va * t
        B = pb + vb * t
        C = pc + vc * t
        # Проверяем, что он поглотит все точки:
        for i in range(n):
            if not insideTriangle(Pt(x[i], y[i]), A, B, C):
                return False
        return True
    # бинарный поиск по ответу, потому что непонятно, какую величину взять за high
    # 1. находим первоначальные границы поиска: (low, high]
    low, high = 0, 1e-7
    while not check(high):
        low = high
        high *= 2
    # 2. сужаем поиск:
    while not isAlmostEqual(low, high, 1e-7):
        mid = (low + high) / 2
        # Проверяем, что треугольник поглотит все точки:
        if check(mid): high = mid
        else: low = mid
    # выводим ответ:
    print(f"{(high + low) / 2:.12f}")
tt = int(input())
for _ in range(tt):
    solve()