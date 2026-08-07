def check(a, m, x):
    pieces = 0
    for length in a:
        count = length / x
        if count >= m - pieces: return True
        pieces += int(count)
    return False
# Ищем наибольшую длину, из которой получится хотя бы m отрезков.
n, m = map(int, input().split())
a = list(map(int, input().split()))
low, high = 0.0, max(a) + 1.0
for iter in range(100):
    mid = (low + high) / 2
    if check(a, m, mid): low = mid
    else: high = mid
print(f'{low:.10f}')