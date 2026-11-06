from random import randint
# модульная арифметика и хеши:
mod1, mod2 = 10**9+7, 10**9+9
def random(a, b):
    return randint(a, b)
NMAX = 1 << 20
def initPower():
    result = [[1]*(NMAX+1) for _ in range(2)]
    base1 = random(1000, mod1-10) | 1 # нечётное число всегда лучше
    base2 = random(1000, mod2-10) | 1 # аналогично
    result[0][1], result[1][1] = base1, base2
    for i in range(2, NMAX+1):
        result[0][i] = result[0][i-1]*result[0][1]%mod1
        result[1][i] = result[1][i-1]*result[1][1]%mod2
    return result
power = initPower()
# решение задачи:
def solve():
    # читаем входные данные:
    k, s = input().split(); k = int(k)
    # предварительно вычисляем полиномиальные хеши, чтобы сравнивать подстроки за O(1):
    n = len(s)
    hashes = [[0]*(n+1) for _ in range(2)]
    for i, it in enumerate(s):
        hashes[0][i+1] = (hashes[0][i]*power[0][1]+ord(it))%mod1
        hashes[1][i+1] = (hashes[1][i]*power[1][1]+ord(it))%mod2
    # вычисление хешей на подотрезке [start, start + len):
    def getHash(start, len):
        return ((hashes[0][start+len]-hashes[0][start]*power[0][len])%mod1,
                (hashes[1][start+len]-hashes[1][start]*power[1][len])%mod2)
    # находим все возможные периоды: периодичность проверяем хешами, сравнивая подстроки [0, n-t) и [t, n)
    answer = []
    for period in range(1, n+1):
        if getHash(0, n-period) == getHash(period, n-period): answer.append(period)
    # ответ: минимальный период, который подходит под ограничения задачи на k дубликатов:
    was = False
    for it in answer:
        if it*k >= n:
            print(it)
            was = True
            break
    assert was
tt = int(input())
for _ in range(tt): solve()