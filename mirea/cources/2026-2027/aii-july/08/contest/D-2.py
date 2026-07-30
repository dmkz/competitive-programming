# Прочитаем все числа, которые когда-либо появятся в множестве, и отсортируем их. Затем
# рассмотрим запросы в обратном порядке: каждая вставка теперь станет удалением. Медиану
# полного множества легко найти в отсортированном массиве. При удалении одного числа
# нижняя медиана сдвигается не более чем на одного соседа. Соседей храним в двусвязном
# списке, реализованном двумя массивами Prev и Next.
from bisect import bisect_left

def solve():
    # читаем начальные числа и запросы:
    n, q = map(int, input().split())
    initial = list(map(int, input().split()))
    queries = list(map(int, input().split()))
    x = initial + queries
    # сортируем все числа, которые будут в множестве после последней вставки:
    x.sort()
    # строим двусвязный список отсортированных чисел:
    Prev = [-1] * (n + q)
    Next = [-1] * (n + q)
    for i in range(n + q - 1):
        Prev[i + 1] = i
        Next[i] = i + 1
    # в полном множестве находим нижнюю медиану:
    median = (n + q - 1) // 2
    answ = [0] * q
    # обрабатываем запросы с конца: вставка превращается в удаление:
    for query_id in range(q - 1, -1, -1):
        # текущая нижняя медиана и есть ответ после этой вставки:
        answ[query_id] = x[median]
        # находим элемент, который теперь нужно удалить:
        xi = bisect_left(x, queries[query_id])
        size = n + query_id + 1
        # сдвигаем медиану до удаления, если её ранг изменится:
        if size % 2 == 0 and xi <= median:
            median = Next[median]
        if size % 2 == 1 and xi >= median:
            median = Prev[median]
        # связываем соседей друг с другом, удаляя xi:
        pi = Prev[xi]
        ni = Next[xi]
        if pi != -1:
            Next[pi] = ni
        if ni != -1:
            Prev[ni] = pi
    # выводим ответ:
    for value in answ:
        print(value, end=' ')
    print()


tt = int(input())
while tt > 0:
    solve()
    tt -= 1