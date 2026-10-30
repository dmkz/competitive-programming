from math import gcd
def solve(r):
    # число x можно представить в виде: x = d + 10*(other_digits)
    # переберём последнюю цифру и посчитаем, какие числа на неё делятся
    # для каждой цифры точно делятся делители 10, то есть: {1, 2, 5}
    # остальные сокращаем на gcd и считаем, сколько способов выбрать (other_digits)
    # other_digits должно делиться на d / gcd(d, 10)
    answ = 0
    for d in range(1,10):
        step = d // gcd(d,10)
        # к ответу прибавляется k+1 из: d + 10 * k * step <= r
        # k <= (r - d) / (10 * step)
        k = max(0,(r-d) // (10*step))
        answ += k+1 if r >= d else 0
    return answ
q = int(input())
while q > 0:
    q -= 1
    l, r = map(int,input().split())
    print(solve(r) - solve(l-1))