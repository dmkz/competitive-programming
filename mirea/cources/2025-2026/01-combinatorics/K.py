# File 'K.py'

MOD = 10**9 + 7

def mul(a, b):
    return a * b % MOD

def add(a, b):
    a += b
    if a >= MOD:
        a -= MOD
    return a

def sub(a, b):
    a -= b
    if a < 0:
        a += MOD
    return a

def binpow(a, n):
    res = 1
    while n > 0:
        if n & 1:
            res = mul(res, a)
        n >>= 1
        a = mul(a, a)
    return res

def inv(a):
    return binpow(a, MOD - 2)

def main():
    # считаем факториалы и обратные факториалы:
    fact = [1] * (1000 + 1)
    ifact = [1] * (1000 + 1)
    for i in range(2, 1000 + 1):
        fact[i] = mul(fact[i - 1], i)
        ifact[i] = inv(fact[i])

    # заполняем массив из лампочек которые горят / не горят
    n, m = map(int, input().split())
    in_arr = [0] * n
    pos = [int(x) for x in input().split()]
    for v in pos[:m]:
        in_arr[v - 1] = 1

    # Для каждого подотрезка без лампочек считаем его длину
    # для такого подотрезка (кроме префикса и суффикса), мы можем зажигать
    # лампочку либо слева, либо справа. В итоге 2^(длина подотрезка-1) вариантов
    # Последняя лампочка выбирается единственным способом.
    # Теперь, выбирая последовательность действий, каждый раз мы выбираем
    # подотрезок, в котором будем зажигать лампочку. Если мы пронумеруем
    # подотрезки от 1 до K (их количества), то получится последовательность
    # из чисел от 1 до K. Количество цифры i равно длине i-го подотрезка.
    
    # считаем длины всех непрерывных отрезков из нулей двумя указателями
    segLen = []
    i = 0
    while i < n:
        j = i
        while j < n and in_arr[i] == in_arr[j]:
            j += 1
        # подотрезок [i, j) состоит из символов, равных in_arr[i]
        if j > i and in_arr[i] == 0:
            segLen.append(j - i)
        i = j

    # считаем ответ. Сначала формируем последовательность из выбранных номеров
    # подотрезков:
    answ = fact[n - m]
    for length in segLen:
        answ = mul(answ, ifact[length])

    # теперь для внутренних отрезков считаем количество вариантов их заполнения:
    prefixExists = (in_arr[0] == 0)
    suffixExists = (in_arr[-1] == 0)
    # пропускаем префикс и суффикс при перемножении степеней двойки
    start = 1 if prefixExists else 0
    end = len(segLen) - (1 if suffixExists else 0)
    for idx in range(start, end):
        answ = mul(answ, binpow(2, segLen[idx] - 1))

    print(answ)

if __name__ == "__main__":
    main()
