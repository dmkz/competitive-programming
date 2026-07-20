# Перед ответом на запросы для каждого префикса и каждого суффикса
# заранее посчитаем количество уникальных чисел. Для этого идём вдоль массива,
# вставляем очередной элемент в set и сохраняем размер set после вставки.
# При ответе на запросы берём из массива заранее посчитанные значения и выводим их.
def solve():
    # читаем массив
    n, q = map(int, input().split())
    a = list(map(int, input().split()))
    # считаем и запоминаем количество уникальных элементов на каждом префиксе:
    numbers = set()
    p = [0] * n
    for i in range(n):
        numbers.add(a[i])
        p[i] = len(numbers)
    # аналогично для каждого суффикса:
    numbers.clear()
    s = [0] * n
    for i in range(n - 1, -1, -1):
        numbers.add(a[i])
        s[i] = len(numbers)
    # отвечаем на запросы:
    while q > 0:
        c, i = input().split()
        i = int(i) - 1
        print(p[i] if c == 'p' else s[i])
        q -= 1


tt = int(input())
while tt > 0:
    solve()
    tt -= 1