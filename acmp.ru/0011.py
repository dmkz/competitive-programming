k, n = (int(x) for x in input().split())
a = [0]*(n+1); a[0] = 1
for i in range(0, n):
    limit = min(n-i, k)
    for j in range(1, limit+1):
        a[i+j] += a[i]
print(a[n])