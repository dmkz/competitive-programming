# Считываем веса предметов и проверяемый вес:
n, c = map(int, input().split())
w = list(map(int, input().split()))
# Бит с номером x показывает, достижим ли вес x.
# Единственный установленный бит соответствует пустому подмножеству с весом 0.
possible = 1
# Сдвиг создаёт варианты с предметом i, а | сохраняет варианты без него.
for i in range(n):
    possible |= possible << w[i]
if possible >> c & 1: print('YES')
else: print('NO')