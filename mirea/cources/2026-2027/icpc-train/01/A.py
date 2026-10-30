def solve():
    # читаем изначальные количества монет:
    c = list(map(int,input().split()))
    d = [1,2,5,10,20,50]
    # читаем и отвечаем на запросы:
    q = int(input())
    while q > 0:
        q -= 1
        # читаем i-й запрос:
        p, *u = map(int,input().split())
        # считаем сумму. если суммы не хватает, то покупатель сразу уходит:
        s = 0
        for i in range(6):
            s += d[i] * u[i]
        if s < p:
            print("REFUSED")
            continue
        # сначала монеты попадают в автомат:
        saved = c.copy()
        for i in range(6):
            c[i] += u[i]
        # теперь мы должны выдать сдачу:
        r = s - p
        answ = [0] * 6
        for i in range(5,-1,-1):
            # выдаём максимальное количество монет, которое можем:
            cntI = min(c[i], r // d[i])
            r -= d[i] * cntI
            c[i] -= cntI
            answ[i] = cntI
        if r != 0:
            # не получилось -> откатываем:
            c = saved
            print("REFUSED")
            continue
        # тут всё получилось, выводим ответ:
        print(*answ)
solve()