n = int(input())
k = 0
while n > 1:
    n = n - n // 2
    k += 1
print(k)