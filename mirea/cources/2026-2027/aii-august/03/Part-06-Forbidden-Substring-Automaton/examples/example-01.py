mod = 1000000007
def findNext(p, matched, ch):
    # В состоянии matched суффикс строки совпадает с префиксом p такой длины.
    current = p[:matched] + ch
    # Среди суффиксов current ищем самый длинный префикс шаблона.
    for length in range(min(len(p), len(current)), -1, -1):
        equal = True
        # Проверяем, равен ли выбранный суффикс префиксу p той же длины.
        for i in range(length):
            if current[len(current) - length + i] != p[i]: equal = False
        # Перебор идёт по убыванию, поэтому первое совпадение задаёт новое состояние.
        if equal: return length
    return 0
# Считываем длину строящейся строки и запрещённый шаблон:
n = int(input())
p = input()
m = len(p)
# findNext слишком дорог для каждого перехода динамики, поэтому считаем таблицу один раз.
nextState = [[0] * 26 for i in range(m)]
for matched in range(m):
    for ch in range(26):
        nextState[matched][ch] = findNext(p, matched, chr(ord('a') + ch))
# current[j] хранит число строк текущей длины без p, находящихся в состоянии j.
current = [0] * m
# Пустая строка имеет состояние 0.
current[0] = 1
for length in range(n):
    # Добавляем по одной букве к каждой допустимой строке.
    next = [0] * m
    for matched in range(m):
        for ch in range(26):
            to = nextState[matched][ch]
            # Переход в m завершил шаблон, поэтому такую строку не учитываем.
            if to == m: continue
            next[to] = (next[to] + current[matched]) % mod
    # Полученный слой описывает строки следующей длины.
    current = next
# Складываем все безопасные конечные состояния.
print(sum(current) % mod)