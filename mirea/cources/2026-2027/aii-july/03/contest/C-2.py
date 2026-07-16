# Данное решение работает за линейное времян - за O(n+q). Мы храним одновременно:
# 1) стек из элементов;
# 2) стек на минимум;
# 3) стек на максимум;
# 4) хеш-таблицу с количеством каждого элемента.
# Из хеш-таблицы удаляем значения, когда их количество достигло нуля. Таким образом,
# размер хеш-таблицы и будет количеством различных элементов. А минимум и максимум
# берём с верхушки стеков.
inf = 1000000007


def solve():
    # читаем данные
    n = int(input())
    cnt = {}
    stVal, stMin, stMax = [], [], []
    # добавим бесконечности:
    stVal.append(inf)
    stMin.append(+inf)
    stMax.append(-inf)
    # теперь добавим нормальные элементы:
    i = 0
    while i < n:
        for x in map(int, input().split()):
            stVal.append(x)
            stMin.append(min(stMin[-1], x))
            stMax.append(max(stMax[-1], x))
            cnt[x] = cnt.get(x, 0) + 1
            i += 1
            if i == n:
                break
    # обрабатываем запросы
    q = int(input())
    while q > 0:
        query = input().split()
        c = query[0]
        if c == '+':
            x = int(query[1])
            stVal.append(x)
            stMin.append(min(stMin[-1], x))
            stMax.append(max(stMax[-1], x))
            cnt[x] = cnt.get(x, 0) + 1
        elif c == '?':
            print(stMin[-1], stMax[-1], len(cnt))
        elif c == '-':
            # сначала удалим из стека:
            last = stVal[-1]
            stVal.pop()
            stMin.pop()
            stMax.pop()
            # теперь аккуратно удалим из хеш-таблицы:
            cnt[last] -= 1  # уменьшаем количество
            if cnt[last] == 0:  # стало равным нулю => удаляем
                del cnt[last]
        q -= 1


tt = int(input())
for _ in range(tt):
    solve()