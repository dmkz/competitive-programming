n = int(input())
arr = [0 for x in range(0, n+1)]
arr[0] = 1
arr[1] = 1
if (n >= 2): arr[2] = 2
if (n >= 3): arr[3] = 4
for i in range(4, n+1):
    arr[i] += arr[i-1] + arr[i-2] + arr[i-3]
print(arr[n])