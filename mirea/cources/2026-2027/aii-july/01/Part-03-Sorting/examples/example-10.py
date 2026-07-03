# Сортировка слиянием в Python3


def merge_sort(a):
    if len(a) <= 1:
        return a

    mid = len(a) // 2

    # Разбиваем список на две половины и сортируем их отдельно
    left = merge_sort(a[:mid])
    right = merge_sort(a[mid:])

    # Сливаем две уже отсортированные половины в один отсортированный список
    merged = []
    i = 0
    j = 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            merged.append(left[i])
            i += 1
        else:
            merged.append(right[j])
            j += 1

    # Добавляем оставшиеся элементы
    while i < len(left):
        merged.append(left[i])
        i += 1
    while j < len(right):
        merged.append(right[j])
        j += 1

    return merged


# Чтение списка и запуск сортировки
n = int(input())
a = list(map(int, input().split()))
a = merge_sort(a)

# Вывод отсортированного списка
print(*a)