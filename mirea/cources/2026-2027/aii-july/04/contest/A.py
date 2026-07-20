# Построим префиксные суммы отдельно для чётных и отдельно для нечётных чисел,
# а затем ответим на запросы.
def solve():
    # читаем массив
    n, q = map(int, input().split())
    a = list(map(int, input().split()))
    # строим префиксные суммы: отдельно для чётных и отдельно для нечётных чисел
    s0 = [0] * (n + 1)
    s1 = [0] * (n + 1)
    for i in range(n):
        s0[i + 1] = s0[i]
        s1[i + 1] = s1[i]
        if a[i] % 2 == 0:
            s0[i + 1] += a[i]
        else:
            s1[i + 1] += a[i]
    # отвечаем на запросы:
    while q > 0:
        l, r = map(int, input().split())
        print(s0[r] - s0[l - 1], s1[r] - s1[l - 1])
        q -= 1


tt = int(input())
while tt > 0:
    solve()
    tt -= 1