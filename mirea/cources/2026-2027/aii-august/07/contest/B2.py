def solve():
    # читаем данные:
    a, b, c, x, y, z = map(int, input().split())
    # применим бинарный поиск по ответу: по размеру сета роллов
    # функция проверки заданного размера сета роллов:
    def check(n):
        na = n // a
        if na < x:
            return False # первый не наелся
        nb = n // b - n // (a * b)
        if nb < y:
            return False # второй не наелся
        nc = n // c - n // (b * c) - n // (a * c) + n // (a * b * c)
        return nc >= z # наелся ли третий
    # ищем ответ на полуинтервале (0, 10^{18}]:
    low, high = 0, 10**18
    while high - low > 1:
        mid = (low + high) // 2
        if check(mid):
            high = mid
        else:
            low = mid
    print(high)
tt = int(input())
for _ in range(tt):
    solve()