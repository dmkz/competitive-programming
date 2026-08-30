mod = 998244353
def solve():
    # читаем данные:
    n = int(input())
    a = list(map(int, input().split()))
    # лестница - комбинация из двух подпоследовательностей: возрастающей и убывающей
    # для каждой позиции считаем количество возрастающих
    # подпоследовательностей, заканчивающихся в ней:
    dpL = [1] * n
    for i in range(1, n):
        for j in range(i):
            if a[j] < a[i]:
                dpL[i] = (dpL[i] + dpL[j]) % mod
    # зеркально для каждой позиции считаем количество убывающих
    # подпоследовательностей, начинающихся в ней:
    dpR = [1] * n
    for i in range(n-2, -1, -1):
        for j in range(i+1, n):
            if a[j] < a[i]:
                dpR[i] = (dpR[i] + dpR[j]) % mod
    # считаем и выводим ответ:
    answ = 0
    for i in range(n):
        answ = (answ + dpL[i] * dpR[i]) % mod
    print(answ)
tt = int(input())
for _ in range(tt):
    solve()