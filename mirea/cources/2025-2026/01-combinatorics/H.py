# File 'H.py'
# Те же предподсчёты факториалов и обратных факториалов, что и в G,
# но нужно поддерживать ответ онлайн при изменениях символов.

import sys

MOD = 10**9 + 7
NMAX = 10**6 + 10

def mul(a, b):
    return a * b % MOD

def binpow(a, n):
    return pow(a, n, MOD)

def inverse(a):
    return binpow(a, MOD - 2)

# предподсчёт факториалов
fact = [1] * (NMAX + 1)
for i in range(2, NMAX + 1):
    fact[i] = fact[i - 1] * i % MOD

# предподсчёт обратных факториалов
# допустим, знаем ifact[n+1] = 1/(n+1)!
# Тогда мы можем вычислить и 1/n!, умножив ifact[n+1] на (n+1)
# формула: ifact[n] = (n+1) * ifact[n+1]
# считаем с конца в начало
ifact = [1] * (NMAX + 1)
ifact[-1] = inverse(fact[-1])
for i in range(NMAX - 1, -1, -1):
    ifact[i] = ifact[i + 1] * (i + 1) % MOD

def main():
    # быстрый ввод-вывод:
    input = sys.stdin.readline

    # считаем количество каждой буквы, тогда ответ считаем по формуле:
    # n! / (cnt[a]! * cnt[b]! * ... * cnt[z]!)
    # после запроса нужно пересчитывать ответ только для тех символов
    # которые меняются
    n = int(input())
    s = list(input().strip())
    letterCount = [0] * 26
    for letter in s:
        letterCount[ord(letter) - ord('a')] += 1
    answ = fact[n]
    for i in range(26):
        answ = mul(answ, ifact[letterCount[i]])
    print(answ)
    q = int(input())
    for _ in range(q):
        pos_str, newChar = input().split()
        pos = int(pos_str) - 1
        if s[pos] != newChar:
            oldCharId = ord(s[pos]) - ord('a')
            newCharId = ord(newChar) - ord('a')
            # пересчитываем только множители, которые затрагивают два символа:
            answ = mul(answ, fact[letterCount[oldCharId]])
            answ = mul(answ, fact[letterCount[newCharId]])
            letterCount[oldCharId] -= 1
            letterCount[newCharId] += 1
            answ = mul(answ, ifact[letterCount[oldCharId]])
            answ = mul(answ, ifact[letterCount[newCharId]])
            s[pos] = newChar
        print(answ)

if __name__ == "__main__":
    main()
