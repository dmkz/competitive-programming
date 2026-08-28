# структура для хранения точки:
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    def __sub__(self, other):
        return Point(self.x - other.x, self.y - other.y)
# векторное произведение:
def cross(a, b):
    return a.x * b.y - a.y * b.x
# решение задачи:
def solve():
    # читаем данные:
    n = int(input())
    x = list(map(int, input().split()))
    y = list(map(int, input().split()))
    # сначала отметим сами пики:
    isPeak = [False] * n
    cntPeaks = 0
    for i in range(1, n - 1):
        isPeak[i] = y[i] > max(y[i - 1], y[i + 1])
        cntPeaks += isPeak[i]
    # теперь для каждого горного пика посчитаем, сколько пиков мы с него увидим
    answ = [0] * n
    for i in range(1, n - 1):
        if not isPeak[i]:
            continue
        pi = Point(x[i], y[i])
        # считаем в правую сторону: храним точку, которая образует максимальный угол
        # мы видим новый горный пик, если прямая от текущей точки до него не пересекает
        # ни одну из предыдущих точек. Это означает новый максимальный угол, ведь все
        # остальные находятся ниже.
        # ОЧЕНЬ ВАЖНО: максимум храним среди всех точек, а не только среди пиков
        m = i + 1
        for r in range(i + 2, n):
            currVec = Point(x[r], y[r]) - pi
            bestVec = Point(x[m], y[m]) - pi
            # если самый лучший вектор находится под текущим:
            if cross(bestVec, currVec) > 0:
                # новый максимум
                answ[i] += isPeak[r]
                m = r
        # аналогично считаем в левую сторону:
        m = i - 1
        for l in range(i - 2, -1, -1):
            currVec = Point(x[l], y[l]) - pi
            bestVec = Point(x[m], y[m]) - pi
            # если самый лучший вектор находится под текущим:
            if cross(bestVec, currVec) < 0:
                # новый минимум
                answ[i] += isPeak[l]
                m = l
    # выводим ответы:
    print(cntPeaks)
    for i in range(n):
        if isPeak[i]:
            print(i + 1, answ[i])
tt = int(input())
for _ in range(tt):
    solve()