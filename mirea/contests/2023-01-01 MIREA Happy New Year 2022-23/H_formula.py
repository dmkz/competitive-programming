def fwd(t):
    a, s, n = t
    new_s = 6*(s+n)
    new_n = 6*n+1
    new_a = 6*a + 2 * new_s *(new_n - n)
    return new_a, new_s, new_n
    
    
res = [(0, 0, 1)]

for _ in range(10):
    res.append(fwd(res[-1]))
    
q = int(input().strip())

for _ in range(q):
    k = int(input().strip())
    print(res[k][0])