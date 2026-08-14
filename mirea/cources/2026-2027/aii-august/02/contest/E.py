# Запишем формальное условие. Мы можем сделать прыжок i --> j, если верно следующее:
# i < j и y[j] - y[i] < x[j] - x[i]. Преобразуем неравенство путём переноса того, что зависит
# от i, налево, а того, что зависит от j, направо. Получим: x[i] - y[i] < x[j] - y[j].
# Обозначим A[i] = x[i] - y[i]. Тогда нужно найти наибольшую возрастающую последовательность
# в массиве A и восстановить её элементы.
from bisect import bisect_left
inf = 2 * 10 ** 9 + 100
def solve():
    # читаем данные:
    n = int(input())
    x = list(map(int, input().split()))
    y = list(map(int, input().split()))
    # Формальное условие: y[j] - y[i] < x[j] - x[i] => x[i] - y[i] < x[j] - y[j]
    # Обозначим a[i] = x[i] - y[i]. Тогда для массива "a" нужно найти максимальную
    # возрастающую подпоследовательность и вывести индексы входящих в неё элементов
    a = [0] * n
    prev = [-1] * n
    dp = [(inf, inf)] * (n + 1)
    dp[0] = (-inf, -1)
    for i in range(n):
        a[i] = x[i] - y[i]
        it = bisect_left(dp, (a[i], -inf))
        prev[i] = dp[it - 1][1]
        dp[it] = (a[i], i)
    # находим длину НВП:
    len = n
    while len >= 0 and dp[len][0] == inf:
        len -= 1
    # восстанавливаем индексы входящих в неё элементов:
    answ = []
    i = dp[len][1]
    while i > -1:
        answ.append(i)
        i = prev[i]
    answ.reverse()
    # выводим ответ:
    print(len)
    for it in answ:
        print(it + 1, end=' ')
    print()
tt = int(input())
while tt > 0:
    solve()
    tt -= 1