# Читаем награды и проходимость ступеней:
n = int(input())
a = [0] + list(map(int, input().split()))
cells = input()
def setmax(a, index, value):
    if a[index] < value: a[index] = value
# dp[i][r] — лучший путь к ступени i после r двойных прыжков подряд.
inf = 10 ** 30
dp = [[-inf] * 3 for i in range(n + 1)]
dp[0][0] = 0
for i in range(n + 1):
    for r in range(3):
        if dp[i][r] == -inf: continue
        # Одинарный прыжок сбрасывает длину серии двойных прыжков.
        if i + 1 <= n and cells[i] == '.':
            setmax(dp[i + 1], 0, dp[i][r] + a[i + 1])
        # После двух двойных прыжков следующий двойной прыжок запрещён.
        if r < 2 and i + 2 <= n and cells[i + 1] == '.':
            setmax(dp[i + 2], r + 1, dp[i][r] + a[i + 2])
# Выбираем лучшее допустимое состояние на последней ступени:
answ = max(dp[n])
if answ == -inf: print('IMPOSSIBLE')
else: print(answ)