from heapq import heappush, heappop
def solve():
    # читаем данные и строим граф
    nVert, nLines = map(int, input().split())
    adj = [[] for _ in range(1+nVert)]
    for j in range(nLines):
        k, s, p = map(int, input().split())
        vertices = list(map(int, input().split()))
        durations = list(map(int, input().split()))
        times = [s]*k
        for i in range(1, k):
            times[i] = times[i-1]+durations[i-1]
        for i in range(k-1):
            from_ = vertices[i]
            to = vertices[i+1]
            adj[from_].append((to, times[i], p, times[i+1]-times[i]))
    # запускаем алгоритм Дейкстры
    inf = 10**18
    dist = [inf]*(1+nVert)
    pq = []
    heappush(pq, (0, 1))
    while pq:
        d, u = heappop(pq)
        if dist[u] <= d:
            continue
        dist[u] = d
        for v, t, p, w in adj[u]:
            # можем поехать в вершину v начиная с времени t каждые p минут
            # t + k * p >= d
            k = (d-t+p-1)//p
            if k < 0: k = 0
            heappush(pq, (t+k*p+w, v))
    # выводим ответ:
    for i in range(1, nVert+1):
        if dist[i] >= inf: dist[i] = -1
    print(*dist[1:])
tt = 1
# tt = int(input())
for _ in range(tt):
    solve()