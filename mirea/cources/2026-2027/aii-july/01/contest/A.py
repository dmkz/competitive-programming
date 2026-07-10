# Сначала найдём максимум в исходном массиве. Назовём его max1. Теперь найдём второй
# максимум, пройдя вдоль массива ещё раз в поисках максимального элемента среди тех,
# которые меньше max1.
def solve():
    n = int(input())
    a = list(map(int, input().split()))
    # первый максимум:
    max1 = max(a)
    # второй максимум:
    max2 = -1000000000
    for i in range(n):
        if max2 < a[i] and a[i] < max1:
            max2 = a[i]
    print(max2)

tt = int(input())
for _ in range(tt):
    solve()