# математика, жадные алгоритмы, O(n)
import sys

input = sys.stdin.readline

def solve(n, k, a):
    sum_ = 0
    mx = 0
    for i in range(n):
        x = a[i]
        sum_ += x
        mx = max(mx, x)
    others = sum_ - mx
    if mx <= others + 1:
        answ = k * sum_ - (k - 1) * n
    else:
        answ = k * (2 * others + 1) - (k - 1) * (n - 1)
    return answ

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    print(solve(n, k, a))