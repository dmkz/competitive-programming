mod = int(1e9) + 7
# решение:
def solve():
    n, m = map(int, input().split())
    q = int(input())
    invPow2 = pow(pow(2, 60, mod), -1, mod)
    answ = pow(2, 60 * n * m, mod)
    xorRows, xorCols = 0, 0
    usedRows, usedCols = 0, 0
    while q > 0:
        ch = input().split()
        if ch[0] == 'r':
            k, x = int(ch[1]), int(ch[2])
            usedRows += 1
            xorRows ^= x
        else:
            assert ch[0] == 'c'
            k, x = int(ch[1]), int(ch[2])
            usedCols += 1
            xorCols ^= x
        if usedRows == n and usedCols == m and xorRows != xorCols:
            answ = 0
        if usedRows + usedCols < n + m:
            answ = answ * invPow2 % mod
        print(answ)
        q -= 1
tt = int(input())
while tt > 0:
    solve()
    tt -= 1