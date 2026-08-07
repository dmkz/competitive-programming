def sum_squares(k):
    return k * (k + 1) * (2 * k + 1) // 6
n = int(input())
# Ищем последнее k, для которого хватает квадратов на все фигуры от 1 до k.
low, high = 0, 1_500_000
while high - low > 1:
    mid = (low + high) // 2
    if sum_squares(mid) <= n: low = mid
    else: high = mid
print(low)