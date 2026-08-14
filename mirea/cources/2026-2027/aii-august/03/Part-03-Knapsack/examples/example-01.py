# Считываем предметы и вместимость рюкзака:
n, c = map(int, input().split())
w, v = [], []
for i in range(n):
    weight, value = map(int, input().split())
    w.append(weight)
    v.append(value)
def setmax(a, index, value):
    # Заменяем элемент, только если кандидат его улучшает.
    if a[index] < value: a[index] = value
# previous[x] хранит наибольшую ценность набора из уже обработанных предметов для вместимости x.
previous = [0] * (c + 1)
for i in range(n):
    # Копируем варианты, в которых предмет i не входит в набор.
    current = previous[:]
    # Если взять предмет i, добавляем его ценность к оптимальному набору вместимости x - w[i].
    for x in range(w[i], c + 1):
        setmax(current, x, previous[x - w[i]] + v[i])
    # Полученная строка описывает уже обработанные предметы на следующем шаге.
    previous = current
print(previous[c])