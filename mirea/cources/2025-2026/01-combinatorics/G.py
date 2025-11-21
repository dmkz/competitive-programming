# File 'G.py'
# В этой задаче используется предподсчёт факториалов и обратных факториалов
# и формула количества перестановок строки с повторами:
# n! / (cnt[a]! * cnt[b]! * ... * cnt[z]!)

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
    # считаем количество каждой буквы, тогда ответ считаем по формуле:
    # n! / (cnt[a]! * cnt[b]! * ... * cnt[z]!)
    n = int(input())
    s = input().strip()
    letterCount = [0] * 26
    for letter in s:
        letterCount[ord(letter) - ord('a')] += 1
    answ = fact[n]
    for i in range(26):
        answ = mul(answ, ifact[letterCount[i]])
    print(answ)

if __name__ == "__main__":
    main()
