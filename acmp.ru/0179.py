last = int(input())
sum = [0 for _ in range(0, last+1)]
for i in range(1, last+1): 
    sum[i] = 3 * sum[i-1] + 2;
print(sum[last]+2);