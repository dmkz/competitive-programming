# Напишем рекурсивный перебор, чтобы перебрать все 2^n вариантов расстановки знаков.
# Если мы ставим "+" перед a[i], то сумма увеличивается на a[i], иначе уменьшается.
# Если в самом конце получили ту сумму, которую хотели, то обновляем ответ.
# В данном решении текущая сумма не хранится. Вместо неё хранится величина, которую
# нам ещё осталось набрать.
a = []
s = []
answ = ""
cnt = 0


def clear():
    global a, s, answ, cnt
    a = []
    s = []
    answ = ""
    cnt = 0


def dfs(i, x):
    global answ, cnt
    if i == len(a):
        if x == 0:  # нашли ответ
            cnt += 1
            if not answ:
                answ = "".join(s)
        return
    # пробуем плюс
    s.append('+')
    dfs(i + 1, x - a[i])
    s.pop()
    # пробуем минус
    s.append('-')
    dfs(i + 1, x + a[i])
    s.pop()


def solve():
    # читаем данные
    n, x = map(int, input().split())
    clear()
    a.extend(map(int, input().split()))
    dfs(0, x)
    if cnt == 0:
        print(0)
        print("NO SOLUTION")
    else:
        print(cnt)
        print(answ)


tt = int(input())
while tt > 0:
    solve()
    tt -= 1