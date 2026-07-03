# Сортировка списка по возрастанию и убыванию в Python3


def print_list(a):
    print(*a)


# Чтение списка и подготовка вариантов сортировки
n = int(input())
a = list(map(int, input().split()))

asc = sorted(a)
desc = sorted(a, reverse=True)
in_place = a[:]

# Сортировка списка на месте по возрастанию
in_place.sort()

# Вывод результата
print_list(asc)
print_list(desc)
print_list(in_place)