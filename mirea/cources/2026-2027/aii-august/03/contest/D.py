inf = 1 << 60
def solve():
    # читаем все доступные данные:
    nRows, nCols, q = map(int, input().split())
    a = [list(map(int, input().split())) for _ in range(nRows)]
    rows = list(map(int, input().split()))
    cols = list(map(int, input().split()))
    # считаем две динамики: прямую (1, 1) -> (n, m) и обратную (n, m) -> (1, 1)
    dpS = [[-inf] * nCols for _ in range(nRows)]
    dpF = [[-inf] * nCols for _ in range(nRows)]
    dpS[0][0] = a[0][0]
    dpF[nRows - 1][nCols - 1] = a[nRows - 1][nCols - 1]
    # переходы для прямой динамики:
    for r in range(nRows):
        for c in range(nCols):
            if r > 0:
                dpS[r][c] = max(dpS[r][c], a[r][c] + dpS[r - 1][c])
            if c > 0:
                dpS[r][c] = max(dpS[r][c], a[r][c] + dpS[r][c - 1])
    # переходы для обратной динамики:
    for r in range(nRows - 1, -1, -1):
        for c in range(nCols - 1, -1, -1):
            if r + 1 < nRows:
                dpF[r][c] = max(dpF[r][c], a[r][c] + dpF[r + 1][c])
            if c + 1 < nCols:
                dpF[r][c] = max(dpF[r][c], a[r][c] + dpF[r][c + 1])
    # отвечаем на запросы:
    for i in range(q):
        r, c = rows[i] - 1, cols[i] - 1
        res = dpS[r][c] + dpF[r][c] - a[r][c]
        print(res)
tt = int(input())
while tt > 0:
    solve()
    tt -= 1