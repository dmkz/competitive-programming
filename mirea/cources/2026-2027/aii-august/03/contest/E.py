dp = [[0] * 1001 for _ in range(1001)]  # глобальный массив нужен из-за мультитестов
                                         # нельзя выделять массив 1001 * 1001 для каждого теста, так как их 10000
def solve():
    # читаем данные:
    s = ["$"] + list(input())
    t = ["^"] + list(input())
    # инициализируем динамику:
    for i in range(1, len(s)):
        for j in range(1, len(t)):
            if s[i] == t[j]:
                dp[i][j] = 1 + dp[i - 1][j - 1]
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
    # отдельно вынесем функцию вычисления i-й строки: она получается удалением цикла по j
    def calcIthRow(i):
        for j in range(1, len(t)):
            if s[i] == t[j]:
                dp[i][j] = 1 + dp[i - 1][j - 1]
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
    # отдельно вынесем функцию вычисления j-го столбца: она получается удалением цикла по i
    def calcJthCol(j):
        for i in range(1, len(s)):
            if s[i] == t[j]:
                dp[i][j] = 1 + dp[i - 1][j - 1]
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
    # обрабатываем запросы:
    q = int(input())
    while q > 0:
        query = input().split()
        if query[0] == "S+":
            # читаем символ, добавляем его в конец строки "s", и вычисляем новую строку ДП:
            ch = query[1]
            s.append(ch)
            calcIthRow(len(s) - 1)
        elif query[0] == "T+":
            # читаем символ, добавляем его в конец строки "t", и вычисляем новый столбец ДП:
            ch = query[1]
            t.append(ch)
            calcJthCol(len(t) - 1)
        elif query[0] == "S-":
            # просто удаляем последний символ строки s
            s.pop()
        elif query[0] == "T-":
            # просто удаляем последний символ строки t
            t.pop()
        # выводим ответ:
        print(dp[len(s) - 1][len(t) - 1])
        q -= 1
tt = int(input())
while tt > 0:
    solve()
    tt -= 1