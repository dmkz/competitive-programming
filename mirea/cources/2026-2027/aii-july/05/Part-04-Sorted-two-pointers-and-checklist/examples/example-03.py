# Пример: количество пар с суммой не больше s двумя указателями после сортировки.
# Ввод: число тестов, затем для каждого теста n, s и массив a.
# Вывод: для каждого теста число пар (i, j), i < j, таких что a[i] + a[j] <= s.

def solve():
    n, s = map(int, input().split())
    a = list(map(int, input().split()))

    a.sort()

    left = 0
    right = n - 1
    answer = 0
    while left < right:
        current_sum = a[left] + a[right]
        if current_sum <= s:
            # Для фиксированного left подходят все вторые индексы от left + 1 до right.
            answer += right - left
            left += 1
        else:
            # Правый элемент слишком велик, уменьшаем сумму.
            right -= 1

    print(answer)


tests = int(input())
for _ in range(tests):
    solve()