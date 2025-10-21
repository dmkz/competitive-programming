# Задача: K, Вердикт: OK, Время: 2.267s, Память: 327.07Mb
import sys;

def main():
    # быстрый ввод
    data = sys.stdin.buffer.read().split();
    it = iter(data);
    n = int(next(it)); q = int(next(it));

    ops = []; # все запросы в хронологическом порядке
    updates = []; # (t, l, r, d, vid) - запросы вставки после сжатия
    queries = []; # (t, p, k, id) - запросы k-й порядковой статистики
    keys = []; # сжатые координаты

    currTime = 0;
    for _ in range(q):
        tp = int(next(it))
        if tp == 1:
            # вставка
            a = int(next(it)) - 1;
            b = int(next(it)) - 1;
            c = int(next(it));
            d = int(next(it));
            ops.append((1, a, b, c, d, currTime));
            keys.append(c);
        else:
            # k-й элемент
            a = int(next(it)) - 1;
            k = int(next(it));
            qid = len(queries);
            ops.append((2, a, k, qid, currTime));
            queries.append((currTime, a, k, qid));
        currTime += 1;

    # сортировка + удаление повторов
    keys.sort();
    w = 0;
    for i in range(len(keys)):
        if i == 0 or keys[i] != keys[i-1]:
            keys[w] = keys[i];
            w += 1;
    vals = keys[:w];
    m = len(vals);
    
    # поиск сжатой координаты для x
    def id_of(x):
        lo, hi = 0, m;
        while lo < hi:
            md = (lo + hi) >> 1;
            if vals[md] < x:
                lo = md + 1;
            else:
                hi = md;
        return lo;

    for op in ops:
        if op[0] == 1:
            _, a, b, c, d, t = op;
            updates.append((t, a, b, d, id_of(c)));

    # сортируем все запросы по времени
    updates.sort(key=lambda x: x[0]);
    queries.sort(key=lambda x: x[0]);
    
    # создаём фенвика
    Fenwick = [0] * (n + 2);
    def add(i, v):
        i += 1;
        N1 = n + 1;
        while i <= N1:
            Fenwick[i] += v;
            i += i & -i;

    def sum(i):
        i += 1;
        s = 0;
        while i > 0:
            s += Fenwick[i];
            i -= i & -i;
        return s;
        
    def rangeAdd(l, r, v):
        add(l, v);
        add(r+1, -v);

    ans = [10**9 + 1] * len(queries);

    sys.setrecursionlimit(1 << 25);

    def solve(L, R, updList, queryList):
        if not queryList:
            return;
        if L > R:
            return;
        if L == R:
            # пришли в лист, надо ответить на запросы
            v = vals[L] if L < m else 10**9 + 1;
            for (_, _, _, qid, _) in queryList:
                ans[qid] = v;
            return;
        mid = (L + R) >> 1;

        # Разбиваем апдейты на те, которые слева, и те, которые справа
        updLeft = [];
        updRight = [];
        for (t, l, r, d, vid) in updList:
            if vid <= mid:
                updLeft.append((t, l, r, d, vid));
            else:
                updRight.append((t, l, r, d, vid));

        # апдейты
        ql = [];
        qr = [];
        i = 0;
        U = updLeft;
        # применяем апдейты до времени запроса
        for (tq, p, kcur, qid, _) in queryList:
            while i < len(U) and U[i][0] <= tq:
                _, l, r, d, _ = U[i];
                rangeAdd(l, r, d);
                i += 1;
            s = sum(p);
            if s >= kcur:
                ql.append((tq, p, kcur, qid, s));
            else:
                qr.append((tq, p, kcur - s, qid, s));
        # откатываем
        while i > 0:
            i -= 1;
            _, l, r, d, _ = U[i];
            rangeAdd(l, r, -d);

        # рекурсия
        solve(L, mid, updLeft, ql);
        solve(mid + 1, R, updRight, qr);

    # запуск рекурсии 
    rootQueries = [(t, p, k, qid, 0) for (t, p, k, qid) in queries];
    solve(0, m - 1, updates, rootQueries);
    
    # вывод ответа
    out = [];
    for v in ans:
        out.append(str(v));
    sys.stdout.write("\n".join(out));

if __name__ == "__main__":
    main();