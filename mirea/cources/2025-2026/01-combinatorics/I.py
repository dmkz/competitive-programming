# File 'I.py'
import sys

MOD = 10**9 + 7

def mul(a, b):
    return a * b % MOD

def binpow(a, n):
    return pow(a, n, MOD);

def main():
    input = sys.stdin.readline
    n, m, k = map(int, input().split())

    if k == 1 or k > n:
        # ограничений нет, любую букву можем выбрать как угодно
        numUniqueLetters = n
    elif k == n:
        # вся строка - палиндром. Первую половину букв выбираем как угодно
        numUniqueLetters = (n + 1) // 2
    elif k % 2 == 0:
        # если k - чётное, то все символы должны быть равны одной букве
        numUniqueLetters = 1
    else:
        # если k - нечётное, то чётные должны быть равны одной букве,
        # а нечётные - другой
        numUniqueLetters = 2

    print(binpow(m, numUniqueLetters))

if __name__ == "__main__":
    main()
