inf = 10**18
n, len, a = map(int, input().split())
items = [[] for _ in range(n)] # {width, height, cost}
for i in range(n):
    w, h, a0, a1, a2, a3 = map(int, input().split())
    items[i].append((w, h, max(a0, a2)))
    items[i].append((h, w, max(a1, a3)))
# sum W <= len
# max H <= answ
# sum cost >= a
def check(maxH):
    # можно ли, взяв только картины высотой <= maxH, добиться суммарной стоимости >= a,
    # используя длину l? dp[l] = max total cost
    curr = [-inf] * (1+len)
    curr[0] = 0
    for i in range(n):
        next = curr.copy()
        w1, h1, a1 = items[i][0]
        w2, h2, a2 = items[i][1]
        if h1 <= maxH:
            for was in range(len-w1, -1, -1):
                next[was+w1] = max(next[was+w1], curr[was] + a1)
        if h2 <= maxH:
            for was in range(len-w2, -1, -1):
                next[was+w2] = max(next[was+w2], curr[was] + a2)
        curr = next
    return max(curr) >= a
# бинарный поиск по ответу - максимальной высоте картины
low, high = -1, 10**5
while high - low > 1:
    mid = (low + high) // 2
    if check(mid): high = mid
    else: low = mid
if high >= 10**4: print(-1)
else: print(high)