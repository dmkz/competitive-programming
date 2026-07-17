# Пример: существует ли подотрезок с суммой 0.
# Ввод: n и массив чисел.
# Вывод: YES, если такой подотрезок есть, иначе NO.

n = int(input())
a = list(map(int, input().split()))

seen = {0}
current_sum = 0
for value in a:
    current_sum += value
    if current_sum in seen:
        print("YES")
        break
    seen.add(current_sum)
else:
    print("NO")