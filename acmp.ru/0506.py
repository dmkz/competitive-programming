n, k1, k2, s = (int(x) for x in input().split())
count = [[0 for _ in range(n+1)] for _ in range(n+1)]
count[k1][k2] = 2**100
for i1 in range(k1, n):
    for i2 in range(k2, n):
        count[i1+1][i2] += count[i1][i2] // 2
        count[i1][i2+1] += count[i1][i2] // 2

s1 = 0; s2 = 0;
for i in range(n+1): s1 += count[i][n];
for i in range(n+1): s2 += count[n][i];
assert(s1+s2 == 2**100)
s1 = s * s1 // 2**100
s2 = s * s2 // 2**100
print(s2, s1, end = ' ')
