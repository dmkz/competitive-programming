# Считываем проходимость и значения клеток:
n, m = map(int, input().split())
cells = [input() for i in range(n)]
a = [list(map(int, input().split())) for i in range(n)]
# previous хранит значения для строки над текущей, а current формируется для текущей строки.
inf = 10 ** 30
previous = [-inf] * m
for i in range(n):
    # Обработку новой строки начинаем с недостижимых состояний.
    current = [-inf] * m
    for j in range(m):
        # Через закрытую клетку путь пройти не может.
        if cells[i][j] == '#': continue
        # Верхняя левая клетка служит началом любого пути.
        if i == 0 and j == 0: current[j] = a[i][j]
        else:
            # Выбираем лучший из путей, которые приходят сверху или слева.
            best = max(previous[j], -inf if j == 0 else current[j - 1])
            # Значение для клетки можно получить только от достижимого предшественника.
            if best != -inf: current[j] = best + a[i][j]
    # После обработки эта строка станет предыдущей для следующей.
    previous = current
if previous[m - 1] == -inf: print('IMPOSSIBLE')
else: print(previous[m - 1])