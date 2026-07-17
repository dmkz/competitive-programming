# Пример: количество каждой буквы от 'a' до 'z' на подотрезке.
# Ввод: строка s, затем q запросов [l, r] в единичной индексации.
# Вывод: для каждого запроса 26 чисел - количества букв 'a'..'z' на отрезке.

s = input().strip()
n = len(s)
q = int(input())

# pref[i][c] хранит количество буквы c среди первых i символов строки.
pref = [[0] * 26 for _ in range(n + 1)]
for i, ch in enumerate(s):
    pref[i + 1] = pref[i][:]
    pref[i + 1][ord(ch) - ord('a')] += 1

for _ in range(q):
    l, r = map(int, input().split())
    l -= 1
    r -= 1

    # Для каждой буквы берём разность двух префиксных состояний.
    answer = [0] * 26
    for c in range(26):
        answer[c] = pref[r + 1][c] - pref[l][c]
    print(*answer)