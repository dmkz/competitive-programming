# строки, реализация, максимальный общий префикс и суффикс, O(n^2)
import sys

input = sys.stdin.readline

tt = int(input())
for _ in range(tt):
    s, t = input().split()
    if t in s:
        print("0")
        print("0")
        continue

    # строка s входит в строку t: префикс и суффикс определяются однозначно
    pos = t.find(s)
    if pos != -1:
        pref = t[:pos]
        suff = t[pos + len(s):]
        pref = pref[::-1]
        print(len(pref), pref)
        print(len(suff), suff)
        continue

    # иначе мы вставляем либо только в конец, либо только в начало
    # ищем наибольший суффикс s, совпадающий с префиксом t:
    maxPref = 0
    maxSuff = 0
    for length in range(min(len(s), len(t)) + 1):
        if s[len(s) - length:] == t[:length]:
            maxSuff = length

    # ищем наибольший префикс s, совпадающий с суффиксом t:
    for length in range(min(len(s), len(t)) + 1):
        if s[:length] == t[len(t) - length:]:
            maxPref = length

    # выводим ответ:
    if maxPref >= maxSuff:
        # вставляем только в префикс:
        t = t[:len(t) - maxPref]
        t = t[::-1]
        print(len(t), t)
        print(0)
    else:
        # вставляем только в суффикс:
        t = t[maxSuff:]
        print(0)
        print(len(t), t)