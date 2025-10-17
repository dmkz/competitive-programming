# Задача: J, Вердикт: OK, Время: 0.897s, Память: 110.59Mb

# В задаче требуется найти вес минимального остовного дерева (MST) во взвешанном
# графе. На C++ или других компилируемых языках с этим справляется алгоритм Прима.
# На Python3 вместо алгоритма Прима используем алгоритм Краскала - он быстрее, но
# сложнее! Алгоритм Краскала:
# - сортируем рёбра по весу (a + b * x);
# - проходим рёбра по возрастанию и добавляем те, что соединяют разные компоненты связности (DSU);
# - когда добавлено n-1 рёбер, получен MST.
# Поскольку вес рёбер зависит от параметра "x" линейно и x в [L, R], минимум по "x"
# достигается на концах отрезка: считаем MST для x = L и x = R и берём минимум из них.

# Быстрый ввод-вывод на Python 3:
# - читаем весь stdin байтами: sys.stdin.buffer.read().split()
# - итерируемся по токенам как по итератору
# - выводим все ответы одной операцией через sys.stdout.write

import sys

class DSU:
    # Система Непересекающихся Множеств (DSU) с сжатием путей и объединением по размеру
    def __init__(self, n: int):
        self.p = list(range(n + 1))
        self.sz = [1] * (n + 1)

    def find(self, x: int) -> int:
        # Эвристика сжатия путей
        p = self.p
        while p[x] != x:
            p[x] = p[p[x]]
            x = p[x]
        return x

    def union(self, a: int, b: int) -> bool:
        # объединение компонент связности для "a" и "b"
        pa = self.find(a)
        pb = self.find(b)
        if pa == pb:
            return False
        if self.sz[pa] < self.sz[pb]:
            pa, pb = pb, pa
        self.p[pb] = pa
        self.sz[pa] += self.sz[pb]
        return True

def solve_all():
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    out = []

    while True:
        try: # пытаемся прочитать тест
            n = int(next(it));
            m = int(next(it));
            L = int(next(it));
            R = int(next(it))
        except StopIteration:
            break
        if n == 0: # тесты закончились
            break

        # Храним рёбра в массивах для минимизации накладных расходов в Python.
        # Используем списки смежности для хранения графа.
        U = [0] * m
        V = [0] * m
        A = [0] * m
        B = [0] * m
        for i in range(m):
            u = int(next(it));
            v = int(next(it));
            a = int(next(it));
            b = int(next(it));
            U[i] = u;
            V[i] = v;
            A[i] = a;
            B[i] = b;

        def mst_cost(x: int) -> int:
            # Ускорение для Python3:
            # Вычисляем веса ребёр графа для текущего x и порядок индексов рёбер
            # по возрастанию этого веса.
            # Декорируем: одна таблица весов W и сортировка индексов по W.
            W = [A[i] + B[i] * x for i in range(m)]
            order = list(range(m))
            order.sort(key=W.__getitem__)
            
            dsu = DSU(n)
            taken = 0
            total = 0
            # Локальные переменные для ускорения доступа.
            U_loc, V_loc, W_loc = U, V, W
            find = dsu.find
            union = dsu.union
            # проходимся по всем рёбрам в порядке возрастания веса
            for idx in order:
                # ребро u <--> v
                u = U_loc[idx]; v = V_loc[idx]
                # если они в разных компонентах связности
                if find(u) != find(v):
                    union(u, v); # объединяем
                    total += W_loc[idx]; # увеличиваем ответ
                    taken += 1;
                    if taken == n - 1:
                        break
            return total

        # Линейность по x => минимум на концах [L, R]: считаем оба и берём min.
        ans = mst_cost(L)
        valR = mst_cost(R)
        if valR < ans:
            ans = valR
        out.append(str(ans))
    
    # для ускорения вывода выводим все ответы сразу:
    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    solve_all()