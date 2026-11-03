def ask(x):
    print("?", x, flush=True)
    res = input()
    return res
def solve():
    n = int(input())
    # сначала находим L:
    low, high = 0, n+1
    while high - low > 1:
        mid = (low + high) // 2
        if ask(mid) == "LEFT":
            low = mid
        else:
            high = mid
    L = high
    # теперь находим R:
    high = n+1
    while high - low > 1:
        mid = (low + high) // 2
        if ask(mid) == "RIGHT":
            high = mid
        else:
            low = mid
    R = low
    # выводим ответ
    print("!", L, R, flush=True)
tt = int(input())
while tt > 0:
    tt -= 1
    solve()