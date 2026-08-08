# Читаем последовательность:
n = int(input())
a = list(map(int, input().split()))
# Инициализируем длину подпоследовательности из одного элемента:
dp = [1] * n
# Перебираем возможные предпоследние элементы:
for i in range(n):
    for j in range(i):
        if a[j] < a[i]: dp[i] = max(dp[i], dp[j] + 1)
# Выводим длину лучшей подпоследовательности:
answ = 0
for it in dp:
    answ = max(answ, it)
print(answ)