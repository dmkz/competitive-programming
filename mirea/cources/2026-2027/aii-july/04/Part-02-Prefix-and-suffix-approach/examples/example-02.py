# Пример: Школа танцев.
# Ввод: n и строка из двух типов символов, описывающая ряд учеников.
# Вывод: количество подотрезков, где учеников двух типов поровну.

n = int(input())
s = input().strip()

# Считаем, что символ 'a' даёт вклад +1,
# а любой другой символ даёт вклад -1.
cnt = {0: 1}
balance = 0
answer = 0
for ch in s:
    balance += 1 if ch == 'a' else -1
    answer += cnt.get(balance, 0)
    cnt[balance] = cnt.get(balance, 0) + 1

print(answer)