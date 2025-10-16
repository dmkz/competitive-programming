# Задача: H, Вердикт: OK, Время: 460ms, Память: 48.95Mb

# Римских чисел всего 4000. Построим взвешенный граф на римских числах,
# где переходы между числами описываются правилами из условия.
# Запустим алгоритм Дейкстры поиска всех кратчайших расстояний, начиная
# из пустой римской строки (номер 0). Затем ответим на запросы о
# кратчайших расстояниях до чисел из ввода.
# Используется стандартный ввод через input() и очередь heapq.

import heapq

# таблица для преобразования из арабских чисел в их римскую запись
_ROMAN_TABLE = [
    (1000, "M"), (900, "CM"), (500, "D"), (400, "CD"),
    (100, "C"),  (90, "XC"),  (50, "L"),  (40, "XL"),
    (10, "X"),   (9, "IX"),   (5, "V"),   (4, "IV"),
    (1, "I")
]

def to_roman(x: int) -> str:
    # преобразовать целое x в римскую строку
    s = []
    for value, sym in _ROMAN_TABLE:
        while x >= value:
            s.append(sym)
            x -= value
    return "".join(s)

def generate_roman_map():
    # сгенерировать список римских представлений и словарь их индексов
    roman = [""] * 4000
    idx = {}
    for i in range(1, 4000):
        r = to_roman(i)
        roman[i] = r
        idx[r] = i
    return roman, idx

def precalc_edges(roman, idx):
    # предвычисление переходов удаления префикса/суффикса и добавления
    n = 4000
    del_edges = [[] for _ in range(n)]
    for u in range(1, n):
        s = roman[u]
        # для каждого разбиения строки на префикс и суффикс
        for cut in range(1, len(s)):
            left, right = s[:cut], s[cut:] # префикс + суффикс = s
            li, ri = idx.get(left, 0), idx.get(right, 0) # индексы префикса и суффикса
            if li and ri:
                del_edges[u].append((li, ri))
    add_edges = [[] for _ in range(n)]
    # по каждому удалению восстанавливаем обратные добавления
    for uv in range(1, n):
        for u, v in del_edges[uv]:
            add_edges[u].append((v, uv))
            add_edges[v].append((u, uv))
    # добавления к пустой строке: "" -> v
    for v in range(1, n):
        add_edges[0].append((v, v))
    return del_edges, add_edges

def run_dijkstra(add_cost, del_cost, del_edges, add_edges):
    # классический алгоритм Дейкстры с priority queue (heapq)
    INF = 10**9
    dist = [INF] * 4000
    pq = [(0, 0)]  # (текущая дистанция, вершина)
    while pq:
        d, u = heapq.heappop(pq)
        if d >= dist[u]:
            continue
        dist[u] = d
        # пробуем удаления префикса и суффикса
        for li, ri in del_edges[u]:
            nd = d + del_cost[li]
            if nd < dist[ri]:
                heapq.heappush(pq, (nd, ri))
            nd = d + del_cost[ri]
            if nd < dist[li]:
                heapq.heappush(pq, (nd, li))
        # пробуем добавления
        for k, res in add_edges[u]:
            nd = d + add_cost[k]
            if nd < dist[res]:
                heapq.heappush(pq, (nd, res))
    return dist

def main():
    # генерация всех римских чисел и их индексов
    roman, idx = generate_roman_map()
    # предвычисление ребер графа
    del_edges, add_edges = precalc_edges(roman, idx)

    # начальные стоимости равны номеру
    add_cost = list(range(4000))
    del_cost = list(range(4000))

    # читаем изменения стоимостей (num, новая стоимость добавления, удаления)
    n = int(input())
    for _ in range(n):
        num, c_add, c_del = map(int, input().split())
        add_cost[num] = c_add
        del_cost[num] = c_del

    # запускаем Дейкстру после всех обновлений
    dist = run_dijkstra(add_cost, del_cost, del_edges, add_edges)

    # отвечаем на запросы: для каждого v выводим dist[v]
    q = int(input())
    for _ in range(q):
        v = int(input())
        print(dist[v])

if __name__ == "__main__":
    main()
