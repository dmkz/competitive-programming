# структура данных для хранения прямоугольника:
class Rect:
    def __init__(self, x1, y1, x2, y2):
        self.xMin = x1
        self.yMin = y1
        self.xMax = x2
        self.yMax = y2
    def square(self):
        return max(0, self.xMax - self.xMin) * max(0, self.yMax - self.yMin)
# пересечение двух прямоугольников:
def intersect(a, b):
    return Rect(max(a.xMin, b.xMin), max(a.yMin, b.yMin),
                min(a.xMax, b.xMax), min(a.yMax, b.yMax))
# решение задачи:
inf = 10**9 + 7
def solve():
    # читаем прямоугольники:
    n = int(input())
    x1 = [-inf] + list(map(int, input().split())) + [-inf]
    y1 = [-inf] + list(map(int, input().split())) + [-inf]
    x2 = [+inf] + list(map(int, input().split())) + [+inf]
    y2 = [+inf] + list(map(int, input().split())) + [+inf]
    # считаем пересечение прямоугольников на каждом префиксе:
    pref = [Rect(-inf, -inf, +inf, +inf) for _ in range(1 + n + 1)]
    for i in range(1, n + 1):
        pref[i] = intersect(pref[i - 1], Rect(x1[i], y1[i], x2[i], y2[i]))
    # считаем пересечение прямоугольников на каждом суффиксе:
    suff = [Rect(-inf, -inf, +inf, +inf) for _ in range(1 + n + 1)]
    for i in range(n, 0, -1):
        suff[i] = intersect(suff[i + 1], Rect(x1[i], y1[i], x2[i], y2[i]))
    # находим максимальную площадь пересечения всех прямоугольников, исключая i-й:
    bestS, bestI = -1, -1
    for i in range(1, n + 1):
        si = intersect(pref[i - 1], suff[i + 1]).square()
        if bestS < si:
            bestS, bestI = si, i
    print(bestI, bestS)
tt = int(input())
for _ in range(tt):
    solve()