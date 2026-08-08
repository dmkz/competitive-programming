def enumerate(i, n, path):
    if i == n:
        print(*path)
        return
    if i > n: return
    # Продолжаем маршрут каждым допустимым прыжком.
    for jump in (1, 2):
        path.append(jump)
        enumerate(i + jump, n, path)
        path.pop()
# Читаем конечную ступень:
n = int(input())
enumerate(0, n, [])