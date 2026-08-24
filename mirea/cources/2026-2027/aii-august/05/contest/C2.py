# Время: 1296 мс, Память: 135288 КБ
# дополнительные оптимизации по сравнению с решением на C++:
# 1. В решете храним минимальные делители только нечётных чисел.
# 2. Для простых чисел оставляем ноль, поэтому не нужен дополнительный проход по решету.
# 3. Одинаковые простые множители в факторизации обрабатываем одной группой.
# 4. В стеке сохраняем факторизацию числа и ответ до умножения на x.
# 5. При отмене операции восстанавливаем сохранённый ответ без модульного деления.
# 6. Кэшируем уже вычисленные обратные элементы.
# операции по простому модулю:
mod = 998244353
invs = {1: 1}
# умножение:
def mulmod(a, b):
    return a * b % mod
# обратный:
def invmod(b):
    result = invs.get(b)
    if result is None:
        result = pow(b, -1, mod)
        invs[b] = result
    return result
# деление:
def divmod(a, b):
    return mulmod(a, invmod(b))
# предподсчёт минимальных простых делителей:
NMAX = 10 ** 7
minDiv = [0] * (NMAX // 2 + 1)
def precalc():
    # отдельно храним минимальные делители только нечётных чисел:
    i = 3
    while i * i <= NMAX:
        if not minDiv[i // 2]:
            for j in range(i * i, NMAX + 1, 2 * i):
                if not minDiv[j // 2]:
                    minDiv[j // 2] = i
        i += 2
def factor(x):
    result = []
    # отдельно извлекаем простой делитель 2:
    k = 0
    while x % 2 == 0:
        x //= 2
        k += 1
    if k:
        result.append((2, k))
    # извлекаем остальные простые делители:
    while x > 1:
        p = minDiv[x // 2]
        if not p:
            result.append((x, 1))
            break
        k = 0
        while x % p == 0:
            x //= p
            k += 1
        result.append((p, k))
    return result
# решение задачи:
def solve():
    q = int(input())
    st = [] # стек запросов в порядке обработки
    cnt = {} # количество каждого простого числа
    answ = 1 # текущее количество делителей
    while q > 0:
        s = input().split()
        t = s[0]
        if t == '+':
            # умножение на новое число: обновляем все простые, которые в него входят
            x = int(s[1])
            primeDivisors = factor(x)
            st.append((answ, primeDivisors)) # сохраняем ответ до умножения
            for p, k in primeDivisors:
                # обновляем степень этого делителя:
                prev = cnt.get(p, 0)
                cnt[p] = prev + k
                answ = divmod(answ, prev + 1) # делим на то, что было
                answ = mulmod(answ, prev + k + 1) # умножаем на то, что стало
        else:
            # отмена операции: восстанавливаем сохранённый ответ
            answ, primeDivisors = st.pop()
            for p, k in primeDivisors:
                cnt[p] -= k
        # выводим ответ:
        print(answ)
        q -= 1
precalc() # предподсчитываем минимальные простые делители один раз
tt = int(input())
while tt > 0:
    solve()
    tt -= 1