# Вердикт: Time Limit Exceeded на тесте 33 для PyPy3-64, но для C++ - OK
from bisect import bisect_left
def lowpos(v, x):
    return bisect_left(v, x)
class SegTree:
    def __init__(self, n):
        self.n = n
        self.data = [0] * (4*n)
    def add(self, p, x):
        self._add(0, 0, self.n, p, x)
    def sum(self, l, r):
        return self._sum(0, 0, self.n, l, r+1)
    def _add(self, v, tl, tr, p, x):
        if p < tl or p >= tr: return
        if tl + 1 == tr:
            self.data[v] += x
            return
        tm = (tl + tr) // 2
        self._add(2*v+1, tl, tm, p, x)
        self._add(2*v+2, tm, tr, p, x)
        self.data[v] = self.data[2*v+1] + self.data[2*v+2]
    def _sum(self, v, tl, tr, ql, qr):
        if qr <= tl or ql >= tr: return 0
        if ql <= tl and tr <= qr: return self.data[v]
        tm = (tl + tr) // 2
        return self._sum(2*v+1, tl, tm, ql, qr) + self._sum(2*v+2, tm, tr, ql, qr)
def solve():
    # читаем входные данные:
    n, s, c = map(int, input().split())
    a = list(map(int, input().split()))
    b = input()
    # раскладываем товары в три различных списка по типам, а также в объединённый список:
    fi, se, th, coords = [], [], [], []
    for i in range(n):
        if b[i] == 'M': fi.append((a[i], i))
        elif b[i] == 'S': se.append((a[i], i))
        else:
            assert b[i] == 'D'
            th.append((a[i], i))
        coords.append((a[i], i))
    # сортируем:
    coords.sort()
    fi.sort()
    se.sort()
    th.sort()
    # сжимаем координаты и строим дерево отрезков поверх объединённого списка всех товаров:
    segTreeSum = SegTree(len(coords))
    segTreeCnt = SegTree(len(coords))
    def insert(x): # вставка товара
        ix = lowpos(coords, x)
        segTreeSum.add(ix, +x[0])
        segTreeCnt.add(ix, +1)
    def remove(x): # удаление товара
        ix = lowpos(coords, x)
        segTreeSum.add(ix, -x[0])
        segTreeCnt.add(ix, -1)
    # сперва вставляем туда все элементы:
    for it in coords: insert(it)
    # теперь перебираем все варианты для фиксированного количества акций "три по c"
    # если мы использовали акцию 0 раз, то мы берём k самых дешёвых товаров суммой <= s
    # если мы использовали акцию 1 раз, то нам выгодно купить самый дорогой товар каждого
    # типа, удалить их из дерева отрезков как доступные для покупки, а затем снова купить
    # k самых дешёвых товаров суммой <= s. Так перебираем все варианты и находим лучший
    answ, best, pref = 0, 0, 0
    for x, _ in coords:
        if pref+x <= s: pref += x; best += 1
        else: break
    # применяем акцию, пока можем, и считаем лучший вариант для заданного количества акций:
    while (len(fi) or len(se) or len(th)) and s >= c:
        # удаляем три самых дорогих товара: включаем их в акцию
        if len(fi):
            item = fi.pop()
            answ += 1
            remove(item)
        if len(se):
            item = se.pop()
            answ += 1
            remove(item)
        if len(th):
            item = th.pop()
            answ += 1
            remove(item)
        s -= c
        # теперь бинарным поиском находим, какое максимальное количество товаров можем купить
        # за оставшиеся деньги по одному:
        low, high = -1, n
        while high - low > 1:
            mid = (low + high) // 2
            if segTreeSum.sum(0, mid) > s: high = mid
            else: low = mid
        # low - крайний элемент, для которого sum(0, low) <= S
        best = max(best, answ + segTreeCnt.sum(0, low))
    print(best)
tt = int(input())
while tt > 0:
    solve()
    tt -= 1