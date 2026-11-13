# Вердикт: 1.303 с - Time Limit Exceeded на PyPy3-64, тогда как на C++ - OK
def solve():
    n = int(input())
    a = list(map(int,input().split()))
    # 0 удалений невозможно: S = 0 (mod n)
    # 1 удаление невозможно: S - a[i] = 0 (mod n-1) для любого i => a[i] = S (mod n-1) =>
    # остатки всех элементов равны одному и тому же числу.
    # Похоже, что мы можем добиться неравенства нулю только тогда, когда у нас будет как
    # минимум два различных остатка. Иначе -1
    S = sum(a)
    if (S % n) != 0: print(n); return
    cnt = [0] * n
    for i in range(1,min(30,n)): # сколько элементов удаляем
        for j in range(len(cnt)):
            cnt[j] = 0
        for it in a:
            cnt[it % (n-i)] += 1
        fi = 0
        while fi < len(cnt) and cnt[fi] == 0: fi += 1
        se = fi+1
        while se < len(cnt) and cnt[se] == 0: se += 1
        if se == len(cnt):
            # только один уникальный остаток: пробуем вычесть его из S ровно i раз
            if (S-i*fi) % (n-i) != 0:
                print(n-i)
                return
        else:
            # даже проверять не нужно, всегда можем
            print(n-i)
            return
    print(-1)
tt = int(input())
for _ in range(tt): solve()