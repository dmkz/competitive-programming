# Время: 765 мс, Память: 16660 КБ
# операции по простому модулю:
mod = 998244353
# умножение:
def mulmod(a, b):
    return a * b % mod
# обратный:
def invmod(b):
    return pow(b, -1, mod)
# деление:
def divmod(a, b):
    return mulmod(a, invmod(b))
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
            # умножение на новое число: увеличиваем количество и обновляем ответ
            p = int(s[1])
            st.append(p)
            prev = cnt.get(p, 0)
            cnt[p] = prev + 1
            answ = divmod(answ, prev + 1) # делим на то, что было
            answ = mulmod(answ, prev + 2) # умножаем на то, что стало
        else:
            # отмена операции: уменьшаем количество и обновляем ответ
            p = st[-1]
            st.pop()
            prev = cnt[p]
            cnt[p] = prev - 1
            answ = divmod(answ, prev + 1) # делим на то, что было
            answ = mulmod(answ, prev) # умножаем на то, что стало
        # выводим ответ:
        print(answ, end=" ")
        q -= 1
    print()
tt = int(input())
while tt > 0:
    solve()
    tt -= 1