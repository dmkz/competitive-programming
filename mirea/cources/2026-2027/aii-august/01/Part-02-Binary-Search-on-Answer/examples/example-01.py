# Читаем число доступных единичных квадратов.
n = int(input())
# low подходит, high не подходит.
low, high = 1, 2_000_000_000
while high - low > 1:
    mid = (low + high) // 2
    if mid * mid <= n: low = mid
    else: high = mid
print(low)