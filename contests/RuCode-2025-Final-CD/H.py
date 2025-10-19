import sys

# Задача: H, Вердикт: OK, Время: 0.400, Память: 120 MB
#
# Самое важное в этой задаче понять, что они могут перемещаться одновременно
# только за время t5 или t6. Все другие способы (t1, t2, t3, t4) выглядят так,
# что одна из лягушек осуществляет перемещение, а вторая стоит на месте и ждёт,
# пока вторая не завершит перемещение на соседнюю кувшинку.
# В связи с этим, решение выглядит следующим образом: пусть между ними расстояние
# dist, а timeA и timeB - время, за которое лягушки A и B делают перемещение навстречу
# друг другу поочерёдно, а timeAB - время, за которое они шагают одновременно.
# Тогда расстояние dist уменьшается на 2 за min(2 * min(timeA, timeB), timeAB) -
# либо самая быстрая лягушка делает два шага, либо они шагают навстречу друг другу.
# Таким образом, мы можем уменьшать расстояние на 2 кувшинки пока dist >= 2.
# При dist == 1 последний шаг делает самая быстрая лягушка за min(timeA, timeB).
# ОСОБЫЙ СЛУЧАЙ: иногда выгодно увеличить dist на 1, а только потом начать сближаться.
# Пусть самая быстрая лягушка отпрыгнет назад, а потом они начнут сближаться.
# Рассмотрим все 4 варианта и выберем минимум:
# 1) сближаемся по дуге AB:
#     a) сразу; b) с отпрыгиванием назад;
# 2) сближаемся по дуге BA:
#     c) сразу; d) с отпрыгиванием назад.
# Ответ: min(a, b, c, d)
#
# Отличия от решения на C++:
# - В Python нет перегрузки функций, поэтому используем разные имена функций.
# - В Python целые числа произвольной длины, отдельные типы int64_t не нужны.
# - Используется быстрый ввод-вывод через sys.stdin/sys.stdout.

# функция для вычисления времени сближения напрямик, уменьшая расстояние dist
def solve_dist(dist: int, timeA: int, timeB: int, timeMeet: int) -> int:
    # за время timeMeet -> dist-2
    # за время 2 * min(timeA, timeB) -> dist-2
    per2 = min(timeMeet, 2 * min(timeA, timeB))
    answ = (dist // 2) * per2
    if dist % 2:
        answ += min(timeA, timeB)
    return answ

# функция, рассматривающая два варианта:
# --- 1) сближаемся напрямик;
# --- 2) делаем шаг назад и сближаемся напрямик.
def solve_with_back(dist: int, timeA: int, timeB: int, timeAinv: int, timeBinv: int, timeMeet: int) -> int:
    return min(
        solve_dist(dist, timeA, timeB, timeMeet),
        solve_dist(dist + 1, timeA, timeB, timeMeet) + min(timeAinv, timeBinv)
    )

# функция для оригинальных входных данных
def solve_full(n: int, a: int, b: int, t1: int, t2: int, t3: int, t4: int, t5: int, t6: int) -> int:
    # считаем длину дуги AB:
    dAB = (b - a) if (a <= b) else (b + n - a)
    # считаем длину дуги BA:
    dBA = (a - b) if (b <= a) else (a + n - b)
    # считаем время для преодоления дуги AB:
    answAB = solve_with_back(dAB, t1, t4, t2, t3, t5)
    # считаем время для преодоления дуги BA:
    answBA = solve_with_back(dBA, t2, t3, t1, t4, t6)
    # берём минимум:
    return min(answAB, answBA)

def main():
    data = sys.stdin.read().strip().split()
    it = iter(data)
    tt = int(next(it))
    out = []
    for _ in range(tt):
        # решаем задачу для одного набора входных данных:
        n = int(next(it)); a = int(next(it)); b = int(next(it))
        t1 = int(next(it)); t2 = int(next(it)); t3 = int(next(it))
        t4 = int(next(it)); t5 = int(next(it)); t6 = int(next(it))
        out.append(str(solve_full(n, a, b, t1, t2, t3, t4, t5, t6)))
    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    main()
