# Создадим два массива: один для нечётных элементов, а второй - для чётных.
# Отсортируем их отдельно, как это требуется в задаче, затем выведем их элементы
# на экран, чередуя массивы.
def solve():
    n = int(input())
    a = list(map(int, input().split()))
    odd = [] # нечётные элементы
    even = [] # чётные элементы
    for i in range(1, n + 1):
        x = a[i - 1]
        if i % 2 == 1:
            odd.append(x)
        else:
            even.append(x)
    # сортируем оба вектора:
    odd.sort(reverse=True)
    even.sort()
    # чередуя, выводим ответ:
    i, j = 0, 0
    while i < len(odd):
        # нечётный элемент:
        print(odd[i], end=' ')
        i += 1
        # чётный элемент:
        if j < len(even):
            print(even[j], end=' ')
            j += 1
    print()

tt = int(input())
for _ in range(tt):
    solve()