# Сортировка слиянием через heapq.merge в Python3

from heapq import merge


def merge_sort(a):
    if len(a) <= 1:
        return a

    mid = len(a) // 2

    # Делим список пополам и отдельно сортируем обе половины
    left = merge_sort(a[:mid])
    right = merge_sort(a[mid:])

    # Стандартная функция merge объединяет две отсортированные половины
    return list(merge(left, right))


# Чтение списка и запуск сортировки
n = int(input())
a = list(map(int, input().split()))
a = merge_sort(a)

# Вывод отсортированного списка
print(*a)