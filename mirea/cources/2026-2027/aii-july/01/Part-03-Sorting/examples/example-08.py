# Демонстрация устойчивой сортировки в Python3

# Встроенная сортировка Python3 уже является устойчивой
students = [
    (2, "Ann"),
    (1, "Boris"),
    (2, "Clara"),
    (1, "Diana"),
    (2, "Eva"),
]

# Сортируем по первому элементу пары и сохраняем порядок равных элементов
students.sort(key=lambda item: item[0])

# Вывод результата
for score, name in students:
    print(f"{score}:{name}")